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


class GraphNode:
    def __init__(self: "GraphNode", data: any):
        self._data = data

    def get_data(self: "GraphNode"):
        return self._data

    def __eq__(self: "GraphNode", target: "GraphNode"):
        return self._data == target._data

    def __str__(self: "GraphNode"):
        return str(self._data)


class GraphEdge:
    def __init__(self: "GraphEdge", nfrom: GraphNode, nto: GraphNode, data: any):
        self._from = nfrom
        self._to = nto
        self._data = data

    def get_from(self: "GraphEdge"):
        return self._from

    def get_to(self: "GraphEdge"):
        return self._to

    def get_data(self: "GraphEdge"):
        return self._data

    def __eq__(self: "GraphEdge", target: "GraphEdge"):
        return self._from == target._from and self._to == target._to


class Graph:
    def __init__(self: "Graph"):
        self._edges: list[GraphEdge] = []
        self._nodes: list[GraphNode] = []

    def add_node(self: "Graph", node: GraphNode):
        self._nodes.append(node)

    def remove_node(self: "Graph", node: GraphNode):
        self._nodes.remove(node)

    def add_edge(self: "Graph", nfrom: GraphNode, nto: GraphNode):
        # TODO: check whether nodes belong to the graph
        # TODO: check for duplicates
        edge = GraphEdge(nfrom, nto)
        self._edges.append(edge)

    def get_nodes(self: "Graph"):
        # Muttable? if not, return a copy of the list
        return self._nodes

    def get_edges(self: "Graph"):
        return self._edges

    def remove_edge(self: "Graph", nfrom: GraphNode, nto: GraphNode):
        edge = GraphEdge(nfrom, nto)
        self._edges.remove(edge)

    def __str__(self: "Graph"):
        ss = "{nodes: "
        if len(self._nodes) == 0:
            ss += "None\n"
        else:
            ss += "[" + ", ".join([str(x) for x in self._nodes]) + "]"

        ss += ", edges: "
        if len(self._edges) == 0:
            ss += "None\n"
        else:
            ss += "[" + ",".join([str(x) for x in self._edges]) + "]"
        ss += " }"
        return ss
