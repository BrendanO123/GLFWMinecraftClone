#pragma once

#define GL_SILENCE_DEPRECATION
#include <glad/gl.h>

#include "Blocks.h"
#include "ChunkData.h"
#include "Layer.h"
#include <vector>
#include <thread>

#include "Shaders.h"

using namespace std;

/**
 * @brief A vertex for a normal block in a chunk (int style cordinates).
 */
struct Vertex
{
    GLubyte texPosX, texPosY;
    GLbyte posX, posY, posZ;

    Vertex(glm :: vec3 Pos, glm :: vec2 TexPos){
        posX = (char)int(Pos.x); 
        posY=(char)int(Pos.y); 
        posZ=(char)int(Pos.z); 
        texPosX = (unsigned char)TexPos.x;
        texPosY = (unsigned char)TexPos.y;
    }
    Vertex(glm :: vec3 Pos, GLubyte texX, GLubyte texY){
        posX = (char)int(Pos.x); 
        posY=(char)int(Pos.y); 
        posZ=(char)int(Pos.z); 
        texPosX = texX; 
        texPosY = texY;
    }
    Vertex(GLbyte x, GLbyte y, GLbyte z, glm :: vec2 TexPos){
        posX=x; posY=y; posZ=z; 
        texPosX = (unsigned char)TexPos.x; texPosY = (unsigned char)TexPos.y;
    }
    Vertex(GLbyte x, GLbyte y, GLbyte z, GLubyte texX, GLubyte texY){posX=x; posY=y; posZ=z; texPosX = texX; texPosY = texY;}
    Vertex(){posX = 0; posY = 0; posZ = 0; texPosX = 0; texPosY = 0;}
};

/**
 * @brief A vertex for a billboard block (such as a flower or tall grass) in a chunk (float cordinates). 
 */
struct BillboardVertex
{
    glm :: vec3 pos;
    GLubyte texPosX, texPosY;

    BillboardVertex(glm :: vec3 Pos, glm :: vec2 TexPos){pos=Pos; texPosX = (unsigned char)TexPos.x; texPosY = (unsigned char)TexPos.y;}
    BillboardVertex(glm :: vec3 Pos, GLubyte texX, GLubyte texY){pos=Pos; texPosX = texX; texPosY = texY;}
    BillboardVertex(){pos= glm ::vec3(1); texPosX = 0; texPosY = 0;}
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
        void getPos(int &x, int &z){x = int(pos_world.x/(1<<(4+LOD))); z = int(pos_world.z/(1<<(4+LOD)));}

        ChunkData* data, *left, *right, *front, *back;
        
    private:
        GLuint VAONorm, VBONorm, EBONorm, VAOTranslucent, VBOTranslucent, EBOTranslucent, VAOBoard, VBOBoard, EBOBoard, modelMatLoc;
        glm :: vec3 pos_world;
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