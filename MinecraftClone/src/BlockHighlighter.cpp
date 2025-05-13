#include "BlockHighlighter.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

BlockHighlighter :: ~BlockHighlighter(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}
BlockHighlighter :: BlockHighlighter(Shader shader){

    int vOffset = 0;
    verticies.emplace_back(   -overfill, -overfill,  overfill, ColorPositionX,   ColorPositionY,   4);
    verticies.emplace_back((1+overfill), -overfill,  overfill, ColorPositionX+1, ColorPositionY,   4);
    verticies.emplace_back(   -overfill, 1+overfill, overfill, ColorPositionX,   ColorPositionY+1, 4);
    verticies.emplace_back((1+overfill), 1+overfill, overfill, ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;


    verticies.emplace_back((1+overfill), -overfill,  overfill,      ColorPositionX,   ColorPositionY,   4);
    verticies.emplace_back((1+overfill), -overfill,  (-1-overfill), ColorPositionX+1, ColorPositionY,   4);
    verticies.emplace_back((1+overfill), 1+overfill, overfill,      ColorPositionX,   ColorPositionY+1, 4);
    verticies.emplace_back((1+overfill), 1+overfill, (-1-overfill), ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;


    verticies.emplace_back((1+overfill), -overfill,  (-1-overfill), ColorPositionX,   ColorPositionY,   4);
    verticies.emplace_back(   -overfill, -overfill,  (-1-overfill), ColorPositionX+1, ColorPositionY,   4);
    verticies.emplace_back((1+overfill), 1+overfill, (-1-overfill), ColorPositionX,   ColorPositionY+1, 4);
    verticies.emplace_back(   -overfill, 1+overfill, (-1-overfill), ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;

    verticies.emplace_back(-overfill, -overfill,  (-1-overfill), ColorPositionX,  ColorPositionY,    4);
    verticies.emplace_back(-overfill, -overfill,  overfill,      ColorPositionX+1, ColorPositionY,   4);
    verticies.emplace_back(-overfill, 1+overfill, (-1-overfill), ColorPositionX,   ColorPositionY+1, 4);
    verticies.emplace_back(-overfill, 1+overfill, overfill,      ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;

    verticies.emplace_back(   -overfill, 1+overfill, overfill,      ColorPositionX,   ColorPositionY,   4);
    verticies.emplace_back((1+overfill), 1+overfill, overfill,      ColorPositionX+1, ColorPositionY,   4);
    verticies.emplace_back(   -overfill, 1+overfill, (-1-overfill), ColorPositionX,   ColorPositionY+1, 4);
    verticies.emplace_back((1+overfill), 1+overfill, (-1-overfill), ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;


    verticies.emplace_back(   -overfill, -overfill,   (-1-overfill), ColorPositionX,   ColorPositionY,   4);
    verticies.emplace_back((1+overfill), -overfill,   (-1-overfill), ColorPositionX+1, ColorPositionY,   4);
    verticies.emplace_back(   -overfill, -overfill,   overfill,      ColorPositionX,   ColorPositionY+1, 4);
    verticies.emplace_back((1+overfill), -overfill,   overfill,      ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(FVertex), verticies.data(), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);

    GLuint posLoc = glGetAttribLocation(shader.program, "vPos");
    GLuint heightLoc = glGetAttribLocation(shader.program, "height");
    GLuint vtexPos_location = glGetAttribLocation(shader.program, "vtexPos");
    GLuint vNormalLoc = glGetAttribLocation(shader.program, "normal");
    modelMatLoc = glGetUniformLocation(shader.program, "modelPos");
    invertUniformLoc = glGetUniformLocation(shader.program, "invert");


    glEnableVertexAttribArray(vtexPos_location);
    glVertexAttribPointer(vtexPos_location, 2, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(FVertex), (void*) (offsetof(FVertex, texPosX)));

    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*) (offsetof(FVertex, posX)));

    glEnableVertexAttribArray(heightLoc);
    glVertexAttribPointer(heightLoc, 1, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*) (offsetof(FVertex, posY)));

    glEnableVertexAttribArray(vNormalLoc);
    glVertexAttribPointer(vNormalLoc, 1, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(FVertex), (void*) (offsetof(FVertex, NormalSelector)));
}

void BlockHighlighter :: highlight(glm :: ivec3 position, GLubyte blockType){

    glUniform3iv(modelMatLoc, 1, glm::value_ptr(position));
    glUniform1f(invertUniformLoc, invert);

    Block block = Blocks :: blocks[blockType];

    int sideLowX, sideHighX, sideLowY, sideHighY;
    int topLowX, topHighX, topLowY, topHighY;
    int bottomLowX, bottomHighX, bottomLowY, bottomHighY;

    if((blockType != Blocks :: AIR ) && ((block.flagByte & Blocks :: BILLBOARD_BIT) == 0)){
        sideLowX = block.sideLowX;
        sideHighX = block.sideHighX;
        sideLowY = block.sideLowY;
        sideHighY = block.sideHighY;

        topLowX = block.topLowX;
        topHighX = block.topHighX;
        topLowY = block.topLowY;
        topHighY = block.topHighY;

        bottomLowX = block.bottomLowX;
        bottomHighX = block.bottomHighX;
        bottomLowY = block.bottomLowY;
        bottomHighY = block.bottomHighY;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_BLEND);
        glEnable(GL_CULL_FACE);
    }
    else{
        if(block.flagByte & Blocks :: BILLBOARD_BIT){
            glEnable(GL_BLEND);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_CULL_FACE);
        }
        else{
            glDisable(GL_BLEND);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_CULL_FACE);
        }
        sideLowX = ColorPositionX;
        sideHighX = ColorPositionX+1;
        sideLowY = ColorPositionY;
        sideHighY = ColorPositionY+1;

        topLowX = ColorPositionX;
        topHighX = ColorPositionX+1;
        topLowY = ColorPositionY;
        topHighY = ColorPositionY+1;

        bottomLowX = ColorPositionX;
        bottomHighX = ColorPositionX+1;
        bottomLowY = ColorPositionY;
        bottomHighY = ColorPositionY+1;
    }

    int i = -1;
    for(int j=0; j<4; j++){
        verticies.at(++i).texPosX = sideLowX; verticies.at(i).texPosY = sideLowY;
        verticies.at(++i).texPosX = sideHighX; verticies.at(i).texPosY = sideLowY;
        verticies.at(++i).texPosX = sideLowX; verticies.at(i).texPosY = sideHighY;
        verticies.at(++i).texPosX = sideHighX; verticies.at(i).texPosY = sideHighY;
    }

    verticies.at(++i).texPosX = topLowX; verticies.at(i).texPosY = topLowY;
    verticies.at(++i).texPosX = topHighX; verticies.at(i).texPosY = topLowY;
    verticies.at(++i).texPosX = topLowX; verticies.at(i).texPosY = topHighY;
    verticies.at(++i).texPosX = topHighX; verticies.at(i).texPosY = topHighY;

    verticies.at(++i).texPosX = bottomLowX; verticies.at(i).texPosY = bottomLowY;
    verticies.at(++i).texPosX = bottomHighX; verticies.at(i).texPosY = bottomLowY;
    verticies.at(++i).texPosX = bottomLowX; verticies.at(i).texPosY = bottomHighY;
    verticies.at(++i).texPosX = bottomHighX; verticies.at(i).texPosY = bottomHighY;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(FVertex), verticies.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
}