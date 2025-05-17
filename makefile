#Flags and Compilers
CXX = g++
CC = gcc
CXXFLAGS = -Wall -g
CPPVERSION = -std=c++17

#.out file name
TARGET = build.out

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
SRCS_RAW_CPP = LOCShaders.cpp LOCBlock.cpp LOCChunk.cpp LOCCamera.cpp LOCWorld.cpp LOCWorldGen.cpp LOCChunkData.cpp LOCStructure.cpp LOCFractal.cpp LOCNoise.cpp LOCUnitVoxelRaycaster.cpp LOCPlayer.cpp LOCBlockHighlighter.cpp LOCFileManager.cpp
SRCS_CPP = $(SRCS_RAW_CPP:LOC%=$(SRC_PATH)%) #LOC -> path to source files

#source .h files (same path)
SRCS_RAW_H = LOCShaders.h LOCBlocks.h LOCBlock.h LOCChunk.h LOCCamera.h LOCWorld.h LOCWorldGen.h LOCChunkData.h LOCLayer.h LOCStructures.h LOCStructure.h LOCFractal.h LOCNoise.h LOCNoiseStructs.h LOCUnitVoxelRaycaster.h LOCPlayer.h LOCChunkList.h LOCBlockHighlighter.h LOCFileManager.h LOCWorldGenSettings.h
SRCS_H = $(SRCS_RAW_H:LOC%=$(SRC_PATH)%) #LOC -> path to source files

#object .o files
OBJ_PATH = Dependencies/bin/
OBJS = $(SRCS_RAW_CPP:LOC%.cpp=$(OBJ_PATH)%.o) #.cpp -> .o
DEPS = $(OBJS:%.o=%.d)
TEST_OBJS = $(TESTS_RAW_CPP:LOC%.cpp=$(OBJ_PATH)tests/%.o) #.cpp -> .o
ENTRY = $(OBJ_PATH)$(MAIN).o

#included .c file for glad
GL_OBJ = Dependencies/bin/gl.o
GL_SRC = MinecraftClone/src/gl.c

#default compilation rule
ALL: $(TARGET)

#Rule to generate the main target from the .o files (depends on .h files to ensure it recompiles often enough)
$(TARGET) : $(OBJS) $(ENTRY) $(GL_OBJ) $(SRCS_H)
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -o $(TARGET) $(OBJS) $(ENTRY) $(GL_OBJ) -I$(INCLUDE) -l$(LIB) $(FRAMEWORKS) -L$(LIB_PATH)
	@echo "RECOMPILED"

#rules for generating .o files
-include $(DEPS)

#Rule to generate app.o (seperate bc no .h for the .cpp)
$(ENTRY) : $(SRC_PATH)$(MAIN).cpp
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE)

#rule to generate testing files in spereate folder
$(OBJ_PATH)tests/%Test.o : $(SRC_PATH)%Test.cpp 
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE)

#rule to generate testing files in spereate folder
$(OBJ_PATH)SaveFileCleaner.o : $(SRC_PATH)SaveFileCleaner.cpp 
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE)

#rule to generate .d files
$(OBJ_PATH)%.d : $(SRC_PATH)%.cpp
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -MM -o $(patsubst %.o, %.d, $@) $< -I$(INCLUDE)

DEPENDS : $(DEPS)
	@echo "MADE DEPENDENCY FILES"

#Rule to generate .o files from corresponding .cpp and .h files
$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE)

#Rule to generate the .o file from the .c file
$(GL_OBJ) : $(GL_SRC)
	@$(CC) -c -o $@ $< -I$(INCLUDE)

build:
	@make -s
	@rm -f $(OBJS) $(ENTRY)


#recompile .out if neccessary and run
run:
	@make -s
	@./$(TARGET)

RaycastTest: $(OBJS) $(OBJ_PATH)tests/RaycastingTest.o $(GL_OBJ) $(SRCS_H)
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -o RayCastTest.out $(OBJS) $(OBJ_PATH)tests/RaycastingTest.o $(GL_OBJ) -I$(INCLUDE) -l$(LIB) $(FRAMEWORKS) -L$(LIB_PATH)
	@echo "COMPILED TEST"

saveFileTrimmer: $(OBJS) $(OBJ_PATH)SaveFileCleaner.o $(GL_OBJ) $(SRCS_H)
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -o trimSaves.out $(OBJS) $(OBJ_PATH)SaveFileCleaner.o $(GL_OBJ) -I$(INCLUDE) -l$(LIB) $(FRAMEWORKS) -L$(LIB_PATH)
	@echo "COMPILED PROGRAM"

trimSaves: 
	@make saveFileTrimmer -s
	@./trimSaves.out
	@echo "DONE"

TestRaycast:
	@make RaycastTest -s
	@./RayCastTest.out


#clean .o and .out files
clean:
	@rm -f $(TARGET) $(OBJS) $(ENTRY) $(DEPS) $(GL_OBJ)
	@rm -f $(TEST_OBJS)
	@rm -rf $(TARGET).dSYM
	@echo "CLEANED"

#clean .out file
delete_exc:
	@rm -f $(TARGET)
	@rm -rf $(TARGET).dSYM
	@echo "CLEANED EXECUTABLE"


delete_%:
	@rm -r MinecraftClone/saves/"$(strip $*)"
	@echo "DELETED SAVE: $(strip $*)"

echo_saves:
	@echo MinecraftClone/saves/*
