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
#include "../include/IniFileHandler.hpp"

#include <list>
#include <fstream>
#include <iostream>

#include "GraphEdge.hpp"
#include "GraphNode.hpp"
#include "Graph.hpp"


#define ENDL '\n'

namespace OrcaSeer::Graph {

#define IGNORE 0
#define FIND_NODE_HEADER 1
#define PARSE_NODES 2
#define FIND_EDGE_HEADER 3
#define PARSE_EDGES 4

#define NODE_HEADER "[nodes]"
#define EDGE_HEADER "[edges]"

//Graph* GraphFileHandler::parseFromFile(std::string filename) {
//    Graph* graph = new Graph();
//
//    std::ifstream file;
//    file.open(filename);
//
//    int state = IGNORE;
//
//    if (!file.is_open()) return nullptr;
//
//    std::string line;
//    std::stringstream ss;
//
//    while (!file.eof() && std::getline(file, line)) {
//        if (line[0] == '#' || line[0] == ENDL || line == "")
//            continue;
//
//        if (line == NODE_HEADER) {
//            state = PARSE_NODES;
//            continue;
//        } else if (line == EDGE_HEADER) {
//            state = PARSE_EDGES;
//            continue;
//        }
//
//        ss = std::stringstream(line);
//
//        switch (state) {
//            case IGNORE:
//            case FIND_NODE_HEADER:
//                break;
//
//            case PARSE_NODES: {
//                GraphNode* node = new GraphNode();
//                ss >> node->getData()->id;
//                ss >> node->getData()->name;
//                ss >> node->getData()->cpDever;
//                ss >> node->getData()->cpA56;
//                ss >> node->getData()->cpGPU;
//                ss >> node->getData()->deadline;
//                ss >> node->getData()->period;
//                graph->addNode(node);
//            } break;
//
//            case FIND_EDGE_HEADER:
//                break;
//
//            case PARSE_EDGES: {
//                GraphEdge* edge = new GraphEdge();
//                int from, to;
//                ss >> from;
//                ss >> to;
//                ss >> edge->getData()->dataTransferTime;
//
//                GraphNode *nfrom, *nto;
//                std::list<GraphNode*>* nodes = graph->getNodes();
//                std::list<GraphNode*>::iterator i;
//                for (i = nodes->begin(); i != nodes->end(); i++) {
//                    if ((*i)->getData()->id == from) {
//                        edge->setFrom(*i);
//                    } else if ((*i)->getData()->id == to) {
//                        edge->setTo(*i);
//                    }
//                }
//                graph->addEdge(edge);
//            } break;
//
//            default:
//                break;
//        }
//    }
//
//    file.close();
//    return graph;
//}
//
//void GraphFileHandler::saveToFile(std::string filename, Graph* g) {
//    return;
//}

}  // namespace OrcaSeer::Graph
