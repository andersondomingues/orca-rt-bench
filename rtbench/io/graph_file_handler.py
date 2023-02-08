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
from enum import Enum
from rtbench.modeling.graph import Graph, GraphEdge, GraphNode

# define ENDL '\n'


class GraphParseState(Enum):
    IGNORE = 0
    FIND_NODE_HEADER = 1
    PARSE_NODES = 2
    FIND_EDGE_HEADER = 3
    PARSE_EDGES = 4


def parse_graph_from_file(file_name: str) -> Graph:

    NODE_HEADER = "[nodes]"
    EDGE_HEADER = "[edges]"

    graph = Graph()

    with open(file_name) as file:
        state: GraphParseState = GraphParseState.IGNORE

        line: str
        ss: str

        while True:
            line = file.readline()

            if not line:
                break

            if line[0] == '#' or line[0] == '\n' or line == "":
                continue

            if line == NODE_HEADER:
                state = GraphParseState.PARSE_NODES
                continue
            elif line == EDGE_HEADER:
                state = GraphParseState.PARSE_EDGES
                continue

            if state in [GraphParseState.IGNORE,
                         GraphParseState.FIND_NODE_HEADER,
                         GraphParseState.FIND_EDGE_HEADER]:
                pass
            elif state == GraphParseState.PARSE_NODES:
                lline = line.split('t')
                lline.remove('')

                graph.add_node(GraphNode({
                    "id" : lline[0],
                    "name" : lline[0],
                    "period" : lline[0],
                    "capacity" : lline[0],
                    "deadline" : lline[0]
                }))

            elif state == GraphParseState.PARSE_EDGES:

                lline = line.split('\t')
                lline.remove('')

                node_from: GraphNode
                node_to: GraphNode

                for nn in graph.get_nodes():
                    if nn.get_data().id == lline[0]:
                        node_from = nn
                    elif nn.get_data().id == lline[1]:
                        node_to = nn

                edge = GraphEdge(node_from, node_to, lline[2])
                graph.add_edge(edge)

        return graph
