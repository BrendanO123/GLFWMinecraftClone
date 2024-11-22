#include "Chunk.h"
#include "Blocks.h"
#include "Block.h"
#include "WorldGen.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string.h>

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

Chunk :: Chunk(GLuint lod, glm :: ivec2 chunkPos) : LOD(lod){
    pos_world = glm ::vec3(((int)chunkPos.x) << (4+LOD), 0, ((int)chunkPos.y) << (4+LOD)); //will niot actually work if LOD is changed
}
Chunk :: ~Chunk(){
    
    glDeleteBuffers(1, &VBONorm);
    glDeleteBuffers(1, &EBONorm);
    glDeleteVertexArrays(1, &VAONorm);
    glDeleteBuffers(1, &VBOTranslucent);
    glDeleteBuffers(1, &EBOTranslucent);
    glDeleteVertexArrays(1, &VAOTranslucent);
    glDeleteBuffers(1, &VBOBoard);
    glDeleteBuffers(1, &EBOBoard);
    glDeleteVertexArrays(1, &VAOBoard);
}

void Chunk :: genChunkMesh(){
    GLuint vOffset=0, transLVOff = 0, BoardVOff = 0, index, y;
    Block block, adjacentBlock;
    GLubyte type, adjacentType;
    vector<GLubyte> layer;
    bool transL;

    int x, z; getPos(x, z);

    for(int i=data->data.size()-1; i>=0; i--){
        for(GLubyte x=0; x<16; x++){
            for(GLbyte z=0; z<16; z++){
                index = z + (int(x) << 4);
                type = data->data.at(i).data[index];
                block = Blocks :: blocks[type];
                if(type){
                    y=data->data.at(i).y;
                    layer=data->data.at(i).data;
                    using namespace Blocks;{
                        if(block.flagByte & BILLBOARD_BIT){

                            //positive front
                            billboardVerticies.emplace_back(BillboardVertex(glm :: vec3(x+0.14645f, y, -0.85355f-z), block.sideLowX, block.sideLowY));
                            billboardVerticies.emplace_back(BillboardVertex(glm :: vec3(x+0.85355f, y, -0.14645f-z), block.sideHighX, block.sideLowY));
                            billboardVerticies.emplace_back(BillboardVertex(glm :: vec3(x+0.14645f, y+1, -0.85355f-z), block.sideLowX, block.sideHighY));
                            billboardVerticies.emplace_back(BillboardVertex(glm :: vec3(x+0.85355f, y+1, -0.14645f-z), block.sideHighX, block.sideHighY));

                            billboardIndicies.push_back(BoardVOff); billboardIndicies.push_back(BoardVOff+2); billboardIndicies.push_back(BoardVOff+1);
                            billboardIndicies.push_back(BoardVOff+3); billboardIndicies.push_back(BoardVOff+1); billboardIndicies.push_back(BoardVOff+2);
                            BoardVOff+=4;

                            //negative front
                            billboardVerticies.emplace_back(BillboardVertex(glm :: vec3(x+0.14645f, y, -0.14645f-z), block.sideLowX, block.sideLowY));
                            billboardVerticies.emplace_back(BillboardVertex(glm :: vec3(x+0.85355f, y, -0.85355f-z), block.sideHighX, block.sideLowY));
                            billboardVerticies.emplace_back(BillboardVertex(glm :: vec3(x+0.14645f, y+1, -0.14645f-z), block.sideLowX, block.sideHighY));
                            billboardVerticies.emplace_back(BillboardVertex(glm :: vec3(x+0.85355f, y+1, -0.85355f-z), block.sideHighX, block.sideHighY));

                            billboardIndicies.push_back(BoardVOff); billboardIndicies.push_back(BoardVOff+2); billboardIndicies.push_back(BoardVOff+1);
                            billboardIndicies.push_back(BoardVOff+3); billboardIndicies.push_back(BoardVOff+1); billboardIndicies.push_back(BoardVOff+2);
                            BoardVOff+=4;
                        }
                        else{

                            transL = (block.flagByte & TRANSLUCENT_BIT); //transparency check

                            //front quad
                            if(z==0){
                                adjacentType = front->findBlock(GLubyte(15 + (int(x)<<4)), y);
                                adjacentBlock = blocks[adjacentType];
                            }
                            else{
                                adjacentType = layer[z-1 + (int(x) << 4)];
                                adjacentBlock = blocks[adjacentType];
                            }

                            if(((adjacentBlock.flagByte & TRANSPARENT_BIT) != 0) || (((adjacentBlock.flagByte & TRANSLUCENT_BIT) != 0) && (adjacentType!=type))){
                                if(transL){
                                    translucentVerticies.emplace_back(Vertex(x, y, -z, block.sideLowX, block.sideLowY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y, -z, block.sideHighX, block.sideLowY));
                                    translucentVerticies.emplace_back(Vertex(x, y+1, -z, block.sideLowX, block.sideHighY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y+1, -z, block.sideHighX, block.sideHighY));

                                    translucentIndicies.push_back(transLVOff); translucentIndicies.push_back(transLVOff+2); translucentIndicies.push_back(transLVOff+1);
                                    translucentIndicies.push_back(transLVOff+3); translucentIndicies.push_back(transLVOff+1); translucentIndicies.push_back(transLVOff+2);
                                    transLVOff+=4;
                                }
                                else{
                                    verticies.emplace_back(Vertex(x, y, -z, block.sideLowX, block.sideLowY));
                                    verticies.emplace_back(Vertex(x+1, y, -z, block.sideHighX, block.sideLowY));
                                    verticies.emplace_back(Vertex(x, y+1, -z, block.sideLowX, block.sideHighY));
                                    verticies.emplace_back(Vertex(x+1, y+1, -z, block.sideHighX, block.sideHighY));

                                    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                    vOffset+=4;
                                }
                            }

                            //right quad
                            if(x==15){
                                adjacentType = right->findBlock(GLubyte(z), y);
                                adjacentBlock = blocks[adjacentType];
                            }
                            else{
                                adjacentType = layer[z + (int(x+1) << 4)];
                                adjacentBlock = blocks[adjacentType];
                            }

                            if(((adjacentBlock.flagByte & TRANSPARENT_BIT) != 0) || (((adjacentBlock.flagByte & TRANSLUCENT_BIT) != 0) && (adjacentType!=type))){
                                if(transL){
                                    translucentVerticies.emplace_back(Vertex(x+1, y, -z, block.sideLowX, block.sideLowY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y, -z-1, block.sideHighX, block.sideLowY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y+1, -z, block.sideLowX, block.sideHighY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y+1, -z-1, block.sideHighX, block.sideHighY));

                                    translucentIndicies.push_back(transLVOff); translucentIndicies.push_back(transLVOff+2); translucentIndicies.push_back(transLVOff+1);
                                    translucentIndicies.push_back(transLVOff+3); translucentIndicies.push_back(transLVOff+1); translucentIndicies.push_back(transLVOff+2);
                                    transLVOff+=4;
                                }
                                else{
                                    verticies.emplace_back(Vertex(x+1, y, -z, block.sideLowX, block.sideLowY));
                                    verticies.emplace_back(Vertex(x+1, y, -z-1, block.sideHighX, block.sideLowY));
                                    verticies.emplace_back(Vertex(x+1, y+1, -z, block.sideLowX, block.sideHighY));
                                    verticies.emplace_back(Vertex(x+1, y+1, -z-1, block.sideHighX, block.sideHighY));

                                    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                    vOffset+=4;
                                }
                            }

                            //back quad
                            if(z==15){
                                adjacentType = back->findBlock(GLubyte(0 + (int(x)<<4)), y);
                                adjacentBlock = blocks[adjacentType];
                            }
                            else{
                                adjacentType = layer[z+1 + (int(x) << 4)];
                                adjacentBlock = blocks[adjacentType];
                            }

                            if(((adjacentBlock.flagByte & TRANSPARENT_BIT) != 0) || (((adjacentBlock.flagByte & TRANSLUCENT_BIT) != 0) && (adjacentType!=type))){
                                if(transL){
                                    translucentVerticies.emplace_back(Vertex(x+1, y, -z-1, block.sideLowX, block.sideLowY));
                                    translucentVerticies.emplace_back(Vertex(x, y, -z-1, block.sideHighX, block.sideLowY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y+1, -z-1, block.sideLowX, block.sideHighY));
                                    translucentVerticies.emplace_back(Vertex(x, y+1, -z-1, block.sideHighX, block.sideHighY));

                                    translucentIndicies.push_back(transLVOff); translucentIndicies.push_back(transLVOff+2); translucentIndicies.push_back(transLVOff+1);
                                    translucentIndicies.push_back(transLVOff+3); translucentIndicies.push_back(transLVOff+1); translucentIndicies.push_back(transLVOff+2);
                                    transLVOff+=4;
                                }
                                else{
                                    verticies.emplace_back(Vertex(x+1, y, -z-1, block.sideLowX, block.sideLowY));
                                    verticies.emplace_back(Vertex(x, y, -z-1, block.sideHighX, block.sideLowY));
                                    verticies.emplace_back(Vertex(x+1, y+1, -z-1, block.sideLowX, block.sideHighY));
                                    verticies.emplace_back(Vertex(x, y+1, -z-1, block.sideHighX, block.sideHighY));

                                    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                    vOffset+=4;
                                }
                            }

                            //left quad
                            if(x==0){
                                adjacentType = left->findBlock(GLubyte(z) + (15<<4), y);
                                adjacentBlock = blocks[adjacentType];
                            }
                            else{
                                adjacentType = layer[z + (int(x-1) << 4)];
                                adjacentBlock = blocks[adjacentType];
                            }

                            if(((adjacentBlock.flagByte & TRANSPARENT_BIT) != 0) || (((adjacentBlock.flagByte & TRANSLUCENT_BIT) != 0) && (adjacentType!=type))){
                                if(transL){
                                    translucentVerticies.emplace_back(Vertex(x, y, -z-1, block.sideLowX, block.sideLowY));
                                    translucentVerticies.emplace_back(Vertex(x, y, -z, block.sideHighX, block.sideLowY));
                                    translucentVerticies.emplace_back(Vertex(x, y+1, -z-1, block.sideLowX, block.sideHighY));
                                    translucentVerticies.emplace_back(Vertex(x, y+1, -z, block.sideHighX, block.sideHighY));

                                    translucentIndicies.push_back(transLVOff); translucentIndicies.push_back(transLVOff+2); translucentIndicies.push_back(transLVOff+1);
                                    translucentIndicies.push_back(transLVOff+3); translucentIndicies.push_back(transLVOff+1); translucentIndicies.push_back(transLVOff+2);
                                    transLVOff+=4;
                                }
                                else{
                                    verticies.emplace_back(Vertex(x, y, -z-1, block.sideLowX, block.sideLowY));
                                    verticies.emplace_back(Vertex(x, y, -z, block.sideHighX, block.sideLowY));
                                    verticies.emplace_back(Vertex(x, y+1, -z-1, block.sideLowX, block.sideHighY));
                                    verticies.emplace_back(Vertex(x, y+1, -z, block.sideHighX, block.sideHighY));

                                    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                    vOffset+=4;
                                }
                            }

                            //top quad
                            if(i == data->data.size()-1){
                                adjacentType = AIR;
                                adjacentBlock = blocks[adjacentType];
                            }
                            else{
                                if(data->data.at(i+1).y == y+1){
                                    adjacentType = data->data.at(i+1).data[z + (int(x) << 4)];
                                    adjacentBlock = blocks[adjacentType];
                                }
                                else{
                                    adjacentType = AIR;
                                    adjacentBlock = blocks[adjacentType];
                                }
                            }

                            if(((adjacentBlock.flagByte & TRANSPARENT_BIT) != 0) || (((adjacentBlock.flagByte & TRANSLUCENT_BIT) != 0) && (adjacentType!=type))){
                                if(transL){
                                    translucentVerticies.emplace_back(Vertex(x, y+1, -z, block.topLowX, block.topLowY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y+1, -z, block.topHighX, block.topLowY));
                                    translucentVerticies.emplace_back(Vertex(x, y+1, -z-1, block.topLowX, block.topHighY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y+1, -z-1, block.topHighX, block.topHighY));

                                    translucentIndicies.push_back(transLVOff); translucentIndicies.push_back(transLVOff+2); translucentIndicies.push_back(transLVOff+1);
                                    translucentIndicies.push_back(transLVOff+3); translucentIndicies.push_back(transLVOff+1); translucentIndicies.push_back(transLVOff+2);
                                    transLVOff+=4;
                                }
                                else{
                                    verticies.emplace_back(Vertex(x, y+1, -z, block.topLowX, block.topLowY));
                                    verticies.emplace_back(Vertex(x+1, y+1, -z, block.topHighX, block.topLowY));
                                    verticies.emplace_back(Vertex(x, y+1, -z-1, block.topLowX, block.topHighY));
                                    verticies.emplace_back(Vertex(x+1, y+1, -z-1, block.topHighX, block.topHighY));

                                    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                    vOffset+=4;
                                }
                            }

                            //bottom quad
                            if(i==0){
                                adjacentType = AIR;
                                adjacentBlock = blocks[adjacentType];
                            }
                            else{
                                if(data->data.at(i-1).y == y-1){
                                    adjacentType = data->data.at(i-1).data[z + (int(x) << 4)];
                                    adjacentBlock = blocks[adjacentType];
                                }
                                else{
                                    adjacentType = AIR;
                                    adjacentBlock = blocks[adjacentType];
                                }
                            }

                            if(((adjacentBlock.flagByte & TRANSPARENT_BIT) != 0) || (((adjacentBlock.flagByte & TRANSLUCENT_BIT) != 0) && (adjacentType!=type))){
                                if(transL){
                                    translucentVerticies.emplace_back(Vertex(x, y, -z-1, block.bottomLowX, block.bottomLowY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y, -z-1, block.bottomHighX, block.bottomLowY));
                                    translucentVerticies.emplace_back(Vertex(x, y, -z, block.bottomLowX, block.bottomHighY));
                                    translucentVerticies.emplace_back(Vertex(x+1, y, -z, block.bottomHighX, block.bottomHighY));

                                    translucentIndicies.push_back(transLVOff); translucentIndicies.push_back(transLVOff+2); translucentIndicies.push_back(transLVOff+1);
                                    translucentIndicies.push_back(transLVOff+3); translucentIndicies.push_back(transLVOff+1); translucentIndicies.push_back(transLVOff+2);
                                    transLVOff+=4;
                                }
                                else{
                                    verticies.emplace_back(Vertex(x, y, -z-1, block.bottomLowX, block.bottomLowY));
                                    verticies.emplace_back(Vertex(x+1, y, -z-1, block.bottomHighX, block.bottomLowY));
                                    verticies.emplace_back(Vertex(x, y, -z, block.bottomLowX, block.bottomHighY));
                                    verticies.emplace_back(Vertex(x+1, y, -z, block.bottomHighX, block.bottomHighY));

                                    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                    vOffset+=4;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    flagByte |= ChunkFlags :: GENERATED;
}

void Chunk :: render(Shader shader){
    
    if(!(flagByte & ChunkFlags :: READY)){
        if(!(flagByte & ChunkFlags :: GENERATED)){return;}
        glGenVertexArrays(1, &VAONorm);
        glBindVertexArray(VAONorm);

        glGenBuffers(1, &VBONorm);
        glBindBuffer(GL_ARRAY_BUFFER, VBONorm);
        glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), verticies.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBONorm);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBONorm);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);

        GLuint posLoc = glGetAttribLocation(shader.program, "vPos");
        GLuint vtexPos_location = glGetAttribLocation(shader.program, "vtexPos");
        glEnableVertexAttribArray(vtexPos_location);
        glVertexAttribPointer(vtexPos_location, 2, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, texPosX)));
        glEnableVertexAttribArray(posLoc);
        glVertexAttribPointer(posLoc, 3, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, posX)));



        glGenVertexArrays(1, &VAOTranslucent);
        glBindVertexArray(VAOTranslucent);

        glGenBuffers(1, &VBOTranslucent);
        glBindBuffer(GL_ARRAY_BUFFER, VBOTranslucent);
        glBufferData(GL_ARRAY_BUFFER, translucentVerticies.size() * sizeof(Vertex), translucentVerticies.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &VBOTranslucent);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOTranslucent);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, translucentIndicies.size() * sizeof(GLuint), translucentIndicies.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(vtexPos_location);
        glVertexAttribPointer(vtexPos_location, 2, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, texPosX)));
        glEnableVertexAttribArray(posLoc);
        glVertexAttribPointer(posLoc, 3, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, posX)));



        glGenVertexArrays(1, &VAOBoard);
        glBindVertexArray(VAOBoard);

        glGenBuffers(1, &VBOBoard);
        glBindBuffer(GL_ARRAY_BUFFER, VBOBoard);
        glBufferData(GL_ARRAY_BUFFER, billboardVerticies.size() * sizeof(BillboardVertex), billboardVerticies.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBOBoard);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOBoard);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, billboardIndicies.size() * sizeof(GLuint), billboardIndicies.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(posLoc);
        glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(BillboardVertex), (void*)(offsetof(BillboardVertex, pos)));
        glEnableVertexAttribArray(vtexPos_location);
        glVertexAttribPointer(vtexPos_location, 2, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(BillboardVertex), (void*)(offsetof(BillboardVertex, texPosX)));

        modelMatLoc = glGetUniformLocation(shader.program, "model");
        flagByte |= ChunkFlags :: READY;
    }

    glm :: mat4 model = glm ::mat4(1.0f);
    model = glm :: translate(model, pos_world);
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm :: value_ptr(model));

    glEnable(GL_CULL_FACE);
    glBindVertexArray(VAONorm);
    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);

    glDisable(GL_CULL_FACE);
    glBindVertexArray(VAOBoard);
    glDrawElements(GL_TRIANGLES, billboardIndicies.size(), GL_UNSIGNED_INT, 0);

    glEnable(GL_BLEND);
    //only water and other liquid textues will want cull face off 
    //so if I add other translucent blocks like stained glass I will have to break this into liquid VAO and translucent VAO
    //the liquid VAO having no cull face and the normal translucent VAO having cull face
    glBindVertexArray(VAOTranslucent);
    glDrawElements(GL_TRIANGLES, translucentIndicies.size(), GL_UNSIGNED_INT, 0);
    glDisable(GL_BLEND);
}