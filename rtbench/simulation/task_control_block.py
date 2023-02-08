"""
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
"""


class TaskControlBlock:
    def __eq__(self: "TaskControlBlock", target: "TaskControlBlock"):
        return self._id == target._id

    def __init__(
        self: "TaskControlBlock",
        id: int,
        name: str,
        period: int,
        capacity: int,
        deadline: int,
    ):
        self._id = id
        self._name = name
        self._period = period
        self._capacity = capacity
        self._deadline = deadline

        self._current_capacity = 0
        self._release_time = 0
        self._next_deadline = self._deadline

    def __str__(self: "TaskControlBlock"):
        ss = "[" + self._id + "] " + self._name
        ss += ", p:" + str(self._period)
        ss += ", c:" + str(self._current_capacity) + "/" + str(self._capacity)
        ss += ", d:" + str(self._next_deadline) + "/" + str(self._deadline)
        return ss
