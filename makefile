CC = g++
C_COMPILER = gcc
CFLAGS = -Wall -g

TARGET = build.out

SRC_PATH = MinecraftClone/src/
SRCS_RAW_CPP = LOCApplication.cpp LOCShaders.cpp LOCBlock.cpp LOCChunk.cpp
SRCS_CPP = $(SRCS_RAW_CPP:LOC%=$(SRC_PATH)%)

SRCS_RAW_H = LOCShaders.h LOCBlocks.h LOCBlock.h LOCChunk.h
SRCS_H = $(SRCS_RAW_H:LOC%=$(SRC_PATH)%)

OBJ_PATH = Dependencies/bin/
OBJ1 = $(SRCS_RAW_CPP:%.cpp=%.o)
OBJS = $(OBJ1:LOC%=$(OBJ_PATH)%)
OBJS_TEMP = $(OBJ1:LOC%=%)

GL_OBJ = Dependencies/bin/gl.oc
GL_SRC = MinecraftClone/src/gl.c

INCLUDE = Dependencies/include -I$(SRC_PATH)
LIB = glfw3
LIB_PATH = Dependencies/lib

F = -framework
FRAMEWORKS = $(F) Cocoa $(F) OpenGL $(F) IOKit


$(TARGET) : $(OBJS) $(GL_OBJ)
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(GL_OBJ) -I$(INCLUDE) -l$(LIB) $(FRAMEWORKS) -L$(LIB_PATH)
	@echo "DONE"

$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE)


$(GL_OBJ) : $(GL_SRC)
	@$(C_COMPILER) $(CFLAGS) -c -o $(GL_OBJ) $(GL_SRC) -I$(INCLUDE)

clean:
	@rm -f $(TARGET) $(OBJS)
	@rm -rf $(TARGET).dSYM
	@echo "DONE"