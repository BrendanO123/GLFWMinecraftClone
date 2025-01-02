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
SRCS_RAW_CPP = LOCApplication.cpp LOCShaders.cpp LOCBlock.cpp LOCChunk.cpp LOCCamera.cpp LOCWorld.cpp LOCWorldGen.cpp LOCChunkData.cpp LOCStructure.cpp LOCFractal.cpp LOCNoise.cpp
SRCS_CPP = $(SRCS_RAW_CPP:LOC%=$(SRC_PATH)%) #LOC -> path to source files

#source .h files (same path)
SRCS_RAW_H = LOCShaders.h LOCBlocks.h LOCBlock.h LOCChunk.h LOCCamera.h LOCWorld.h LOCWorldGen.h LOCChunkData.h LOCLayer.h LOCStructures.h LOCStructure.h LOCFractal.h LOCNoise.h LOCNoiseStructs.h
SRCS_H = $(SRCS_RAW_H:LOC%=$(SRC_PATH)%) #LOC -> path to source files

#object .o files
OBJ_PATH = Dependencies/bin/
OBJ1 = $(SRCS_RAW_CPP:%.cpp=%.o) #.cpp -> .o
OBJS = $(OBJ1:LOC%=$(OBJ_PATH)%) #LOC -> path to object file

#included .c file for glad
GL_OBJ = Dependencies/bin/gl.o
GL_SRC = MinecraftClone/src/gl.c


#Rule to generate the main target from the .o files (depends on .h files to ensure it recompiles often enough)
$(TARGET) : $(OBJS) $(GL_OBJ) $(SRCS_H)
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -o $(TARGET) $(OBJS) $(GL_OBJ) -I$(INCLUDE) -l$(LIB) $(FRAMEWORKS) -L$(LIB_PATH)
	@echo "RECOMPILED"

#Rule to generate app.o (seperate bc no .h for the .cpp)
$(OBJ_PATH)Application.o : $(SRC_PATH)Application.cpp
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE)

#Rule to generate .o files from corresponding .cpp and .h files
$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp $(SRC_PATH)%.h
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE)

#Rule to generate the .o file from the .c file
$(GL_OBJ) : $(GL_SRC)
	@$(CC) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE)


#recompile .out if neccessary and run
run:
	@make -s
	@./$(TARGET)


#clean .o and .out files
clean:
	@rm -f $(TARGET) $(OBJS)
	@rm -rf $(TARGET).dSYM
	@echo "CLEANED"

#clean .out file
clean_exc:
	@rm -f $(TARGET)
	@rm -rf $(TARGET).dSYM
	@echo "CLEANED EXECUTABLE"



#extra makefile code for the vulkan testing.

#I am thinking I will not port to Vulkan just yet, so I will likely put the Vulkan Code into its own repository soon.
#Once it is seperated from this project I will clean out this code.
#I might get around to properly port to Vulkan after my science fair in January.
runV:
	@make makeVulk -s
	@DYLD_LIBRARY_PATH=Dependencies/lib    VK_ICD_FILENAMES=Dependencies/Vulkan/share/vulkan/icd.d/MoltenVK_icd.json    VK_LAYER_PATH=Dependencies/Vulkan/share/vulkan/explicit_layer.d    ./VulkanBuild.out

cleanVulk:
	@rm -f VulkanBuild.out $(OBJ_PATH)VKApplication.o
	@rm -rf VulkanBuild.out.dSYM
	@echo "CLEANED VULKAN"

makeVulk : VulkanBuild.out
VulkanBuild.out : $(OBJ_PATH)VKApplication.o
	@$(CXX) $(CXXFLAGS) $(CPPVERSION) -o $@ $< -I$(INCLUDE) -IDependencies/Vulkan/include -lglfw3 -lvulkan.1 -lvulkan.1.3.296 -lMoltenVK -lSDL2 -lSDL2main -framework Cocoa -framework IOKit -L$(LIB_PATH)
	@echo "RECOMPILED VULKAN"

$(OBJ_PATH)VKApplication.o : $(SRC_PATH)VulkanMainTesting/VKApplication.cpp $(SRC_PATH)VulkanMainTesting/VKApplication.h
	@@$(CXX) $(CXXFLAGS) $(CPPVERSION) -c -o $@ $< -I$(INCLUDE) -IDependencies/Vulkan/include