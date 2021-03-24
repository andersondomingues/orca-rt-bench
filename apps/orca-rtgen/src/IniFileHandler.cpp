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
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "IniFileHandler.hpp"
#include "IniFile.hpp"

namespace Orca::RTGen {

#define ENDL '\n'

IniFile* IniFileHandler::LoadFromFile(std::string filename) {

	std::ifstream file;
	std::string line, section, entry, value;

	file.open(filename);
	if (!file.is_open()) return nullptr;

	// create new inifile
	IniFile* ifile = new IniFile();

	// scan lines
	while (!file.eof() && std::getline(file, line)) {

		// skip empty or comment lines
		if (line[0] == '#' || line[0] == ENDL || line == "")
			continue;

		// select current section
		if (line[0] == '[') {
			section = line.substr(1, line.length() - 1);
			continue;
		}

		// parse entry
		std::stringstream ss = std::stringstream(line);
		ss >> entry;
		ss >> value;

		// add entry to the list
		ifile->SetEntry(section, entry, value);
	}

	file.close();
	return ifile;
}

void IniFileHandler::SaveToFile(std::string filename, IniFile* ifile){

	std::ofstream file;
	std::stringstream ss;

	file.open(filename);
	if (!file.is_open()) return;

	std::list<IniFileEntry*>::iterator i = ifile->Begin();
	std::list<IniFileEntry*>::iterator j = ifile->End();

	std::string curr_section;

	for(; i != j; i++){

		IniFileEntry* entry = *i;

		// add header for new sections
		if(entry->section != curr_section){
			curr_section = entry->section;
			file << "[" << curr_section << "]";
		}


		file << entry->section << " " << entry->value;

	}

}

}  // namespace Orca::RTGen
