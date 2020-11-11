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
#ifndef GRAPHEDGE_HPP_
#define GRAPHEDGE_HPP_

#include <string>

#include "GraphEdgeData.hpp"
#include "GraphNode.hpp"

namespace OrcaSeer::Graph {

class GraphNode;

class GraphEdge{
 private:
    GraphNode* from;
    GraphNode* to;
    GraphEdgeData data;

 public:
    GraphEdge();
    ~GraphEdge();
    void setFrom(GraphNode* node);
    void setTo(GraphNode* node);
    GraphNode* getFrom();
    GraphNode* getTo();
    GraphEdgeData* getData();
};

}  // namespace OrcaSeer::Graph

#endif  // GRAPHEDGE_HPP_
