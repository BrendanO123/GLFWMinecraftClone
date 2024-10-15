CC = g++
CFLAGS = -Wall -g

TARGET = build.out

SRC_PATH = MinecraftClone/src/
SRCS_RAW_CPP = LOCApplication.cpp
SRCS_CPP = $(SRCS_RAW_CPP:LOC%=$(SRC_PATH)%)

OBJ_PATH = Dependencies/bin/
OBJ1 = $(SRCS_RAW_CPP:LOC%=$(OBJ_PATH)%)
OBJS = $(OBJ1:%.cpp=%.o)

INCLUDE = Dependencies/include
LIB = glfw3
LIB_PATH = Dependencies/lib

F = -framework
FRAMEWORKS = $(F) Cocoa $(F) OpenGL $(F) IOKit

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) MinecraftClone/src/gl.c -I$(INCLUDE) -l$(LIB) $(FRAMEWORKS) -L$(LIB_PATH)
$(OBJS) : $(SRCS_CPP)
	$(CC) $(CFLAGS) -c $(SRCS_RAW_CPP:LOC%=$(SRC_PATH)%) -o $(OBJS) -I$(INCLUDE)

clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf $(TARGET).dSYM