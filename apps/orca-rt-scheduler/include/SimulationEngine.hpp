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
#ifndef SIM_INCLUDE_SIMULATIONENGINE_HPP_
#define SIM_INCLUDE_SIMULATIONENGINE_HPP_

#include <string>
#include <queue>
#include <list>

#include "Graph.hpp"
#include "SystemEvent.hpp"
#include "SchedulingAlgorithm.hpp"
#include "TaskControlBlock.hpp"

namespace OrcaSeer::Simulation {

typedef uint32_t SimulationTime;

/**
 * This class represents a system simulation.
 */
class SimulationEngine{
 private:
    /**
     * Current system time in milliseconds.
     */
    SimulationTime systemTime;
    SimulationTime elapsedTime;
    /**
     * A queue of <SystemEvent> which is sorted
     * by the time which events occur (ascending).
     */
    std::priority_queue<SystemEvent>* queue;

    /**
     * The scheduler that handles the tasks queues.
     */
    OrcaSeer::Task::SchedulingAlgorithm* algorithm;

    /**
     * Tasks
     */
    std::list<OrcaSeer::Task::TaskControlBlock*>* running;
    std::list<OrcaSeer::Task::TaskControlBlock*>* blocked;
    std::list<OrcaSeer::Task::TaskControlBlock*>* ready;

 public:
    /**
     * Creates a new system simulator. 
     * @param scheduler An instance of <TaskScheduler> 
     *    that implements the tasks state transition 
     *    model for the simulated system
     */
    explicit SimulationEngine(OrcaSeer::Graph::Graph* taskGraph,
     OrcaSeer::Task::SchedulingAlgorithm* algorithm);

    /**
     * Simulate the system for <milliseconds> time.
     * @param milliseconds The amound of time to run the system
     * @returns the time in which the last event ocurred
     */
    SimulationTime Simulate(SimulationTime milliseconds);
    SimulationTime Schedule(OrcaSeer::Task::SchedulingAlgorithm* algo);

    /** 
     * Destructor.
     */
    ~SimulationEngine();

    /**
     * print task lists
     */
    void PrintTaskLists();
};

}  // namespace OrcaSeer::Simulation

#endif  // SIM_INCLUDE_SIMULATIONENGINE_HPP_
