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
#include "TaskScheduler.hpp"
#include "TaskSchedulerEvent.hpp"
#include "GraphNode.hpp"
#include "GraphNodeData.hpp"

// clock interrupt each 5ms
#define SYSTEM_IRQ_PERIOD 5

namespace Orca::Task {

TaskScheduler::TaskScheduler() {
    this->running = new std::priority_queue<TaskSchedulerEvent>();
    this->ready = new std::priority_queue<TaskSchedulerEvent>();
    this->blocked = new std::priority_queue<TaskSchedulerEvent>();
}

TaskScheduler::~TaskScheduler() {
    delete this->running;
    delete this->ready;
    delete this->blocked;
}

void TaskScheduler::Sim(
    TaskSchedulingAlgorithm* algo, Orca::Graph::Graph* graph, uint32_t ticks) {
    this->ticks_to_sim = ticks;

    // schedule all tasks. Create task block and add all tasks to the
    // ready queue. In that queue, tasks are sorted by their deadlines
    // (earliest first).
    std::list<Orca::Graph::GraphNode*>::iterator i;

    for (i = graph->getNodes()->begin(); i != graph->getNodes()->end(); i++) {
        TaskControlBlock block;
        block.id = (*i)->getData()->id;
        block.deadline = (*i)->getData()->executionTime;
        block.capacity = block.deadline;
        block.last_release = -1;
        block.next_deadline = block.deadline;
        block.status = TaskStatus::READY;
        this->ready->push(TaskSchedulerEvent(0, block));
    }

    // schedule clock interruption
    TaskControlBlock block;
    block.capacity = SYSTEM_IRQ_PERIOD;
    block.deadline = SYSTEM_IRQ_PERIOD;
    block.id = -1;
    block.last_release = 0;
    block.next_deadline = SYSTEM_IRQ_PERIOD;
    block.period = SYSTEM_IRQ_PERIOD;
    block.status = TaskStatus::READY;
    this->ready->push(TaskSchedulerEvent(0, block));

    // simulate until reach number of ticks
    while (this->ticks_to_sim > 0) {

        TaskSchedulerEvent e;
        e = this->running->top();
        this->running->pop();

        this->current_time = e.time;  // update internal clock
        this->blocked->push(e);

        // pop next event
        // algo->Schedule(graph, );
        // algo->Dispatch(graph, this->tasks);
    }
}

}  // namespace Orca::Task
