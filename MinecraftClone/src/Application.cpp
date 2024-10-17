#include <iostream>
#include <string.h>

#include "Shaders.h"
#include "blocks.h"

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/linmath.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
    glm :: vec3 pos;
    glm :: vec2 texPos;

    Vertex(glm :: vec3 Pos, glm :: vec2 TexPos){pos=Pos; texPos=TexPos;}
    Vertex(){pos= glm ::vec3(1); texPos = glm :: vec2(1);}
};

struct BlockMesh24{
    Vertex verticies[24];
    int indicies[36];
};
/*struct BlockMeshBillboard{
    Vertex verticies[8];
    int indicies[12];
};*/

const float blockMapW_blocks = 4.f;
const float blockMapH_blocks = 4.f;

namespace Blocks{
    static BlockMesh24 genMeshedBlock(BLOCKS type, float scale, glm :: vec3 position){
        //TODO: block mesh with each quad having its own vertecies
        BlockMesh24 blockMesh;
        Block block = blocks[type];

        int vertOffset=0, indOffset=0;

        //front quad
        blockMesh.verticies[0] = Vertex(glm :: vec3(-0.5f, -0.5f, -0.5f) * scale + position, glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks)));
        blockMesh.verticies[1] = Vertex(glm :: vec3(0.5f, -0.5f, -0.5f) * scale + position, glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks)));
        blockMesh.verticies[2] = Vertex(glm :: vec3(-0.5f, 0.5f, -0.5f) * scale + position, glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks)));
        blockMesh.verticies[3] = Vertex(glm :: vec3(0.5f, 0.5f, -0.5f) * scale + position, glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks)));

        blockMesh.indicies[0] = 0; blockMesh.indicies[1] = 2; blockMesh.indicies[2] = 1;
        blockMesh.indicies[3] = 3; blockMesh.indicies[4] = 1; blockMesh.indicies[5] = 2;
        vertOffset+=4; indOffset+=6;

        //right quad
        blockMesh.verticies[0+vertOffset] = Vertex(glm :: vec3(0.5f, -0.5f, -0.5f) * scale + position, glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks)));
        blockMesh.verticies[1+vertOffset] = Vertex(glm :: vec3(0.5f, -0.5f, 0.5f) * scale + position, glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks)));
        blockMesh.verticies[2+vertOffset] = Vertex(glm :: vec3(0.5f, 0.5f, -0.5f) * scale + position, glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks)));
        blockMesh.verticies[3+vertOffset] = Vertex(glm :: vec3(0.5f, 0.5f, 0.5f) * scale + position, glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks)));

        blockMesh.indicies[0+indOffset] = 0+vertOffset; 
        blockMesh.indicies[1+indOffset] = 2+vertOffset; 
        blockMesh.indicies[2+indOffset] = 1+vertOffset;

        blockMesh.indicies[3+indOffset] = 3+vertOffset; 
        blockMesh.indicies[4+indOffset] = 1+vertOffset; 
        blockMesh.indicies[5+indOffset] = 2+vertOffset;
        vertOffset+=4; indOffset+=6;

        //back quad
        blockMesh.verticies[0+vertOffset] = Vertex(glm :: vec3(0.5f, -0.5f, 0.5f) * scale + position, glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks)));
        blockMesh.verticies[1+vertOffset] = Vertex(glm :: vec3(-0.5f, -0.5f, 0.5f) * scale + position, glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks)));
        blockMesh.verticies[2+vertOffset] = Vertex(glm :: vec3(0.5f, 0.5f, 0.5f) * scale + position, glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks)));
        blockMesh.verticies[3+vertOffset] = Vertex(glm :: vec3(-0.5f, 0.5f, 0.5f) * scale + position, glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks)));

        blockMesh.indicies[0+indOffset] = 0+vertOffset; 
        blockMesh.indicies[1+indOffset] = 2+vertOffset; 
        blockMesh.indicies[2+indOffset] = 1+vertOffset;

        blockMesh.indicies[3+indOffset] = 3+vertOffset; 
        blockMesh.indicies[4+indOffset] = 1+vertOffset; 
        blockMesh.indicies[5+indOffset] = 2+vertOffset;
        vertOffset+=4; indOffset+=6;

        //left quad
        blockMesh.verticies[0+vertOffset] = Vertex(glm :: vec3(-0.5f, -0.5f, 0.5f) * scale + position, glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks)));
        blockMesh.verticies[1+vertOffset] = Vertex(glm :: vec3(-0.5f, -0.5f, -0.5f) * scale + position, glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks)));
        blockMesh.verticies[2+vertOffset] = Vertex(glm :: vec3(-0.5f, 0.5f, 0.5f) * scale + position, glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks)));
        blockMesh.verticies[3+vertOffset] = Vertex(glm :: vec3(-0.5f, 0.5f, -0.5f) * scale + position, glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks)));

        blockMesh.indicies[0+indOffset] = 0+vertOffset; 
        blockMesh.indicies[1+indOffset] = 2+vertOffset; 
        blockMesh.indicies[2+indOffset] = 1+vertOffset;

        blockMesh.indicies[3+indOffset] = 3+vertOffset; 
        blockMesh.indicies[4+indOffset] = 1+vertOffset; 
        blockMesh.indicies[5+indOffset] = 2+vertOffset;
        vertOffset+=4; indOffset+=6;

        //top quad
        blockMesh.verticies[0+vertOffset] = Vertex(glm :: vec3(-0.5f, 0.5f, -0.5f) * scale + position, glm :: vec2(block.topLowX / blockMapW_blocks, 1-(block.topLowY / blockMapH_blocks)));
        blockMesh.verticies[1+vertOffset] = Vertex(glm :: vec3(0.5f, 0.5f, -0.5f) * scale + position, glm :: vec2(block.topHighX / blockMapW_blocks, 1-(block.topLowY / blockMapH_blocks)));
        blockMesh.verticies[2+vertOffset] = Vertex(glm :: vec3(-0.5f, 0.5f, 0.5f) * scale + position, glm :: vec2(block.topLowX / blockMapW_blocks, 1-(block.topHighY / blockMapH_blocks)));
        blockMesh.verticies[3+vertOffset] = Vertex(glm :: vec3(0.5f, 0.5f, 0.5f) * scale + position, glm :: vec2(block.topHighX / blockMapW_blocks, 1-(block.topHighY / blockMapH_blocks)));

        blockMesh.indicies[0+indOffset] = 0+vertOffset; 
        blockMesh.indicies[1+indOffset] = 2+vertOffset; 
        blockMesh.indicies[2+indOffset] = 1+vertOffset;

        blockMesh.indicies[3+indOffset] = 3+vertOffset; 
        blockMesh.indicies[4+indOffset] = 1+vertOffset; 
        blockMesh.indicies[5+indOffset] = 2+vertOffset;
        vertOffset+=4; indOffset+=6;

        //bottom quad
        blockMesh.verticies[0+vertOffset] = Vertex(glm :: vec3(-0.5f, -0.5f, 0.5f) * scale + position, glm :: vec2(block.bottomLowX / blockMapW_blocks, 1-(block.bottomLowY / blockMapH_blocks)));
        blockMesh.verticies[1+vertOffset] = Vertex(glm :: vec3(0.5f, -0.5f, 0.5f) * scale + position, glm :: vec2(block.bottomHighX / blockMapW_blocks, 1-(block.bottomLowY / blockMapH_blocks)));
        blockMesh.verticies[2+vertOffset] = Vertex(glm :: vec3(-0.5f, -0.5f, -0.5f) * scale + position, glm :: vec2(block.bottomLowX / blockMapW_blocks, 1-(block.bottomHighY / blockMapH_blocks)));
        blockMesh.verticies[3+vertOffset] = Vertex(glm :: vec3(0.5f, -0.5f, -0.5f) * scale + position, glm :: vec2(block.bottomHighX / blockMapW_blocks, 1-(block.bottomHighY / blockMapH_blocks)));

        blockMesh.indicies[0+indOffset] = 0+vertOffset; 
        blockMesh.indicies[1+indOffset] = 2+vertOffset; 
        blockMesh.indicies[2+indOffset] = 1+vertOffset;

        blockMesh.indicies[3+indOffset] = 3+vertOffset; 
        blockMesh.indicies[4+indOffset] = 1+vertOffset; 
        blockMesh.indicies[5+indOffset] = 2+vertOffset;

        return blockMesh;
    }
    /*static BlockMeshBillboard genBillboardBlock(BLOCKS type, float scale, vec3 position){
        //TODO: block mesh with billboard mesh. Two quads in an X 
        BlockMeshBillboard blockMesh;
        return blockMesh;
    }*/
}


