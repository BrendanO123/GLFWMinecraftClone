#include "Chunk.h"
#include "Blocks.h"
#include "Block.h"
#include "WorldGen.h"

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string.h>

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

Chunk :: Chunk(GLuint lod, glm :: vec2 chunkPos){
    LOD = lod; pos_world = glm ::vec3(((int)chunkPos.x) << (4+LOD), 0, ((int)chunkPos.y) << (4+LOD));

    chunkThread = std :: thread(&Chunk :: genChunk, this);
}
Chunk :: ~Chunk(){
    if (chunkThread.joinable()){chunkThread.join();}
    else{std :: cout << "Thread Join Failed" << std :: endl;}
    
    glDeleteBuffers(1, &VBONorm);
    glDeleteBuffers(1, &EBONorm);
    glDeleteVertexArrays(1, &VAONorm);
    glDeleteBuffers(1, &VBOBoard);
    glDeleteBuffers(1, &EBOBoard);
    glDeleteVertexArrays(1, &VAOBoard);
}

void Chunk :: genChunk(){

    //TODO: fetch blocks adjacent to chunk
    
    GLuint vOffset=0, BoardVOff = 0, index, y;
    Block block, adjacentBlock;
    GLubyte type;
    vector<GLubyte> layer;

    int x, z; getPos(x, z);
    WorldGen :: generateChunkData(x, z, (1<<(4+LOD)), &data);

    for(int i=data.size()-1; i>=0; i--){
        for(GLubyte x=0; x<16; x++){
            for(GLbyte z=0; z<16; z++){
                index = z + (int(x) << 4);
                type = data[i].data[index];
                block = Blocks :: blocks[type];
                if(type){
                    y=data[i].y;
                    layer=data[i].data;
                    using namespace Blocks;{
                        if(block.flagByte & BILLBOARD_BIT){

                            //positive front
                            billboardVerticies.push_back(BillboardVertex(glm :: vec3(x+0.14645f, y, -0.85355f-z), block.sideLowX, block.sideLowY));
                            billboardVerticies.push_back(BillboardVertex(glm :: vec3(x+0.85355f, y, -0.14645f-z), block.sideHighX, block.sideLowY));
                            billboardVerticies.push_back(BillboardVertex(glm :: vec3(x+0.14645f, y+1, -0.85355f-z), block.sideLowX, block.sideHighY));
                            billboardVerticies.push_back(BillboardVertex(glm :: vec3(x+0.85355f, y+1, -0.14645f-z), block.sideHighX, block.sideHighY));

                            billboardIndicies.push_back(BoardVOff); billboardIndicies.push_back(BoardVOff+2); billboardIndicies.push_back(BoardVOff+1);
                            billboardIndicies.push_back(BoardVOff+3); billboardIndicies.push_back(BoardVOff+1); billboardIndicies.push_back(BoardVOff+2);
                            BoardVOff+=4;

                            //negative front
                            billboardVerticies.push_back(BillboardVertex(glm :: vec3(x+0.14645f, y, -0.14645f-z), block.sideLowX, block.sideLowY));
                            billboardVerticies.push_back(BillboardVertex(glm :: vec3(x+0.85355f, y, -0.85355f-z), block.sideHighX, block.sideLowY));
                            billboardVerticies.push_back(BillboardVertex(glm :: vec3(x+0.14645f, y+1, -0.14645f-z), block.sideLowX, block.sideHighY));
                            billboardVerticies.push_back(BillboardVertex(glm :: vec3(x+0.85355f, y+1, -0.85355f-z), block.sideHighX, block.sideHighY));

                            billboardIndicies.push_back(BoardVOff); billboardIndicies.push_back(BoardVOff+2); billboardIndicies.push_back(BoardVOff+1);
                            billboardIndicies.push_back(BoardVOff+3); billboardIndicies.push_back(BoardVOff+1); billboardIndicies.push_back(BoardVOff+2);
                            BoardVOff+=4;
                        }
                        else{

                            //front quad
                            if(z==0){
                                //TODO: check neighbooring chunks to cull faces along border
                                adjacentBlock = blocks[AIR];
                            }
                            else{
                                adjacentBlock = blocks[layer[z-1 + (int(x) << 4)]];
                            }

                            if(adjacentBlock.flagByte & TRANSPARENT_BIT){
                                verticies.push_back(Vertex(x, y, -z, block.sideLowX, block.sideLowY));
                                verticies.push_back(Vertex(x+1, y, -z, block.sideHighX, block.sideLowY));
                                verticies.push_back(Vertex(x, y+1, -z, block.sideLowX, block.sideHighY));
                                verticies.push_back(Vertex(x+1, y+1, -z, block.sideHighX, block.sideHighY));

                                indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                vOffset+=4;
                            }

                            //right quad
                            if(x==16){
                                //TODO: check neighbooring chunks to cull faces along border
                                adjacentBlock = blocks[AIR];
                            }
                            else{
                                adjacentBlock = blocks[layer[z + (int(x+1) << 4)]];
                            }

                            if(adjacentBlock.flagByte & TRANSPARENT_BIT){
                                verticies.push_back(Vertex(x+1, y, -z, block.sideLowX, block.sideLowY));
                                verticies.push_back(Vertex(x+1, y, -z-1, block.sideHighX, block.sideLowY));
                                verticies.push_back(Vertex(x+1, y+1, -z, block.sideLowX, block.sideHighY));
                                verticies.push_back(Vertex(x+1, y+1, -z-1, block.sideHighX, block.sideHighY));

                                indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                vOffset+=4;
                            }

                            //back quad
                            if(z==16){
                                //TODO: check neighbooring chunks to cull faces along border
                                adjacentBlock = blocks[AIR];
                            }
                            else{
                                adjacentBlock = blocks[layer[z+1 + (int(x) << 4)]];
                            }

                            if(adjacentBlock.flagByte & TRANSPARENT_BIT){
                                verticies.push_back(Vertex(x+1, y, -z-1, block.sideLowX, block.sideLowY));
                                verticies.push_back(Vertex(x, y, -z-1, block.sideHighX, block.sideLowY));
                                verticies.push_back(Vertex(x+1, y+1, -z-1, block.sideLowX, block.sideHighY));
                                verticies.push_back(Vertex(x, y+1, -z-1, block.sideHighX, block.sideHighY));

                                indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                vOffset+=4;
                            }

                            //left quad
                            if(x==0){
                                //TODO: check neighbooring chunks to cull faces along border
                                adjacentBlock = blocks[AIR];
                            }
                            else{
                                adjacentBlock = blocks[layer[z + (int(x-1) << 4)]];
                            }

                            if(adjacentBlock.flagByte & TRANSPARENT_BIT){
                                verticies.push_back(Vertex(x, y, -z-1, block.sideLowX, block.sideLowY));
                                verticies.push_back(Vertex(x, y, -z, block.sideHighX, block.sideLowY));
                                verticies.push_back(Vertex(x, y+1, -z-1, block.sideLowX, block.sideHighY));
                                verticies.push_back(Vertex(x, y+1, -z, block.sideHighX, block.sideHighY));

                                indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                vOffset+=4;
                            }

                            //top quad
                            if(i == data.size()){
                                adjacentBlock = blocks[AIR];
                            }
                            else{
                                if(data[i+1].y == y+1){
                                    adjacentBlock = blocks[data[i+1].data[z + (int(x) << 4)]];
                                }
                                else{
                                    adjacentBlock = blocks[AIR];
                                }
                            }

                            if(adjacentBlock.flagByte & TRANSPARENT_BIT){
                                verticies.push_back(Vertex(x, y+1, -z, block.topLowX, block.topLowY));
                                verticies.push_back(Vertex(x+1, y+1, -z, block.topHighX, block.topLowY));
                                verticies.push_back(Vertex(x, y+1, -z-1, block.topLowX, block.topHighY));
                                verticies.push_back(Vertex(x+1, y+1, -z-1, block.topHighX, block.topHighY));

                                indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                vOffset+=4;
                            }

                            //bottom quad
                            if(i==0){
                                adjacentBlock = blocks[AIR];
                            }
                            else{
                                if(data[i-1].y == y-1){
                                    adjacentBlock = blocks[data[i-1].data[z + (int(x) << 4)]];
                                }
                                else{
                                    adjacentBlock = blocks[AIR];
                                }
                            }

                            if(adjacentBlock.flagByte & TRANSPARENT_BIT){
                                verticies.push_back(Vertex(x, y, -z-1, block.bottomLowX, block.bottomLowY));
                                verticies.push_back(Vertex(x+1, y, -z-1, block.bottomHighX, block.bottomLowY));
                                verticies.push_back(Vertex(x, y, -z, block.bottomLowX, block.bottomHighY));
                                verticies.push_back(Vertex(x+1, y, -z, block.bottomHighX, block.bottomHighY));

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
}