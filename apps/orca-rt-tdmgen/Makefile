SOURCEDIR :=src
HEADERDIR :=include
OUTPUTDIR :=bin
EXENAME :=sim.exe

# Name of the package
LIBNAME := liborcagraph.a

TARGET_DEPS := $(wildcard $(SOURCEDIR)/*.cpp)
TARGET_DEPS := $(subst .cpp,.o, $(TARGET_DEPS))
TARGET_DEPS := $(subst $(SOURCEDIR), $(OUTPUTDIR), $(TARGET_DEPS))

# Add optimization and include flags to the compilation. Compilation 
# optimizations favor performance over code size.
CXX := g++
#CXX := clang++
CXXFLAGS := -std=c++17 -fmax-errors=5  
#-ferror-limit=5

#NOTE: lasan not supported on windows
CXXFLAGS += -ggdb
#-fsanitize=address
#CXXFLAGS += -O3 -march=native -mtune=native 

all: $(TARGET_DEPS) $(OUTPUTDIR)/main.o
	@$(CXX) $(CXXFLAGS) -I$(HEADERDIR) $(TARGET_DEPS) -o $(OUTPUTDIR)/$(EXENAME)

run:
	../bin/sim.exe 20 ../dist/foundations-table3.2.ogm

#compile all classes into %.o files
$(OUTPUTDIR)/%.o: $(SOURCEDIR)/%.cpp $(HEADERDIR)/%.hpp
	@echo "Compiling \"$<\"..."
	@$(CXX) $(CXXFLAGS) $< -o $@ -c -I$(HEADERDIR)

# Remove generated object files and library
clean:
	@rm -rf $(TARGET_DEPS) $(OUTPUTDIR)/$(EXENAME)