const string title = "To Be Minecraft Clone";

int main(){

    const BlockMesh24 blockMesh = genMeshedBlock(Blocks :: LEAVES_OAK, 0.5f, glm ::vec3(0.f, -0.5f, 0.25f));
    const BlockMesh24 blockMesh1 = genMeshedBlock(Blocks :: GRASS, 0.5f, glm ::vec3(0.f, -0.5f, 0.75f));
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
        glfwDestroyWindow(window);
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
    const GLint vtexPos_location = glGetAttribLocation(program, "vtexPos");


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

 
    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    GLuint vertex_buffer; //unsigned int vertex buffer
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blockMesh.verticies), blockMesh.verticies, GL_STATIC_DRAW);

    GLuint element_buffer;
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(blockMesh.indicies), blockMesh.indicies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), /*(void*) offsetof(Vertex, pos)*/(void*)0);
    glEnableVertexAttribArray(vtexPos_location);
    glVertexAttribPointer(vtexPos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), /*(void*) offsetof(Vertex, texPos)*/(void*) sizeof(glm :: vec3));

    GLuint vertex_array2;
    glGenVertexArrays(1, &vertex_array2);
    glBindVertexArray(vertex_array2);

    GLuint vertex_buffer2; //unsigned int vertex buffer
    glGenBuffers(1, &vertex_buffer2);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blockMesh1.verticies), blockMesh1.verticies, GL_STATIC_DRAW);

    GLuint element_buffer2;
    glGenBuffers(1, &element_buffer2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(blockMesh1.indicies), blockMesh1.indicies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), /*(void*) offsetof(Vertex, pos)*/(void*)0);
    glEnableVertexAttribArray(vtexPos_location);
    glVertexAttribPointer(vtexPos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), /*(void*) offsetof(Vertex, texPos)*/(void*) sizeof(glm :: vec3));
    
    
    shader.use();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);

    glClearColor(135/255.0f, 206/255.0f, 235/255.0f, 1.0f);
    while(!glfwWindowShouldClose(window)){ //while window wants to stay open

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        float ratio = width / (float) height;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        
        mat4x4 m, p, mvp;
        mat4x4_identity(m);
        mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        mat4x4_rotate_X(m, m, 0.25f);
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(vertex_array2);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}