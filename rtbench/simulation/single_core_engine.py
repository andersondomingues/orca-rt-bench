'''
This file is part of project ORCA. More information on the project
can be found at the following repositories at GitHub's website.

http://https://github.com/andersondomingues/orca-sim
http://https://github.com/andersondomingues/orca-software
http://https://github.com/andersondomingues/orca-mpsoc
http://https://github.com/andersondomingues/orca-tools
http://https://github.com/andersondomingues/orca-modeling

Copyright (C) 2018-2020 Anderson Domingues, <ti.andersondomingues@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
'''
from queue import PriorityQueue

from lib.terminal import warn, error, info  # debug, header
from rtbench.modeling.graph import Graph
from rtbench.scheduling_algorithm import SchedulingAlgorithm
from rtbench.simulation.task_control_block import TaskControlBlock
from rtbench.simulation.system_event import SystemEvent, SystemEventType


class SingleCoreEngine():

    SCHED_IRQ_PERIOD = 20

    def __init__(self: "SingleCoreEngine", task_graph: Graph,
                 algorithm: SchedulingAlgorithm):
        self._system_time = 0
        self._queue = PriorityQueue()
        self._running = []
        self._blocked = []
        self._ready = []

        # populate blocked list with tasks from the graph
        for n in task_graph.get_nodes():

            tlb = TaskControlBlock(
                n.get_data().get_id(),
                n.get_data().get_name(),
                n.get_data().get_period(),
                n.get_data().get_capacity(),
                n.get_data().get_deadline()
            )
            self._blocked.append(tlb)

        self._algorithm = algorithm

    def simulate(self: "SingleCoreEngine", time: int):

        irq_event : SystemEvent = SystemEvent(0, SystemEventType.SCHEDULER_IRQ)
        self._queue.push(irq_event)

        iterations = 0
        start_time = 0

        # open file >>>>
        while (self._system_time < time):

            top_event = self._queue.top()
            self._queue.pop()

            self._elapsed_time = top_event.time - self._system_time
            self._system_time += self._elapsed_time

            # warning
            if top_event._type == SystemEventType.TASK_FINISHED_IRQ:
                warn(str(self._system_time) + ": task finished")
            else:
                warn(str(self._system_time) + ": scheduled irq")

            # If the top of the queue is a task finish syscall, we must
            # put the finished task into the blocked queue and process
            # a new task to take its place
            self.schedule(self._algorithm)

            # Next event is the scheduler interruption
            if top_event.type == SystemEventType.SCHEDULER_IRQ:
                # remove all events from the simulation queue; since the
                # scheduler_irq has been removed, only the event for the
                # running task remains
                while len(self._queue) > 0:
                    self._queue.pop()

                # register the interruption
                irq_event._time = self._system_time + self._SCHED_IRQ_PERIOD
                self._queue.push(irq_event)

            # register next task finish within the simulation
            next_task = self._running[0]

            info(iterations, start_time, self._system_time, self._system_time)
            start_time = self._system_time
            iterations += 1

            # slack time
            if next_task is not None:
                top_event._time = self._system_time + (
                    next_task._capacity - next_task._current_capacity)

                top_event.type = SystemEventType.TASK_FINISHED_IRQ
                self._queue.push(top_event)
                warn("running task")

                info(iterations, next_task._period, next_task._capacity,
                     next_task._deadline)
            else:
                warn("slack time")

            self.print_task_list()
            return self._system_time

    def schedule(self: "SingleCoreEngine", algorithm: SchedulingAlgorithm):

        for t in self._running:
            # add elapsed time to current capacity of the task
            t._ccurrent_capacity += self._elapsed_time

            # case A: task has timed out, preempted
            if t._current_capacity < t._capacity:
                self._ready.push(t)

            # case B: task has finished succeffuly
            else:
                t._release_time += t._period
                t._current_capacity = 0
                t._next_deadline += t._deadline
                self._blocked.push(t)

        # clear running list as tasks were added to other lists
        self._running.clear()

        freed = []

        # move tasks from blocked to the ready queue
        for t in self._blocked:
            if t._release_time <= self._systemTime:
                self._ready.push(t)
                freed.append(t)

        # remove freed tasks from blocked list
        for t in freed:
            self._blocked.remove(t)

        # sort ready list (using sort algorithm)
        self._algorithm.schedule(self._ready)

        # get first element and push it to the executing queue (if any)
        if len(self._ready) != 0:
            task = self._ready[0]
            self._ready.remove(task)
            self._running.append(task)

            if task._next_deadline < self._system_time:
                error("missed deadline!")

        return self._system_time

    def print_task_list(self: "SingleCoreEngine"):

        # print lists
        print("==============================================")
        print("----- running")
        for t in self._running:
            print(str(t))

        print("----- ready")
        for t in self._ready:
            print(str(t))

        print("----- blocked")
        for t in self._blocked:
            print(str(t))

        print("==============================================")
