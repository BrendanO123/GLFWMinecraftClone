#include <string.h>
#include <iostream>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <GLFW/linmath.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/gtc/type_ptr.hpp>

#include "Shaders.h"
#include "World.h"
#include "Blocks.h"
#include "Camera.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

using namespace std;

#define VSYNC 1 //0 = off, 1 = on

Camera cam = Camera();
bool menu = false;

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error %s\n", description);
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(!menu){cam.mouse_callback(window, xpos, ypos);}
}

static void scroll_callback(GLFWwindow* window, double xOff, double yOff){
    if(!menu){cam.scroll_callback(window, xOff, yOff);}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
    else if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        menu = !menu;
        if(menu){glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}
        else{glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); cam.setFirstMouse(true);}
    }
}

void processInput(GLFWwindow* window, float deltaTime=1.f){if(!menu){cam.processInput(window, deltaTime);}}



const string title = "To Be Minecraft Clone";

int main(){
    glfwSetErrorCallback(error_callback);

    if(!glfwInit()){ //GLFW initialization fails
        glfwTerminate();
        printf("GLFW INIT FAILED\n", stderr);
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //TODO: update to GLFW 4.3
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
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGL(glfwGetProcAddress)){ // Glad initialization fails
        glfwDestroyWindow(window);
        glfwTerminate();
        printf("GLAD INIT FAILED\n", stderr);
        exit(EXIT_FAILURE); 
    }
    glfwSwapInterval(VSYNC);


    Shader shader = Shader("MinecraftClone/assets/shaders/VShader.glsl", "MinecraftClone/assets/shaders/FShader.glsl");

    const GLuint viewMatLoc = glGetUniformLocation(shader.program, "view");
    const GLuint projectionMatLoc = glGetUniformLocation(shader.program, "projection");

    shader.use();

    float alphaErrorRange=0.3f; //MUST BE >0!!
    glUniform1f(glGetUniformLocation(shader.program, "blockMapW_blocks"), Blocks :: blockMapW_blocks);
    glUniform1f(glGetUniformLocation(shader.program, "blockMapH_blocks"), Blocks :: blockMapH_blocks);
    glUniform1f(glGetUniformLocation(shader.program, "alphaH"), alphaErrorRange);


    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //TODO to fix textures:
        //change sprite map to 3d texture where each slice is a block face and gen mipmap of that to prevent interblock bleeding
        //maybe try filling in the empty pixels in the texture with transparent or translucent green instead of transparent white

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR /*GL_NEAREST*/);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);

    stbi_set_flip_vertically_on_load(true);

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

    World :: world = new World(&shader);

    glm ::mat4 view = glm :: identity<glm :: mat4>();
    glm ::mat4 projection = glm :: identity<glm :: mat4>();
    float renderDist = 160.f;

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

        World :: world->update(cam.CameraPos);

        glfwSwapBuffers(window);
        if(!menu){glfwPollEvents();}
        else{glfwWaitEvents();}
    }

    delete(World :: world);
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}