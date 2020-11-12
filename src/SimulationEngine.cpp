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
#include <queue>
#include <iostream>

#include "SimulationEngine.hpp"
#include "SystemEvent.hpp"
#include "SchedulingAlgorithm.hpp"

// ms
#define SCHED_IRQ_PERIOD 300

namespace OrcaSeer::Simulation {

SimulationEngine::SimulationEngine(OrcaSeer::Graph::Graph* graph,
 OrcaSeer::Task::SchedulingAlgorithm* algo) {
    this->systemTime = 0;  // system starts at second zero
    this->queue = new std::priority_queue<SystemEvent>();

    this->running = new std::list<OrcaSeer::Task::TaskControlBlock*>();
    this->blocked = new std::list<OrcaSeer::Task::TaskControlBlock*>();
    this->ready = new std::list<OrcaSeer::Task::TaskControlBlock*>();

    // populate blocked list with tasks from the graph
    std::list<OrcaSeer::Graph::GraphNode*>::iterator i;
    for (i = graph->getNodes()->begin(); i != graph->getNodes()->end(); ++i) {
        OrcaSeer::Graph::GraphNode* node = *i;

        OrcaSeer::Task::TaskControlBlock* block
            = new OrcaSeer::Task::TaskControlBlock(
            node->getData()->id,
            node->getData()->name,
            node->getData()->period,
            node->getData()->cpDever,
            node->getData()->deadline);

        this->blocked->push_back(block);
    }

    this->algorithm = algo;
}

SimulationTime SimulationEngine::Simulate(SimulationTime milliseconds) {
    // adds a new event to the simulation queue to call the
    // scheduler at time=zero
    SystemEvent sched_irq = SystemEvent(0, SystemEventType::SCHEDULER_IRQ);
    queue->push(sched_irq);

    do {
        // Remove next event from the simulation queue. If this is the
        // beggining of the simulation, the queue should have only one
        // event, the scheduler_irq routine. The rest of the simulation
        // should keep exactly two events, the scheduler_irq plus at least
        // one task running. This concept can be later extended to admit
        // two or more cpus, as well as two or more scheduler.
        SystemEvent top_event = queue->top();
        queue->pop();

        // update current time
        this->elapsedTime = top_event.time - this->systemTime;
        this->systemTime += this->elapsedTime;

        std::cout << this->systemTime << ": " <<
            (top_event.type == SystemEventType::TASK_FINISHED_IRQ
                ? "task finished"
                : "scheduler irq")
                    << std::endl;

        PrintTaskLists();

        // If the top of the queue is a task finish syscall, we must
        // put the finished task into the blocked queue and process
        // a new task to take its place
        this->Schedule(algorithm);

        // Next event is the scheduler interruption
        if (top_event.type == SystemEventType::SCHEDULER_IRQ) {
            // remove all events from the simulation queue; since the
            // scheduler_irq has been removed, only the event for the
            // running task remains
            while (queue->size())
                queue->pop();

            // register the interruption
            sched_irq.time = this->systemTime + SCHED_IRQ_PERIOD;
            queue->push(sched_irq);
        }

        // register next task finish within the simulation
        OrcaSeer::Task::TaskControlBlock* next_task
                = this->running->front();

        top_event.time = this->systemTime + (
            next_task->capacity -
            next_task->current_capacity);

        top_event.type = SystemEventType::TASK_FINISHED_IRQ;
        queue->push(top_event);
        //
    } while (this->systemTime < milliseconds);

    return this->systemTime;
}

SimulationTime SimulationEngine::Schedule(
    OrcaSeer::Task::SchedulingAlgorithm* algorithm) {
    // remove running tasks
    std::list<OrcaSeer::Task::TaskControlBlock*>::iterator i;

    OrcaSeer::Task::TaskControlBlock* task;
    for (i = running->begin(); i != running->end(); ++i) {
        task = *i;

        // add elapsed time to current capacity of the task
        task->current_capacity += this->elapsedTime;

        // case A: task has timed out, preempted
        if (task->current_capacity < task->capacity) {
            this->ready->push_back(task);
        // case B: task has finished succeffuly
        } else {
            task->current_capacity = 0;
            task->next_deadline += task->deadline;
            this->blocked->push_back(task);
        }
    }

    // clear running list as tasks were added to other lists
    this->running->clear();

    // move tasks from blocked to the ready queue
    for (i = blocked->begin(); i != blocked->end(); ++i) {
        task = *i;

        // @TODO adjust release time so that tasks wait
        // the next hypercycle to trigger
        this->ready->push_back(task);
    }

    this->blocked->clear();

    // sort ready list (using sort algorithm)
    algorithm->Schedule(this->ready);

    // get first element and push it to the executing queue
    task = *(this->ready->begin());
    this->ready->remove(task);

    this->running->push_back(task);

    PrintTaskLists();

    return this->systemTime;
}

void SimulationEngine::PrintTaskLists() {
    std::list<OrcaSeer::Task::TaskControlBlock*>::iterator i;

    // print lists
    std::cout << "==============================================" << std::endl;
    std::cout << "----- running" << std::endl;

    for (i = running->begin(); i != running->end(); ++i)
        std::cout << (*i)->toString() << std::endl;

    std::cout << "----- ready" << std::endl;

    for (i = ready->begin(); i != ready->end(); ++i)
        std::cout << (*i)->toString() << std::endl;

    std::cout << "----- blocked" << std::endl;

    for (i = blocked->begin(); i != blocked->end(); ++i)
        std::cout << (*i)->toString() << std::endl;

    std::cout << "==============================================" << std::endl;
}

SimulationEngine::~SimulationEngine() {
    delete queue;

    // empty lists
    std::list<OrcaSeer::Task::TaskControlBlock*>::iterator i;

    for (i = running->begin(); i != running->end(); ++i) delete *i;
    for (i = blocked->begin(); i != blocked->end(); ++i) delete *i;
    for (i = ready->begin(); i != ready->end(); ++i) delete *i;

    delete running;
    delete blocked;
    delete ready;
}

}  // namespace OrcaSeer::Simulation
