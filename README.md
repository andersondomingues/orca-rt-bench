# ORCA RT-Bench
- ORCA RT-Bench is a workbench for modeling and simulating real-time scheduling algoritms. For know, we're focusing on single-core algorithms such as EDF and RM. we'll add algorithms (including algorithms for multi-core) as the project grows mature. 

## Project Status
- We're currently migrating our codebase from C++/JAVA to python.

## What is included (old cpp migration folder)?
- A task scheduling visualization tool, based on the Kprofiler tool, by Professor Sergio Johann. More information on his work can be found at [his repository](https://github.com/sjohann81).
- A backend simulation tool which allows to simulate tasks sets with different scheduling algorithms
- Data exchange files to facilitate integration with other tools 
- Already implemented build/run setup for Windows 10 and Linux (tested in Ubuntu 20.04 and Debian 9/10 enviroments)

## Scheduling Algorithms

- The Rate-Monotonic scheduling (RM), fixed-priority policy, higher the frequency of the task, higher its priority.
- Earliest Deadline First (EDF) scheduling, fixed-priority policy, earlier the deadline of a task, the higher is its priority.

## Runtime Requirements

- Python 3.8+ (recommended Pypy 3.8+). 
- pip (use `python3 -m pip install -r requirements.txt` to install requirements)

## Licensing

- This is free software! See ``LICENSE.MD`` for details. 

## Contact

- Feel free to contact me ([andersondomingues](https://github.com/andersondomingues)), the maintainer of this project: mail to: ti.andersondomingues@gmail.com.

## Collaborators

- [Anderson Domingues](https://github.com/andersondomingues)
- [João Benno](https://github.com/bennoXav)
- [Lucas Damo](https://github.com/LucasDamo22)

