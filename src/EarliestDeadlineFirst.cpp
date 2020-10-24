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
#include "EarliestDeadlineFirst.hpp"


namespace Orca::Task {

EarliestDeadlineFirst::EarliestDeadlineFirst() {
    // add all tasks to the tlb
}

EarliestDeadlineFirst::~EarliestDeadlineFirst() {
    //
}

bool earlist_deadline_first(
    const TaskSchedulerEvent& e1, const TaskSchedulerEvent& e2) {
    return e1.data.deadline < e2.data.deadline;
}

// schedule -> sort tasks
void EarliestDeadlineFirst::Schedule(
    std::list<TaskSchedulerEvent>* ready,
    std::list<TaskSchedulerEvent>* blocked,
    std::list<TaskSchedulerEvent>* running) {

    // sort list of ready tasks by earliest deadline
    ready->sort([]
        (const TaskSchedulerEvent& e1, const TaskSchedulerEvent& e2) {
            return e1.data.next_deadline < e2.data.next_deadline;
    });

    std::list<TaskSchedulerEvent>::iterator i;
    for (i = ready->begin(); i != ready->end(); i++) {
        std::cout << "\t" << (*i).data.next_deadline
            << ":" << (*i).data.name << std::endl;
    }
}

// send tasks to corresponding cpu
void EarliestDeadlineFirst::Dispatch(
    std::list<TaskSchedulerEvent>* ready,
    std::list<TaskSchedulerEvent>* blocked,
    std::list<TaskSchedulerEvent>* running) {
    //
    TaskSchedulerEvent e;
    e = ready->front();

    ready->remove(e);
    running->push_front(e);
}

}  // namespace Orca::Task
