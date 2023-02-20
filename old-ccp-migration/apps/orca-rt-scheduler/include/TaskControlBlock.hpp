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
#ifndef SIM_INCLUDE_TASKCONTROLBLOCK_HPP_
#define SIM_INCLUDE_TASKCONTROLBLOCK_HPP_

#include <string>

namespace OrcaSeer::Task {

class TaskControlBlock{
 /* NOTE: Some attributes were set as public as it may be cumbersome
 to access them via tradicional get/set interfaces. Since tlb are not
 exposed to outside the scheduler, it should not be a security problem */
 public:
    // task RT characterization (must be supplied)
    uint32_t period;    // ms < frequency that task is released
    uint32_t deadline;  // ms < maximum allowed execution time
    uint32_t capacity;  // ms < required processor time

    // "user-level" entered information (must be supplied)
    int32_t id;          // task id, informed by the user
    std::string name;    // task name, informed by the user

    // calculated information (generated by the system during runtime)
    uint32_t current_capacity;  // the amount of time that the task processed
    uint32_t next_deadline;     // next time the task will reach its deadline
    uint32_t release_time;      // stores the next release time
    // methods
    TaskControlBlock(uint32_t id, std::string name,
        uint32_t period, uint32_t capacity, uint32_t deadline);

    // comparator implementation (tasks are identified by ID)
    bool operator==(const TaskControlBlock& b) const;

    std::string toString();
};

}  // namespace OrcaSeer::Task

#endif  // SIM_INCLUDE_TASKCONTROLBLOCK_HPP_