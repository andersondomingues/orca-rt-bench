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
#include "../../orca-rtgen/include/GraphNode.hpp"

#include "../../orca-rtgen/include/GraphEdge.hpp"
#include "../../orca-rtgen/include/GraphNodeData.hpp"

namespace OrcaSeer::Graph {

GraphNode::GraphNode() {
    this->from = nullptr;
    this->to = nullptr;
    this->data = GraphNodeData();
}

GraphNode::~GraphNode() {
    // nothing
}

GraphNodeData* GraphNode::getData() {
    return &(this->data);
}

std::list<GraphEdge>* GraphNode::getTo() {
    return this->to;
}

std::list<GraphEdge>* GraphNode::getFrom() {
    return this->from;
}

}  // namespace OrcaSeer::Graph
