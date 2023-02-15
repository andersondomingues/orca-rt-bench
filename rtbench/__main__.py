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

from __future__ import annotations
import sys

from rtbench.modeling.graph import Graph
from rtbench.io.graph_file_handler import parse_graph_from_file
from rtbench.io.terminal import info
from rtbench.simulation.single_core_engine import SingleCoreEngine
from rtbench.scheduling.deadline_monotonic import DeadlineMonotonic
from rtbench.scheduling.earliest_deadline_first import EarliestDeadlineFirst
from rtbench.scheduling.least_laxity_first import LeastLaxityFirst
from rtbench.scheduling.least_slack_time import LeastSlackTime
from rtbench.scheduling.rate_monotonic import RateMonotonic


def main(args: list[str]):
    # make sure we have all the arguments
    if len(args) != 3:
        print("Usage: python3 -m rtbench <TICKS> <APPGRAPH> <ALGORITHM>")
        print(
            "Produces a simulation trace of TICKS length for the given APPGRAPH, "
            "applying the ALGORITHM scheduling."
        )
        exit(0)

    ticks: int = int(args[0])
    graph_file: str = args[1]
    algorithm: str = args[2]

    info(f"** Ticks: {ticks}")
    info(f"** Graph: {graph_file}")
    info(f"** Algorithm: {algorithm}")

    graph: Graph = parse_graph_from_file(graph_file)

    info(f"** Parsed data: {graph}")

    algorithms = {
        "EDF": EarliestDeadlineFirst,
        "RM": RateMonotonic,
        "DM": DeadlineMonotonic,
        "LST": LeastSlackTime,
        "LLF": LeastLaxityFirst,
    }

    alg_class = algorithms[algorithm]
    engine = SingleCoreEngine(graph, alg_class)
    engine.simulate(ticks)


if __name__ == "__main__":
    argv: list[str] = sys.argv[1:]
    main(argv)
