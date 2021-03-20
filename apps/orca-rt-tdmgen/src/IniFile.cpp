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
#include "../include/IniFile.hpp"

#include <list>
#include <fstream>
#include <iostream>

namespace OrcaRT::Ini {

IniFileEntry* IniFile::GetEntry(std::string section, std::string entry){

	std::list<IniFileEntry*>::iterator i = this->Begin();
	std::list<IniFileEntry*>::iterator j = this->End();

	for(; i != j; i++){
		if((*i)->section == section && (*i)->entry == entry)
			return *i;
	}

	return nullptr;
}

IniFileEntry* IniFile::SetEntry(std::string section, std::string entry, std::string value){

	IniFileEntry* w = this->GetEntry(section, entry);

	if(w != nullptr){
		w->value = value;

	}else{
		w = new IniFileEntry();
		w->entry = entry;
		w->section = section;
		w->value = value;

		this->entries.push_back(w);
	}

	return w;
}

std::list<IniFileEntry*>::iterator IniFile::Begin(){
	return this->entries.begin();
}

std::list<IniFileEntry*>::iterator IniFile::End(){
	return this->entries.end();
}

IniFile::IniFile(){
	this->entries = std::list<IniFileEntry*>();
}

IniFile::~IniFile(){

	std::list<IniFileEntry*>::iterator i = this->Begin();
	std::list<IniFileEntry*>::iterator j = this->End();

	for(; i != j; i++){
		delete *i;
	}
}

}  // namespace OrcaRT::Ini
