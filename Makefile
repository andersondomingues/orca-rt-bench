SOURCEDIR :=src
HEADERDIR :=include
OUTPUTDIR :=bin

# Name of the package
LIBNAME := liborcagraph.a

#TARGET_DEPS := \
#	$(OUTPUTDIR)/GraphNode.o \
#	$(OUTPUTDIR)/GraphEdge.o \
#	$(OUTPUTDIR)/Graph.o \
#	$(OUTPUTDIR)/GraphFileHandler.o \
#	$(OUTPUTDIR)/SimulationEngine.o \
#	$(OUTPUTDIR)/SystemEvent.o \
#	$(OUTPUTDIR)/SystemSimulation.o \
#	$(OUTPUTDIR)/EarliestDeadlineFirst.o
TARGET_DEPS := $(wildcard $(SOURCEDIR)/*.cpp)
TARGET_DEPS := $(subst .cpp,.o, $(TARGET_DEPS))
TARGET_DEPS := $(subst $(SOURCEDIR), $(OUTPUTDIR), $(TARGET_DEPS))

# Add optimization and include flags to the compilation. Compilation 
# optimizations favor performance over code size.
#CXX := g++
CXX := clang++
CXXFLAGS := -std=c++17 -ferror-limit=5 
#-ferror-limit=5
#-fmax-errors=5 
CXXFLAGS += -fsanitize=address -ggdb
#CXXFLAGS += -O3 -march=native -mtune=native 

all: $(OUTPUTDIR)/$(LIBNAME) $(OUTPUTDIR)/main.o
	@$(CXX) $(CXXFLAGS) -I$(HEADERDIR) $(OUTPUTDIR)/main.o -o $(OUTPUTDIR)/test.exe -Lbin -lorcagraph
	@echo "done."
	
#pack file into a static library to be used later
$(OUTPUTDIR)/$(LIBNAME): $(TARGET_DEPS)
	@echo "Packing \"$(LIBNAME)\"..."
	@ar rcs $(OUTPUTDIR)/$(LIBNAME) $(TARGET_DEPS)
#@ar -t $(OUTPUTDIR)/$(LIBNAME)

#compile all classes into %.o files
$(OUTPUTDIR)/%.o: $(SOURCEDIR)/%.cpp $(HEADERDIR)/%.hpp
	@echo "Compiling \"$<\"..."
	@$(CXX) $(CXXFLAGS) $< -o $@ -c -I$(HEADERDIR)

# Remove generated object files and library
clean:
	@rm -rf $(OUTPUTDIR)/*.o $(OUTPUTDIR)/*.a $(OUTPUTDIR)/*.exe