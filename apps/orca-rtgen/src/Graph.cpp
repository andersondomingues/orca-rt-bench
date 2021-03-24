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
#include "../../orca-rtgen/include/Graph.hpp"

#include <list>

#include "../../orca-rtgen/include/GraphEdge.hpp"
#include "../../orca-rtgen/include/GraphNode.hpp"

namespace OrcaSeer::Graph {

Graph::Graph() {
    this->edges = new std::list<GraphEdge*>();
    this->nodes = new std::list<GraphNode*>();
}

int Graph::addNode(GraphNode* node) {
    this->nodes->push_front(node);
    return 0;
}

int Graph::removeNode(GraphNode* node) {
    this->nodes->remove(node);
    return 0;
}

int Graph::addEdge(GraphEdge* edge) {
    GraphNode* node;
    std::list<GraphNode*>* nodes = this->getNodes();
    std::list<GraphNode*>::iterator i;

    int mark = 0;
    for (i = nodes->begin(); i != nodes->end(); i++) {
        if (*i == edge->getTo())
            mark++;
        if (*i == edge->getFrom())
            mark++;
    }

    if (mark == 2) {
        this->edges->push_front(edge);
        return 0;
    }

    return 1;
}

std::list<GraphNode*>* Graph::getNodes() {
    return this->nodes;
}

std::list<GraphEdge*>* Graph::getEdges() {
    return this->edges;
}

Graph::~Graph() {
    std::list<GraphNode*>::iterator i;
    for (i = this->nodes->begin(); i != this->nodes->end(); i++)
        delete *i;

    std::list<GraphEdge*>::iterator j;
    for (j = this->edges->begin(); j != this->edges->end(); j++)
        delete *j;

    delete this->nodes;
    delete this->edges;
}

std::string Graph::ToString() {
    std::stringstream ss;

    std::list<OrcaSeer::Graph::GraphNode*>::iterator i;

    ss << "NODES ========================================" << std::endl;
    OrcaSeer::Graph::GraphNodeData data;
    for (i = nodes->begin(); i != nodes->end(); i++) {
        data = *((*i)->getData());
        ss << data.id << "\t" << data.name << " "
            << "\t\t\t" << data.cpDever << std::endl;
    }

    if (nodes->size() == 0) ss << "none" << std::endl;

    std::list<OrcaSeer::Graph::GraphEdge*>::iterator j;

    ss << "EDGES ========================================" << std::endl;
    OrcaSeer::Graph::GraphEdgeData edata;
    for (j = edges->begin(); j != edges->end(); j++) {
        edata = *((*j)->getData());
        ss << (*j)->getFrom()->getData()->name
            << "\t" << (*j)->getTo()->getData()->name
            << edata.dataTransferTime << std::endl;
    }

    if (edges->size() == 0) ss << "none" << std::endl;

    ss << "==============================================" << std::endl;

    return ss.str();
}

}  // namespace OrcaSeer::Graph
