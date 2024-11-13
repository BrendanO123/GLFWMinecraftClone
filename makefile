CC = g++
C_COMPILER = gcc
CFLAGS = -Wall -g
CPPVERSION = -std=c++17

TARGET = build.out

SRC_PATH = MinecraftClone/src/
SRCS_RAW_CPP = LOCApplication.cpp LOCShaders.cpp LOCBlock.cpp LOCChunk.cpp LOCCamera.cpp LOCWorld.cpp LOCWorldGen.cpp
SRCS_CPP = $(SRCS_RAW_CPP:LOC%=$(SRC_PATH)%)

SRCS_RAW_H = LOCShaders.h LOCBlocks.h LOCBlock.h LOCChunk.h LOCCamera.h LOCWorld.h LOCWorldGen.h LOCChunkData.h LOCLayer.h
SRCS_H = $(SRCS_RAW_H:LOC%=$(SRC_PATH)%)

OBJ_PATH = Dependencies/bin/
OBJ1 = $(SRCS_RAW_CPP:%.cpp=%.o)
OBJS = $(OBJ1:LOC%=$(OBJ_PATH)%)
OBJS_TEMP = $(OBJ1:LOC%=%)

GL_OBJ = Dependencies/bin/gl.o
GL_SRC = MinecraftClone/src/gl.c

INCLUDE = Dependencies/include -I$(SRC_PATH)
LIB = glfw3
LIB_PATH = Dependencies/lib

F = -framework
FRAMEWORKS = $(F) Cocoa $(F) OpenGL $(F) IOKit


$(TARGET) : $(OBJS) $(GL_OBJ) $(SRCS_H)
	@$(CC) $(CFLAGS) $(CPPVERSION) -o $(TARGET) $(OBJS) $(GL_OBJ) -I$(INCLUDE) -l$(LIB) $(FRAMEWORKS) -L$(LIB_PATH)
	@echo "DONE"

$(OBJ_PATH)Application.o : $(SRC_PATH)Application.cpp
	@$(CC) $(CFLAGS) $(CPPVERSION) -c -o $(OBJ_PATH)Application.o $(SRC_PATH)Application.cpp -I$(INCLUDE)

$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp $(SRC_PATH)%.h
	@$(CC) $(CFLAGS) $(CPPVERSION) -c $< -o $@ -I$(INCLUDE)

$(GL_OBJ) : $(GL_SRC)
	@$(C_COMPILER) $(CFLAGS) -c -o $(GL_OBJ) $(GL_SRC) -I$(INCLUDE)

clean:
	@rm -f $(TARGET) $(OBJS)
	@rm -rf $(TARGET).dSYM
	@echo "DONE"

clean_exc:
	@rm -f $(TARGET)
	@rm -rf $(TARGET).dSYM
	@echo "DONE"