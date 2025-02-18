#pragma once

#define GL_SILENCE_DEPRECATION
#include <glad/gl.h>
#include <vector>
#include <thread>

#include "Blocks.h"
#include "ChunkData.h"
#include "Layer.h"
#include "Shaders.h"

using namespace std;

/**
 * @brief A vertex for a normal block in a chunk (int style cordinates).
 */
struct Vertex
{
    GLubyte texPosX, texPosY;
    GLbyte posX, posZ;
    GLubyte posY;
    GLubyte NormalSelector;

    Vertex(glm :: vec3 Pos, glm :: vec2 TexPos, GLubyte Normal) : 
        texPosX((unsigned char)TexPos.x), texPosY((unsigned char)TexPos.y),
        posX((unsigned char)Pos.x), posZ((unsigned char)Pos.z), posY((unsigned char)Pos.y),
        NormalSelector(Normal){}

    Vertex(glm :: vec3 Pos, GLubyte texX, GLubyte texY, GLubyte Normal) : 
        texPosX((unsigned char)texX), texPosY((unsigned char)texY),
        posX((unsigned char)Pos.x), posZ((unsigned char)Pos.z), posY((unsigned char)Pos.y),
        NormalSelector(Normal){}
        
    Vertex(GLbyte x, GLbyte y, GLbyte z, glm :: vec2 TexPos, GLubyte Normal) : 
        texPosX((unsigned char)TexPos.x), texPosY((unsigned char)TexPos.y),
        posX((unsigned char)x), posZ((unsigned char)z), posY((unsigned char)y),
        NormalSelector(Normal){}
        
    Vertex(GLbyte x, GLbyte y, GLbyte z, GLubyte texX, GLubyte texY, GLubyte Normal) : 
        texPosX((unsigned char)texX), texPosY((unsigned char)texY),
        posX((unsigned char)x), posZ((unsigned char)z), posY((unsigned char)y),
        NormalSelector(Normal){}
        
    Vertex(GLubyte Normal) : 
        texPosX(0), texPosY(0),
        posX(0), posZ(0), posY(0),
        NormalSelector(Normal){}
};

/**
 * @brief A vertex for a billboard block (such as a flower or tall grass) in a chunk (float cordinates). 
 */
struct BillboardVertex
{
    glm :: vec2 pos;
    GLubyte height;
    GLubyte texPosX, texPosY;
    GLubyte NormalSelector = 4;

    BillboardVertex(glm :: vec3 Pos, glm :: vec2 TexPos) : 
    pos(glm :: vec2(Pos.x, Pos.z)), height((unsigned char)Pos.y),
    texPosX((unsigned char)TexPos.x), texPosY((unsigned char)TexPos.y){}

    BillboardVertex(glm :: vec3 Pos, GLubyte texX, GLubyte texY) : 
    pos(glm :: vec2(Pos.x, Pos.z)), height((unsigned char)Pos.y),
    texPosX((unsigned char)texX), texPosY((unsigned char)texY){}

    BillboardVertex(glm :: vec2 Pos, GLubyte y, glm :: vec2 TexPos) : 
    pos(glm :: vec2(Pos.x, Pos.y)), height((unsigned char)y),
    texPosX((unsigned char)TexPos.x), texPosY((unsigned char)TexPos.y){}

    BillboardVertex(glm :: vec2 Pos, GLubyte y, GLubyte texX, GLubyte texY) : 
    pos(glm :: vec2(Pos.x, Pos.y)), height((unsigned char)y),
    texPosX((unsigned char)texX), texPosY((unsigned char)texY){}

    BillboardVertex() : pos(glm :: vec3(1)), texPosX(0), texPosY(0){}
};

/**
 * @brief the actual Chunk class which handles rendering the chunk.
 */
class Chunk{

    public:
        GLubyte flagByte; //header byte with ready to render and generated flag bits
        //it also has the unused (for now) values of modified and stored in file flag bits

        Chunk(GLuint lod, glm :: ivec2 chunkPos);
        ~Chunk();

        void genChunkMesh();
        void render(Shader shader);
        void renderWater(Shader shader);
        void getPos(int &x, int &z){x = pos_world.x>>(4+LOD); z = pos_world.z>>(4+LOD);}

        ChunkData* data, *left, *right, *front, *back;
        
    private:
        GLuint VAONorm, VBONorm, EBONorm, VAOTranslucent, VBOTranslucent, EBOTranslucent, VAOBoard, VBOBoard, EBOBoard, modelMatLoc;
        glm :: ivec3 pos_world;
        vector<Vertex> verticies, translucentVerticies;
        vector<BillboardVertex> billboardVerticies;
        vector<unsigned int> indicies, translucentIndicies, billboardIndicies;
        GLubyte LOD;
        static inline int Floor(float a){return (a<0 ? int(a) : int(a));}
};
namespace ChunkFlags{
    enum CHUNKFLAGS : unsigned char{
        HAS_BASICS = 1,
        HAS_STRUCTURES = 2,
        HAS_MESH = 4,
        LAND_RENDERABLE = 8,
        WATER_RENDERABLE = 16,
        MODIFIED = 32,
        FILE_STORED = 64
    };
};