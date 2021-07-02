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
#include <exception>

#include "main.hpp"

#include "Graph.hpp"
#include "GraphFileHandler.hpp"
#include "SimulationEngine.hpp"
#include "RateMonotonic.hpp"
#include "EarliestDeadlineFirst.hpp"
#include "LeastSlackTime.hpp"
#include "RateMonotonic.hpp"
#include "DeadlineMonotonic.hpp"
#include "LeastLaxityFirst.hpp"
int main(int argc, char** argv) {
    //
    int ticks;
    std::string graphFile;
<<<<<<< Updated upstream
	std::string schedulingAlgorithmName;
    // check on arguments
    try {
        if (argc != 4) throw std::runtime_error("");

        ticks = std::stoi(argv[1], nullptr, 10);
        graphFile = std::string(argv[2]);
		schedulingAlgorithmName = std::string(argv[3]);
    } catch (std::exception& e) {
        std::cout << "Usage:" << std::endl;
        std::cout << "\t" << std::string(argv[0]);
        std::cout << " <ticks> <graph file> [<algorithm>=EDF or RM or LST]" << std::endl;
=======
    std::string schedulingAlgorithm;
    // check on arguments
    try {
        if (argc != 4) throw std::runtime_error("");
        ticks = std::stoi(argv[1], nullptr, 10);
        graphFile = std::string(argv[2]);
        schedulingAlgorithm = std::string(argv[3]);
    } catch (std::exception& e) {
        std::cout << "Usage:" << std::endl;
        std::cout << "\t" << std::string(argv[0]);
        std::cout << " <ticks> <graph file> <algorithm (EDF or RM or LST)>" << std::endl;
>>>>>>> Stashed changes
        std::cout << std::flush;
        return -1;
    }

    OrcaSeer::Graph::Graph* graph;
    graph = OrcaSeer::Graph::GraphFileHandler::parseFromFile(graphFile);

    if (graph == nullptr) {
        std::cout << "could not open file <" << graphFile << ">" << std::endl;
        return -1;
    }

    OrcaSeer::Task::SchedulingAlgorithm* edf;

<<<<<<< Updated upstream
    OrcaSeer::Task::SchedulingAlgorithm* edf; 
	
	// Scheduling Algorthm check
	if(schedulingAlgorithmName == "RM"){
		
		edf = new OrcaSeer::Task::RateMonotonic();
	
	}else if(schedulingAlgorithmName == "EDF"){
		
		 edf = new OrcaSeer::Task::EarliestDeadlineFirst();
		 
	}else if(schedulingAlgorithmName == "LST"){
		
		 edf = new OrcaSeer::Task::LeastSlackTime();
		 
	}
	
=======
    std::cout << graph->ToString() << std::endl;

    if(schedulingAlgorithm == "EDF"){
		edf  = new OrcaSeer::Task::EarliestDeadlineFirst();
    std::cout << "testebenno" << std::endl;
    }
    if(schedulingAlgorithm == "LST"){
		edf = new OrcaSeer::Task::LeastSlackTime();
    }
    if(schedulingAlgorithm == "RM"){   
		edf  = new OrcaSeer::Task::RateMonotonic();
    }
     if(schedulingAlgorithm == "DM"){   
		edf  = new OrcaSeer::Task::DeadlineMonotonic();
    }
     if(schedulingAlgorithm == "LSF"){
     		edf  = new OrcaSeer::Task::LeastLaxityFirst();
         }
>>>>>>> Stashed changes
    OrcaSeer::Simulation::SimulationEngine* engine
        = new OrcaSeer::Simulation::SimulationEngine(graph, edf);

    engine->Simulate(ticks);  // milliseconds

    delete engine;
    delete edf;
    delete graph;
}
