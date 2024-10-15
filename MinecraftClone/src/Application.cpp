#include <iostream>

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

//sing namespace std;

#define VSYNC 1 //0 = off, 1 = on

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(){

    glfwSetErrorCallback(error_callback);

    if(!glfwInit()){ //GLFW initialization fails
        glfwTerminate();
        printf("GLFW INIT FAILED\n", stderr);
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(640, 480, "Temp Title", NULL, NULL);
    if(!window){ // Window creation fails
        glfwTerminate();
        printf("GLFW WINDOW INIT FAILED\n", stderr);
        exit(EXIT_FAILURE); 
    } 
    glfwMakeContextCurrent(window);


    if(!gladLoadGL(glfwGetProcAddress)){ // Glad initialization fails
        glfwTerminate();
        printf("GLAD INIT FAILED\n", stderr);
        exit(EXIT_FAILURE); 
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(VSYNC);


    //float lastFrame =0.0f;
    while(!glfwWindowShouldClose(window)){ //while window wants to stay open

        int height, width;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        /*float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;*/


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}