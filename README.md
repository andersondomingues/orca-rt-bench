# ORCA RT-Bench
![C++ Build](https://github.com/andersondomingues/orca-rt-bench/actions/workflows/c-cpp.yml/badge.svg) ![Java Build](https://github.com/andersondomingues//orca-rt-bench/actions/workflows/main.yml/badge.svg) [![CodeFactor](https://www.codefactor.io/repository/github/andersondomingues/orca-rt-bench/badge)](https://www.codefactor.io/repository/github/andersondomingues/orca-rt-bench)

- ORCA RT-Bench is a workbench for modeling and simulating real-time scheduling algoritmos. The project is at its initial steps, and is likely to change a lot in the next weeks. No recommended for production-ready projects.

## What is included?
- A task scheduling visualization tool, based on the Kprofiler tool, by Professor Sergio Johann. More information on his work can be found at [his repository](https://github.com/sjohann81).
- A backend simulation tool which allows to simulate tasks sets with different scheduling algorithms
- Data exchange files to facilitate integration with other tools 
- Already implemented build/run setup for Windows 10 and Linux (tested in Ubuntu 20.04 and Debian 9/10 enviroments)

## Scheduling Algorithms

ORCA RT-Bench implements two scheduling algorithms implemented (more to come in the future)
- RM: The Rate-Monotonic Scheduling Algorithm fixed-priority policy where the higher the frequency (1/period) of a task, the higher is its priority.
- EDF: The Earliest Deadline First Scheuling Algorithm fixed-priority policy where the earlier the deadline of a task, the higher is its priority.

## Build Requirements

### Windows Users
- Install Mingw (https://sourceforge.net/projects/mingw/). When prompted, select "development basics" and wait for it to install. Then, add the 'C:\MinGW\bin' folder to the PATH (hit the Windows button, type environment variables and append it to the existe PATH variable).
- Download https://git-scm.com/ and install with default settings (important!).
- (optional) Download lastest Eclipse from https://www.eclipse.org/. Install or unzip it.  

### Linux Users
- Install the following packages: 'build-essentials gcc make git' 
- (optional) Download lastest Eclipse from https://www.eclipse.org/. Install or unzip it.

## Runtime Requirements

- JavaSE (most recent version)

## Licensing

- This is free software! See ``LICENSE.MD`` for details. 

## Contact

- Feel free to contact me ([andersondomingues](https://github.com/andersondomingues)), the maintainer of this project: mail to: ti.andersondomingues@gmail.com.

## Collaborators

- João Benno, [his repository](https://github.com/bennoXav)

