'''
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
'''

#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "KprofilerFileHandler.hpp"

namespace OrcaSeer::Kprofiler {

KprofilerFileHandler::KprofilerFileHandler() {
    this->data = std::list<KprofilerLineData>();
}

void KprofilerFileHandler::clean() {
    this->data.clear();
}

void KprofilerFileHandler::append(
    int id, int startTime, int finish, int finish2) {

    KprofilerLineData line;
    line.id = id;
    line.startTime = startTime;
    line.finish = finish;
    line.finish2 = finish2;

    this->data.push_front(line);
}

bool KprofilerFileHandler::saveToFile(std::string filename) {
    std::ofstream file;
    file.open(filename);

	if (!file.is_open()){ 
	return false;
	}
    // sort entries by starting time
    this->data.sort([]
        (const KprofilerLineData e1, const KprofilerLineData e2){
        return e1.startTime < e2.startTime;
    });

    std::stringstream ss;

    std::list<KprofilerLineData>::iterator i;
    for (i = this->data.begin(); i != this->data.end(); ++i) {
        //
        if (i == data.end() || i == data.begin()) continue;

        KprofilerLineData line =i;
        ss << line.id << " " << line.period << " " << line.capacity;
        ss << " " << line.deadline << " " << (line.startTime1000) << " ? ";
        ss << (line.finish1000) << " ? " << (line.finish21000);
        ss << std::endl;
    }

    file << ss.str();
    file.close();
    return true;
}

}  // namespace OrcaSeer::Kprofiler
