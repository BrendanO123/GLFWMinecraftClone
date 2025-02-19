#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Shaders.h"

struct FVertex
{
    GLubyte texPosX, texPosY;
    float posX, posZ, posY;
    GLubyte NormalSelector;

    FVertex(glm :: vec3 Pos, glm :: u8vec2 TexPos, GLubyte Normal) : 
        texPosX(TexPos.x), texPosY(TexPos.y),
        posX(Pos.x), posZ(Pos.z), posY(Pos.y),
        NormalSelector(Normal){}

    FVertex(glm :: vec3 Pos, GLubyte texX, GLubyte texY, GLubyte Normal) : 
        texPosX(texX), texPosY(texY),
        posX(Pos.x), posZ(Pos.z), posY(Pos.y),
        NormalSelector(Normal){}
        
    FVertex(float x, float y, float z, glm :: u8vec2 TexPos, GLubyte Normal) : 
        texPosX(TexPos.x), texPosY(TexPos.y),
        posX(x), posZ(z), posY(y),
        NormalSelector(Normal){}
        
    FVertex(float x, float y, float z, GLubyte texX, GLubyte texY, GLubyte Normal) : 
        texPosX((unsigned char)texX), texPosY((unsigned char)texY),
        posX(x), posZ(z), posY(y),
        NormalSelector(Normal){}
        
    FVertex(GLubyte Normal) : 
        texPosX(0), texPosY(0),
        posX(0), posZ(0), posY(0),
        NormalSelector(Normal){}
};

class BlockHighlighter{
    GLuint VAO, VBO, EBO, modelMatLoc;
    vector<FVertex> verticies;
    vector<int> indicies;
    constexpr static const float scale = 1.1f;
    constexpr static const int ColorPositionX = 8 - 1;
    constexpr static const int ColorPositionY = 1 - 1;

    public:
        BlockHighlighter(Shader shader);
        ~BlockHighlighter();
        void highlight(glm :: ivec3 position);
};