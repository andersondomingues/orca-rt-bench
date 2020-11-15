SOURCEDIR :=src
HEADERDIR :=include
OUTPUTDIR :=../bin
EXENAME := viewer.exe

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

all: $(TARGET_DEPS) $(OUTPUTDIR)/main.o
	@$(CXX) $(CXXFLAGS) -I$(HEADERDIR) $(OUTPUTDIR)/main.o -o $(OUTPUTDIR)/test.exe -L$(OUTPUTDIR) -lorcagraph

#compile all classes into %.o files
$(OUTPUTDIR)/%.o: $(SOURCEDIR)/%.cpp $(HEADERDIR)/%.hpp
	@echo "Compiling \"$<\"..."
	@$(CXX) $(CXXFLAGS) $< -o $@ -c -I$(HEADERDIR)

# Remove generated object files and library
clean:
	@rm -rf $(OUTPUTDIR)/*.o $(OUTPUTDIR)/*.a $(OUTPUTDIR)/*.exe