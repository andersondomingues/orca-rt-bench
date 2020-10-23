SOURCEDIR :=src
HEADERDIR :=include
OUTPUTDIR :=bin

# Name of the package
LIBNAME := liborcagraph.a

TARGET_DEPS := \
	$(OUTPUTDIR)/GraphNode.o \
	$(OUTPUTDIR)/GraphEdge.o \
	$(OUTPUTDIR)/Graph.o \
	$(OUTPUTDIR)/GraphFileHandler.o \
	$(OUTPUTDIR)/TaskScheduler.o \
	$(OUTPUTDIR)/TaskSchedulingAlgorithm.o \
	$(OUTPUTDIR)/EarliestDeadlineFirst.o
	
# Add optimization and include flags to the compilation. Compilation 
# optimizations favor performance over code size.
CXX := g++
CXXFLAGS := -O3 -march=native -mtune=native -std=c++17 -fmax-errors=5

all: $(OUTPUTDIR)/$(LIBNAME) $(OUTPUTDIR)/main.o
	$(CXX) $(CXXFLAGS) -I$(HEADERDIR) $(OUTPUTDIR)/main.o -o $(OUTPUTDIR)/test.exe -Lbin -lorcagraph
	
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