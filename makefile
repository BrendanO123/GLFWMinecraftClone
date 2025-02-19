#Flags and Compilers
CXX = g++
CC = gcc
CXXFLAGS = -Wall -g
CPPVERSION = -std=c++17

#.out file name
TARGET = build.out
VERSION = .0.1

#Framworks for .out file
F = -framework
FRAMEWORKS = $(F) Cocoa $(F) OpenGL $(F) IOKit

#include directories, libraries, and library directory
INCLUDE = Dependencies/include -I$(SRC_PATH) -IDependencies/include/imgui
LIB = glfw3
LIB_PATH = Dependencies/lib


#source .cpp files
SRC_PATH = MinecraftClone/src/
MAIN = Application
TESTS_RAW_CPP = LOCRaycastingTest.cpp
SRCS_RAW_CPP = LOCShaders.cpp LOCBlock.cpp LOCChunk.cpp LOCCamera.cpp LOCWorld.cpp LOCWorldGen.cpp LOCChunkData.cpp LOCStructure.cpp LOCFractal.cpp LOCNoise.cpp LOCUnitVoxelRaycaster.cpp LOCPlayer.cpp LOCBlockHighlighter.cpp
SRCS_CPP = $(SRCS_RAW_CPP:LOC%=$(SRC_PATH)%) #LOC -> path to source files
TESTS_CPP = $(TESTS_RAW_CPP:LOC%=$(SRC_PATH)%) #LOC -> path to source files

#source .h files (same path)
SRCS_RAW_H = LOCShaders.h LOCBlocks.h LOCBlock.h LOCChunk.h LOCCamera.h LOCWorld.h LOCWorldGen.h LOCChunkData.h LOCLayer.h LOCStructures.h LOCStructure.h LOCFractal.h LOCNoise.h LOCNoiseStructs.h LOCUnitVoxelRaycaster.h LOCPlayer.h LOCChunkList.h LOCBlockHighlighter.h
SRCS_H = $(SRCS_RAW_H:LOC%=$(SRC_PATH)%) #LOC -> path to source files

#object .o files
OBJ_PATH = Dependencies/bin/
OBJS = $(SRCS_RAW_CPP:LOC%.cpp=$(OBJ_PATH)%.o) #.cpp -> .o
TEST_OBJS = $(TESTS_RAW_CPP:%.cpp=$(OBJ_PATH)tests/%.o) #.cpp -> .o
ENTRY = $(OBJ_PATH)$(MAIN).o

#included .c file for glad
GL_OBJ = Dependencies/bin/gl.o
GL_SRC = MinecraftClone/src/gl.c


#Rule to generate the main target from the .o files (depends on .h files to ensure it recompiles often enough)
$(TARGET) : $(OBJS) $(ENTRY) $(GL_OBJ) $(SRCS_H)
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -o $(TARGET) $(OBJS) $(ENTRY) $(GL_OBJ) -I$(INCLUDE) -l$(LIB) $(FRAMEWORKS) -L$(LIB_PATH)
	@echo "RECOMPILED"

#Rule to generate app.o (seperate bc no .h for the .cpp)
$(ENTRY) : $(SRC_PATH)$(MAIN).cpp
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE)

#rule to generate testing files in spereate folder
$(OBJ_PATH)tests/%Test.o : $(SRC_PATH)%Test.cpp 
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE)

#Rule to generate .o files from corresponding .cpp and .h files
$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp $(SRC_PATH)%.h
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE)

#Rule to generate the .o file from the .c file
$(GL_OBJ) : $(GL_SRC)
	@$(CC) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE)

build:
	@make -s
	@rm -f $(OBJS) $(ENTRY)

setSeed:
	@rm -f $(OBJ_PATH)Application.o 
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -DSETSEED -c -o $(OBJ_PATH)Application.o $(SRC_PATH)Application.cpp -I$(INCLUDE)
	@make -s
	@cp $(TARGET) setSeed$(VERSION)

randSeed: 
	@rm -f $(OBJ_PATH)Application.o 
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $(OBJ_PATH)Application.o $(SRC_PATH)Application.cpp -I$(INCLUDE)
	@make -s
	@cp $(TARGET) randSeed$(VERSION)

run_setSeed:
	@make setSeed -s
	@./setSeed$(VERSION)

run_randSeed:
	@make randSeed -s
	@./randSeed$(VERSION)


#recompile .out if neccessary and run
run:
	@make -s
	@./$(TARGET)

RaycastTest: $(OBJS) $(OBJ_PATH)tests/RaycastingTest.o $(GL_OBJ) $(SRCS_H)
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -o RayCastTest.out $(OBJS) $(OBJ_PATH)tests/RaycastingTest.o $(GL_OBJ) -I$(INCLUDE) -l$(LIB) $(FRAMEWORKS) -L$(LIB_PATH)
	@echo "COMPILED TEST"

TestRaycast:
	@make RaycastTest -s
	@./RayCastTest.out


#clean .o and .out files
clean:
	@rm -f $(TARGET) $(OBJS) $(ENTRY)
	@rm -f $(TEST_OBJS)
	@rm -f randSeed$(VERSION)
	@rm -f setSeed$(VERSION)
	@rm -rf $(TARGET).dSYM
	@echo "CLEANED"

#clean .out file
delete_exc:
	@rm -f $(TARGET)
	@rm -f randSeed$(VERSION)
	@rm -f setSeed$(VERSION)
	@rm -rf $(TARGET).dSYM
	@echo "CLEANED EXECUTABLE"

