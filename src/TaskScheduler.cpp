/******************************************************************************
 * This file is part of project ORCA. More information on the project
 * can be found at the following repositories at GitHub's website.
 *
 * http://https://github.com/andersondomingues/orca-sim
 * http://https://github.com/andersondomingues/orca-software
 * http://https://github.com/andersondomingues/orca-mpsoc
 * http://https://github.com/andersondomingues/orca-tools
 * http://https://github.com/andersondomingues/orca-modeling
 *
 * Copyright (C) 2018-2020 Anderson Domingues, <ti.andersondomingues@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. 
******************************************************************************/
#include <iostream>

#include "TaskScheduler.hpp"
#include "TaskSchedulerEvent.hpp"
#include "GraphNode.hpp"
#include "GraphNodeData.hpp"

// clock interrupt each 5ms
#define SYSTEM_IRQ_PERIOD 5

namespace Orca::Task {

TaskScheduler::TaskScheduler(Orca::Graph::Graph* graph) {
    // initialize lists
    this->running = new std::list<TaskSchedulerEvent>();
    this->ready = new std::list<TaskSchedulerEvent>();
    this->blocked = new std::list<TaskSchedulerEvent>();

    // schedule all tasks. Create task block and add all tasks to the
    // ready queue. In that queue, tasks are sorted by their deadlines
    // (earliest first).
    std::list<Orca::Graph::GraphNode*>::iterator i;

    // for each task in the graph, create a new task control block
    for (i = graph->getNodes()->begin(); i != graph->getNodes()->end(); i++) {
        TaskControlBlock block;
        block.id = (*i)->getData()->id;
        block.name = (*i)->getData()->name;
        block.deadline = (*i)->getData()->deadline;
        block.capacity = (*i)->getData()->cpDever;
        block.period   = (*i)->getData()->period;
        block.next_deadline = block.deadline;

        // push these tasks to the "ready" list
        this->ready->push_back(TaskSchedulerEvent(block.deadline, block));

        std::cout << "[" << block.id << "]" << block.name << "(d:"
            << block.deadline << ", c:"
            << block.capacity << ", p:"
            << block.period << ")" << std::endl;
    }

    // schedule clock interruption
    _clock_irq.id = 0;
    _clock_irq.name = "CLOCK_IRQ";
    _clock_irq.capacity = SYSTEM_IRQ_PERIOD;
    _clock_irq.deadline = SYSTEM_IRQ_PERIOD;
    _clock_irq.period = SYSTEM_IRQ_PERIOD;
    _clock_irq.next_deadline = SYSTEM_IRQ_PERIOD;

    // add clock irq to running list (clock irq is always running)
    this->running->push_back(TaskSchedulerEvent(SYSTEM_IRQ_PERIOD, _clock_irq));

    std::cout << "[" << _clock_irq.id << "]" << _clock_irq.name << "(d:"
        << _clock_irq.deadline << ", c:"
        << _clock_irq.capacity << ", p:"
        << _clock_irq.period << ")" << std::endl;
}

TaskScheduler::~TaskScheduler() {
    delete this->running;
    delete this->ready;
    delete this->blocked;
}

void TaskScheduler::Sim(TaskSchedulingAlgorithm* algo, uint32_t ticks) {
    this->ticks_to_sim = ticks;

    // simulate until reach number of ticks
    while (this->ticks_to_sim > 0) {
        // sort running task by their deadline
        this->running->sort([]
            (TaskSchedulerEvent& a, TaskSchedulerEvent& b){
                return a.data.next_deadline < b.data.next_deadline;
        });

        // get first object
        TaskSchedulerEvent e;
        e = this->running->front();

        // empty running list and update exec time for all executing tasks
        std::list<TaskSchedulerEvent>::iterator i;
        for (i = this->running->begin(); i != this->running->end(); i++) {
            TaskSchedulerEvent e = *i;
            if (e.data.id != 0) {
                e.data.next_deadline += e.data.deadline;
                ready->push_front(e);
            }
        }

        // update current time
        this->current_time = this->current_time + e.data.capacity;

        // empty running list
        this->running->clear();

        // call scheduler
        algo->Schedule(ready, blocked, running);

        // dispatch next job to the running queue
        algo->Dispatch(ready, blocked, running);

        // if last event is clock, set clock to next deadline
        if (e.data.id == 0) {
            _clock_irq.next_deadline = this->current_time + _clock_irq.deadline;
            this->ticks_to_sim--;  // decrease the number of ticks to sim
        }

        // update next clock event and add clock interruption
        this->running->push_front(
            TaskSchedulerEvent(_clock_irq.next_deadline, _clock_irq));

        std::cout << this->current_time << "\t\t" << e.data.name << std::endl;
    }
}

}  // namespace Orca::Task
