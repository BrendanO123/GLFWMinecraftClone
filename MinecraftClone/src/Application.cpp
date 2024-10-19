#include <iostream>
#include <string.h>

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <GLFW/linmath.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/gtc/type_ptr.hpp>

#include "Chunk.h"
#include "Shaders.h"
#include "Blocks.h"
#include "Camera.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

using namespace std;

#define VSYNC 1 //0 = off, 1 = on

Camera cam = Camera();

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error %s\n", description);
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    cam.mouse_callback(window, xpos, ypos);
}

static void scroll_callback(GLFWwindow* window, double xOff, double yOff){
    cam.scroll_callback(window, xOff, yOff);
}

void processInput(GLFWwindow* window, float deltaTime=1.f){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }

    cam.processInput(window, deltaTime);
}


const string title = "To Be Minecraft Clone";

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


    GLFWwindow* window = glfwCreateWindow(640, 480, title.data(), NULL, NULL);
    if(!window){ // Window creation fails
        glfwTerminate();
        printf("GLFW WINDOW INIT FAILED\n", stderr);
        exit(EXIT_FAILURE); 
    } 
    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGL(glfwGetProcAddress)){ // Glad initialization fails
        glfwDestroyWindow(window);
        glfwTerminate();
        printf("GLAD INIT FAILED\n", stderr);
        exit(EXIT_FAILURE); 
    }
    glfwSwapInterval(VSYNC);


    Shader shader = Shader("MinecraftClone/assets/shaders/VShader.glsl", "MinecraftClone/assets/shaders/FShader.glsl");

    const GLuint modelMatLoc = glGetUniformLocation(shader.program, "model");
    const GLuint viewMatLoc = glGetUniformLocation(shader.program, "view");
    const GLuint projectionMatLoc = glGetUniformLocation(shader.program, "projection");
    const GLint vpos_location = glGetAttribLocation(shader.program, "vPos");
    const GLint vtexPos_location = glGetAttribLocation(shader.program, "vtexPos");

    shader.use();


    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int w, h, channels;
    GLubyte *data = stbi_load("MinecraftClone/assets/sprites/block_map.png", &w, &h, &channels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        glfwDestroyWindow(window);
        glfwTerminate();
        printf("TEXTURE LOAD FAILED\n", stderr);
        exit(EXIT_FAILURE); 
    }
    stbi_image_free(data);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);

    Chunk chunk = Chunk(0, glm :: vec2(0,0));

    chunk.data.push_back(Layer((unsigned char)0));
    chunk.data[0].data[1 + (0<<4)] = Blocks :: LOG_OAK; chunk.data[0].data[1 + (1<<4)] = Blocks :: DIRT;
    chunk.data[0].data[0 + (0<<4)] = Blocks :: LEAVES_OAK; chunk.data[0].data[0 + (1<<4)] = Blocks :: GRASS;

    chunk.data[0].data[1 + (2<<4)] = Blocks :: GRASS; chunk.data[0].data[1 + (3<<4)] = Blocks :: GRASS;
    chunk.data[0].data[0 + (2<<4)] = Blocks :: STONE; chunk.data[0].data[0 + (3<<4)] = Blocks :: GRASS;

    chunk.data[0].data[1 + (4<<4)] = Blocks :: GRASS;
    chunk.data[0].data[0 + (4<<4)] = Blocks :: GRASS;

    chunk.data.push_back(Layer((unsigned char)1));
    chunk.data[1].data[0 + (1<<4)] = Blocks :: SHORT_GRASS;
    chunk.data[1].data[1 + (2<<4)] = Blocks :: TALL_GRASS_BOTTOM;
    chunk.data[1].data[1 + (3<<4)] = Blocks :: TULIP_WHITE;
    chunk.data[1].data[0 + (3<<4)] = Blocks :: ROSE;

    chunk.data[1].data[1 + (4<<4)] = Blocks :: TULIP_ORANGE;
    chunk.data[1].data[0 + (4<<4)] = Blocks :: TULIP_PINK;

    chunk.data.push_back(Layer((unsigned char)2));
    chunk.data[2].data[1 + (2<<4)] = Blocks :: TALL_GRASS_TOP;

    chunk.genChunk();

    glm ::mat4 view = glm :: identity<glm :: mat4>();
    glm ::mat4 projection = glm :: identity<glm :: mat4>();
    float renderDist = 25.f;

    glClearColor(135/255.0f, 206/255.0f, 235/255.0f, 1.0f);
    float deltaTime, currentFrame, lastFrame = 0.0f;
    while(!glfwWindowShouldClose(window)){ //while window wants to stay open

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        float ratio = width / (float) height;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window, deltaTime);


        projection = glm::perspective(glm::radians(cam.fov), ratio, 0.1f, renderDist);
        glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, glm::value_ptr(projection));

        view = cam.getView();
        glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(view));

        chunk.render(modelMatLoc, vpos_location, vtexPos_location);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}