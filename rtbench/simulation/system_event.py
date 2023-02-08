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
from enum import Enum


class SystemEventType(Enum):
    SCHEDULER_IRQ = 0
    TASK_FINISHED_IRQ = 1


class SystemEvent:
    def __init__(self: "SystemEvent", time: int, type: SystemEventType):
        self._time = time
        self._type = type

    def __lt__(self: "SystemEvent", target: "SystemEvent"):
        return self._time > target._time

    def __eq__(self: "SystemEvent", target: "SystemEvent"):
        return self._time == target._time and self._type == target.type

    def __str__(self: "SystemEvent"):
        return str(self._time) + str(self._type)
