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
#include <TaskControlBlock.hpp>

#include <sstream>

namespace Orca::Task {

inline bool TaskControlBlock::operator==(const TaskControlBlock& b) const {
    return this->id == b.id;
}

TaskControlBlock::TaskControlBlock(uint32_t id, std::string name,
 uint32_t period, uint32_t capacity, uint32_t deadline) {
    this->id = id;
    this->name = name;
    this->period = period;
    this->capacity = capacity;
    this->deadline = deadline;
}

std::string TaskControlBlock::toString() {
    std::stringstream ss;
    ss << "[" << id << "]" << name << "(d:"
        << deadline << ", c:"
        << capacity << ", p:"
        << period << ")";
    return ss.str();
}

}  // namespace Orca::Task
