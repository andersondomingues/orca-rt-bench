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
 * Copyright (C) 2018-2021 Anderson Domingues, <ti.andersondomingues@gmail.com>
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

#include "GraphFileHandler.hpp"

#include "GraphEdge.hpp"
#include "GraphNode.hpp"
#include "GraphNodeData.hpp"

using namespace Orca::RTGen;

int main(int argc, char** argv){

	std::string taskGraphFile, mappingFile;

	try {
		if (argc != 2) throw std::runtime_error("");
		taskGraphFile = std::string(argv[1]);
	} catch (std::exception& e) {
		std::cout << "Usage:" << std::endl;
		std::cout << "\t" << std::string(argv[0]);
		std::cout << " <task-graph>" << std::endl;
		std::cout << std::flush;
		return -1;
	}

    std::cout << "===> Step 1 - Parsing entered file..."
    		<< std::endl << std::endl;

    Graph* taskGraph = GraphFileHandler::loadFromFile(taskGraphFile);
    std::cout << taskGraph->ToString() << std::endl;

//    std::cout << "===> Step 2 - Generate flows..."
//       		<< std::endl << std::endl;
////
//    std::map<int, NetworkFlow>

    delete taskGraph;
}
