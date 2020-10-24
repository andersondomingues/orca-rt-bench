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
#include <iostream>
#include "main.hpp"
#include "Graph.hpp"
#include "GraphFileHandler.hpp"
#include "TaskScheduler.hpp"
#include "EarliestDeadlineFirst.hpp"

void printGraph(Orca::Graph::Graph* graph) {
    std::list<Orca::Graph::GraphNode*>* nodes = graph->getNodes();
    std::list<Orca::Graph::GraphNode*>::iterator i;

    std::cout << "NODES ========================================" << std::endl;
    Orca::Graph::GraphNodeData data;
    for (i = nodes->begin(); i != nodes->end(); i++) {
        data = *((*i)->getData());
        std::cout << data.id << "\t" << data.name << " "
            << "\t\t\t" << data.cpDever << std::endl;
    }

    std::list<Orca::Graph::GraphEdge*>* edges = graph->getEdges();
    std::list<Orca::Graph::GraphEdge*>::iterator j;

    std::cout << "EDGES ========================================" << std::endl;
    Orca::Graph::GraphEdgeData edata;
    for (j = edges->begin(); j != edges->end(); j++) {
        edata = *((*j)->getData());
        std::cout << (*j)->getFrom()->getData()->name
            << "\t" << (*j)->getTo()->getData()->name
            << edata.dataTransferTime << std::endl;
    }
}

int main(int argc, char** argv) {
    std::string filename = "examples-ogm/waters2019.otm";

    Orca::Graph::Graph* graph;
    graph = Orca::Graph::GraphFileHandler::parseFromFile(filename);

    if (graph == nullptr) {
        std::cout << "could not open file <" << filename << ">" << std::endl;
        return 1;
    }

    // printGraph(graph);

    Orca::Task::TaskScheduler* scheduler
        = new Orca::Task::TaskScheduler(graph);
    Orca::Task::TaskSchedulingAlgorithm* edf
        = new Orca::Task::EarliestDeadlineFirst();

    scheduler->Sim(edf, 100);
}
