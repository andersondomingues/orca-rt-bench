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
#ifndef SIM_INCLUDE_KPROFILERFILEHANDLER_HPP_
#define SIM_INCLUDE_KPROFILERFILEHANDLER_HPP_

#include <string>
#include <list>

namespace OrcaSeer::Kprofiler {

struct KprofilerLineData{
    int id;
    int period;
    int capacity;
    int deadline;
    int startTime;
    int name1;
    int finish;
    int name2;
    int finish2;
};

class KprofilerFileHandler {
 private:
    std::list<KprofilerLineData> data;

 public:
    KprofilerFileHandler();

    /**
     * Removes all entries from the buffer
     */
    void clean();

    /**
     * Appeds one entry to the buffer
     */
    void append(int id, int startTime, int finish, int finish2);

    /**
     * Save current buffer to file
     */
    bool saveToFile(std::string filename);
};

}  // namespace OrcaSeer::Graph

#endif  // SIM_INCLUDE_KPROFILERFILEHANDLER_HPP_
