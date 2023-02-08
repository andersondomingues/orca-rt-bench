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

from __future__ import annotations
import sys

from lib.terminal import error
from rtbench.modeling.graph import Graph
from rtbench.io.graph_file_handler import parse_graph_from_file

def main(args: list[str]):
    
    # make sure we have all the arguments
    if len(args) != 4:
        error("Usage:")
        error("python3 -m rtbench <ticks> <app> <algorithm>")
        error("*ticks*: the number of time units to simulate")
        error("*app*: a file name containing an app task graph")
        error("*algorithm*: one of EDF, RM, LST, DM, LLF")
        
    ticks: int = args[0]
    graph_file: str = args[1]
    algorithm: str = args[1]

    graph: Graph = parse_graph_from_file(graph_file)

    algorithms = (
        "EDF" : EarliestDeadlineFirst,
        "RM"  : RateMonotonic,
        "DM"  : DeadlineMonotonic,
        "LST" : LeastSlacktimeFirst,
        "LLF" : LeastLaxityFirst
    )

    alg_class = algorithms[algorithm]
    engine = SingleCoreEngine(graph, alg_class)
    engine.simulate(ticks)

if __name__ == "__main__":
    argv: list[str] = sys.argv[1:]
    main(argv)
