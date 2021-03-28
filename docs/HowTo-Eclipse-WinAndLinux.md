# Project Setup for Eclipse IDE

## Requirements

### Windows Users
- Install Mingw (https://sourceforge.net/projects/mingw/). When prompted, select "development basics" and wait for it to install. Then, add the 'C:\MinGW\bin' folder to the PATH (hit the Windows button, type environment variables and append it to the existe PATH variable).
- Download https://git-scm.com/ and install with default settings (important!).
- Download lastest Eclipse from https://www.eclipse.org/. Install or unzip it.  

### Linux Users
- Install the following packages: 'build-essentials gcc make git' 
- Download lastest Eclipse from https://www.eclipse.org/. Install or unzip it.

## Configuring the project

- Clone the repo from git (should be available from https://github.com/andersondomingues/orca-rt-bench)
- Start Eclipse. When prompted, select "c++ development" (not embedded dev, just the first one). 
- Go to "File -> New -> Makefile Project with Existing Code". Give the project a name of your choice, select the root folder of the cloned repository (the one where the README.md file resides), and select "MinGW GCC" as the toolchain. Hit finish.
- Now, left click on project's root folder on your left, then go to "Project -> Properties". Look for "C/C++ Build". In the "Builder Settings" tab, make sure that "Generate Makefiles automatically" is unchecked, to do that, you may need to go to "Tool chain editor", on the "C/C++ Build" tab, and change "Current builder" to "Gnu Make Builder".
- To build the project, right click on project's root folder and select "build". The same applies for cleaning.



## Submiting code back to GitHub

- Code must be submited as pull requests (see https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/about-pull-requests).