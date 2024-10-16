#include <iostream>
#include <string.h>

#include "Shaders.h"

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/linmath.h>

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

using namespace std;

#define VSYNC 1 //0 = off, 1 = on

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


struct Vertex
{
    vec3 pos;
    vec3 col;
};
static const Vertex vertices[8] =
{
    { {  -0.25f, 0.25f, 0.25f }, { 0.f, 0.f, 0.f } }, /*front top left*/ { {  0.25f, 0.25f, 0.25f }, { 1.f, 0.f, 0.f } }, //front top right
    { { -0.25f, -0.25f, 0.25f }, { 0.f, 1.f, 0.f } }, /*front bottom left*/ { {  0.25f, -0.25f, 0.25f }, { 1.f, 1.f, 0.f } }, //front bottom right
    
    { {  -0.25f, 0.25f, 0.75f }, { 0.f, 0.f, 1.f } }, /*back top left*/ { {  0.25f, 0.25f, 0.75f }, { 1.f, 0.f, 1.f } }, //back top right
    { { -0.25f, -0.25f, 0.75f }, { 0.f, 1.f, 1.f } }, /*back bottom left*/ { {  0.25f, -0.25f, 0.75f }, { 1.f, 1.f, 1.f } } //back bottom right
};

static const GLuint indicies[36] = {
    //front quad
    2, 0, 3, //front bottom tri
    1, 3, 0, //front top tri

    //back quad
    7, 5, 6, //back bottom tri
    4, 6, 5, //back top tri

    //right quad
    3, 1, 7, //right bottom tri
    5, 7, 1, //right top tri

    //left quad
    6, 4, 2, //left bottom tri
    0, 2, 4, //left top tri

    //top quad
    0, 4, 1, //top bottom tri
    5, 1, 4, //top top tri

    //bottom quad
    6, 2, 7, //bottom bottom tri
    3, 7, 2 //bottom top tri
};


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


    if(!gladLoadGL(glfwGetProcAddress)){ // Glad initialization fails
        glfwTerminate();
        printf("GLAD INIT FAILED\n", stderr);
        exit(EXIT_FAILURE); 
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(VSYNC);


    Shader shader = Shader("MinecraftClone/assets/shaders/VShader.glsl", "MinecraftClone/assets/shaders/FShader.glsl");
    GLuint program = shader.program;


    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

 
    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    GLuint vertex_buffer; //unsigned int vertex buffer
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint element_buffer;
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, col));

    shader.use();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(135/255.0f, 206/255.0f, 235/255.0f, 1.0f);
    while(!glfwWindowShouldClose(window)){ //while window wants to stay open

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        float ratio = width / (float) height;

        glClear(GL_COLOR_BUFFER_BIT);


        mat4x4 m, p, mvp;
        mat4x4_identity(m);
        mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        //mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}