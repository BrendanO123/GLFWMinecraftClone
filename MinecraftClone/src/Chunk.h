#pragma once

#include "Blocks.h"
#include <vector>

#include <glm/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

using namespace std;

struct Vertex
{
    glm :: vec3 pos;
    glm :: vec2 texPos;

    Vertex(glm :: vec3 Pos, glm :: vec2 TexPos){pos=Pos; texPos=TexPos;}
    Vertex(){pos= glm ::vec3(1); texPos = glm :: vec2(1);}
};
struct Layer{
    GLubyte y;
    vector<GLubyte> data;

    Layer(GLubyte newY){y = newY; data = vector<unsigned char>(256, (unsigned char)0);};
};
class Chunk{

    public:
        vector<Layer> data; //TODO: make variable with lod
        GLubyte flagByte; //header byte with ready to render and generated flag bits
        //it also has the unused (for now) values of modified and stored in file flag bits

        Chunk(GLuint lod, glm :: vec2 chunkPos);

        void genChunk();
        void render(GLuint modelMatLoc, GLuint vpos_location, GLuint vtexPos_location);
        
    private:
        GLuint VAO, VBO, EBO;
        glm :: vec3 pos_world;
        vector<Vertex> verticies;
        vector<unsigned int> indicies;
        GLubyte LOD;
};
namespace ChunkFlags{
    enum CHUNKFLAGS : unsigned char{
        READY = (unsigned char)(1<<7),
        GENERATED = 1,
        MODIFIED = 2,
        FILE_STORED =4
    };
};