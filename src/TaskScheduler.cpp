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
#include <queue>

#include "TaskScheduler.hpp"
#include "TaskSchedulerEvent.hpp"
#include "GraphNode.hpp"
#include "GraphNodeData.hpp"

// clock interrupt each 300
#define SYSTEM_IRQ_PERIOD 300
#define SYSTEM_IRQ_LIMIT  10

namespace Orca::Task {

/**
 * Default constructor.
 * @brief Internal lists (blocked, ready, and running) 
 * initialization and instantiation of graph data into
 * tcbs.
 * @param graph A task graph instance containing tasks'
 * information; at least id, name, period, capacity and
 * deadline are required.
 */
TaskScheduler::TaskScheduler(Orca::Graph::Graph* graph) {
    // Initialize lists
    this->running = new std::list<TaskControlBlock*>();
    this->ready = new std::list<TaskControlBlock*>();
    this->blocked = new std::list<TaskControlBlock*>();

    // For each task in the graph, create a new task control block
    // and add it to the blocked list; all tasks started as blocked
    // due to the scheduler calculate which tasks go to the ready
    // list during each schedule.
    std::list<Orca::Graph::GraphNode*>::iterator i = graph->getNodes()->begin();
    for (; i != graph->getNodes()->end(); i++) {
        TaskControlBlock* block = new TaskControlBlock(
            (*i)->getData()->id,
            (*i)->getData()->name,
            (*i)->getData()->period,
            (*i)->getData()->cpDever,
            (*i)->getData()->deadline);

        this->blocked->push_back(block);
        std::cout << block->toString() << std::endl;
    }

    _clock_irq = new TaskControlBlock(-1, "_clock_irq",
        SYSTEM_IRQ_PERIOD, SYSTEM_IRQ_PERIOD, SYSTEM_IRQ_PERIOD);
}

/**
 * Destructor.
 * @brief We erase all tcb from memory, then erase lists
 */
TaskScheduler::~TaskScheduler() {
    std::list<Orca::Task::TaskControlBlock*>::iterator i;

    for (i = running->begin(); i != running->end(); i++) delete (*i);
    for (i = ready->begin(); i != ready->end(); i++) delete (*i);
    for (i = blocked->begin(); i != blocked->end(); i++) delete (*i);

    delete this->running;
    delete this->ready;
    delete this->blocked;
}

/**
 * Scheduler simulation
 * @brief We simulate the scheduler for <ticks> ticks 
 * using the provided <algo> scheduling algorithm.
 * @param algo Scheduling algorithm to be used
 * @param ticks Number of ticks to simulate. See <SYSTEM_IRQ_PERIOD>
 */
void TaskScheduler::Sim(TaskSchedulingAlgorithm* algo, uint32_t ticks) {
    // reset timers
    this->ticks_to_sim = ticks;
    this->current_time = 0;

    // move all tasks to the blocked list
    std::list<TaskControlBlock*>::iterator i;
    for (i = this->running->begin(); i != this->running->end(); i++)
        this->blocked->push_back(*i);
    for (i = this->ready->begin(); i != this->ready->end(); i++)
        this->blocked->push_back(*i);
    this->running->clear();
    this->ready->clear();

    // stores events in a priority queue (sorted by time)
    std::priority_queue<TaskSchedulerEvent> events
        = std::priority_queue<TaskSchedulerEvent>();

    // add the scheduler to the priotity queue. Since it is
    // the only event in the queue, it should run first
    _clock_irq->next_deadline = 0;
    events.push(TaskSchedulerEvent(0, _clock_irq));

    // simulate the system until reach the number of ticks
    while (this->ticks_to_sim-- > 0) {
        // get event from the top of the queue (which is the
        // nearest in time)
        TaskSchedulerEvent e = events.top();
        events.pop();

        // update simulation clock
        this->current_time = e.time;

        // next event is the scheduling interruption
        if (e.data->id == -1) {
            // get the next event from the simulation queue
            TaskSchedulerEvent timedOutTask = events.top();
            events.pop();

            // task timed out, update its capacity
            timedOutTask.data->current_capacity +=
                timedOutTask.data->next_deadline - this->current_time;

            // check whether the task has enough capacity to run again
            if (e.data->capacity == e.data->current_capacity) {
                e.data->current_capacity = 0;
                e.data->next_deadline += e.data->deadline;
                this->ready->push_back(timedOutTask.data);
            } else {
                this->blocked->push_back(timedOutTask.data);
            }

            // remove task from the executing queue
            this->running->remove(timedOutTask.data);

            // add scheduling event back to the queue
            _clock_irq->deadline += _clock_irq->deadline;
            events.push(TaskSchedulerEvent(
                _clock_irq->next_deadline, _clock_irq));

        // next event is a task finishing
        } else {
            // task finished, reset capacity, update deadline
            // and add it to the blocked list (end of capacity)
            e.data->capacity = 0;
            e.data->next_deadline += e.data->deadline;

            this->running->remove(e.data);
            this->blocked->push_back(e.data);
        }

        // process blocked tasks
        for (i = this->blocked->begin(); i != this->blocked->end(); i++) {
            this->ready->push_back(*i);
        }
        blocked->clear();

        // call scheduler to sort the ready queue
        algo->Schedule(this->ready);

        // add current task to the running list
        events.push(TaskSchedulerEvent(
            this->current_time + this->ready->front()->current_capacity,
            this->ready->front()));

        // removed current event from the ready queue
        this->ready->remove(this->ready->front());
    }
}

}  // namespace Orca::Task
