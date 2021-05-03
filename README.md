# ORCA RT-Bench
![C++ Build](https://github.com/andersondomingues/orca-rt-bench/actions/workflows/c-cpp.yml/badge.svg)![Java Build](https://github.com/andersondomingues//orca-rt-bench/actions/workflows/main.yml/badge.svg) [![CodeFactor](https://www.codefactor.io/repository/github/andersondomingues/orca-rt-bench/badge)](https://www.codefactor.io/repository/github/andersondomingues/orca-rt-bench)

- ORCA RT-Bench is a workbench for modeling and simulating real-time systems. The project is at its initial steps, and is likely to change a lot in the next weeks. No recommended for production-ready stuff.

## The Project includes:
- A task scheduling visualization tool called ORCA-RT-Bench: Kprofiller, which uses the "Kprofiller Tool" developed by Professor Sergio Johann. More information on his work can be found at [his repository](https://github.com/sjohann81).
- A simulation tool which allows to simulate scheduling tasks with a determined algorithm
- data exchange files to facilitate integration with other tools 
- Already implemented build/run setup for Windows 10 and Linux 20.04

## Scheduling Algorithms

### The ORCA-RT-Bench has, for now, two scheduling algorithms implemented 
- RM: The Rate-Monotonic Scheduling Algorithm fixed-priority policy where the higher the frequency (1/period) of a task, the higher is its priority.
- EDF: The Earliest Deadline First Scheuling Algorithm fixed-priority policy where the earlier the deadline of a task, the higher is its priority.

## Build Requirements

### Windows Users
- Install Mingw (https://sourceforge.net/projects/mingw/). When prompted, select "development basics" and wait for it to install. Then, add the 'C:\MinGW\bin' folder to the PATH (hit the Windows button, type environment variables and append it to the existe PATH variable).
- Download https://git-scm.com/ and install with default settings (important!).
- Download lastest Eclipse from https://www.eclipse.org/. Install or unzip it.  

### Linux Users
- Install the following packages: 'build-essentials gcc make git' 
- Download lastest Eclipse from https://www.eclipse.org/. Install or unzip it.

## Runtime Requirements

- Java 15(or most recent version)

## Licensing

- This is free software! See ``LICENSE.MD`` for details. 

## Contact

- Feel free to contact me ([andersondomingues](https://github.com/andersondomingues)), the maintainer of this project: mail to: ti.andersondomingues@gmail.com.

## Collaborators

- João Benno, [his repository](https://github.com/bennoXav)

