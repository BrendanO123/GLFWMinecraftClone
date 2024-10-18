#include "Chunk.h"
#include "Blocks.h"
#include "Block.h"

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
    LOD = lod; pos_world = glm ::vec3(((int)chunkPos.x) << (4+LOD), 0, ((int)chunkPos.x) << (4+LOD));
}

void Chunk :: genChunk(){
    //TODO: terrain generation
    //currently just uses existing chunk data which is currently public
    //I should change to private, add accessor and modifier funcs and introduce terrain gen

    //TODO: fetch blocks adjacent to chunk
    
    GLuint vOffset=0, index, y;
    Block block, adjacentBlock;
    GLubyte type;
    vector<GLubyte> layer;

    glm :: mat4 rot = glm :: mat4(1.f);
    rot = glm :: rotate(rot, glm ::radians(45.0f), glm :: vec3(0.f, 1.f, 0.f));

    for(int i=data.size()-1; i>=0; i--){
        for(GLubyte x=0; x<16; x++){
            for(GLubyte z=0; z<16; z++){
                index = z + (int(x) << 4);
                type = data[i].data[index];
                block = Blocks :: blocks[type];
                if(type){
                    y=data[i].y;
                    layer=data[i].data;
                    using namespace Blocks;{
                        if(block.flagByte & BILLBOARD_BIT){

                            //positive front
                            verticies.push_back(Vertex(glm :: vec3(x+0.14645f, y, -0.85355f-z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.85355f, y, -0.14645f-z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.14645f, y+1, -0.85355f-z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.85355f, y+1, -0.14645f-z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));

                            indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                            indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                            vOffset+=4;

                            //positive back
                            verticies.push_back(Vertex(glm :: vec3(x+0.85355f, y, -0.14645f-z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.14645f, y, -0.85355f-z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.85355f, y+1, -0.14645f-z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.14645f, y+1, -0.85355f-z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));

                            indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                            indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                            vOffset+=4;

                            //negative front
                            verticies.push_back(Vertex(glm :: vec3(x+0.14645f, y, -0.14645f-z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.85355f, y, -0.85355f-z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.14645f, y+1, -0.14645f-z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.85355f, y+1, -0.85355f-z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));

                            indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                            indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                            vOffset+=4;

                            //negative back
                            verticies.push_back(Vertex(glm :: vec3(x+0.85355f, y, -0.85355f-z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.14645f, y, -0.14645f-z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.85355f, y+1, -0.85355f-z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));
                            verticies.push_back(Vertex(glm :: vec3(x+0.14645f, y+1, -0.14645f-z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));

                            indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                            indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                            vOffset+=4;
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
                                verticies.push_back(Vertex(glm :: vec3(x, y, -z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y, -z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x, y+1, -z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y+1, -z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));

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
                                verticies.push_back(Vertex(glm :: vec3(x+1, y, -z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y, -z-1), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y+1, -z), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y+1, -z-1), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));

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
                                verticies.push_back(Vertex(glm :: vec3(x+1, y, -z-1), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x, y, -z-1), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y+1, -z-1), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x, y+1, -z-1), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));

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
                                verticies.push_back(Vertex(glm :: vec3(x, y, -z-1), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x, y, -z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x, y+1, -z-1), glm :: vec2(block.sideLowX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x, y+1, -z), glm :: vec2(block.sideHighX / blockMapW_blocks, 1-(block.sideHighY / blockMapH_blocks))));

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
                                verticies.push_back(Vertex(glm :: vec3(x, y+1, -z), glm :: vec2(block.topLowX / blockMapW_blocks, 1-(block.topLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y+1, -z), glm :: vec2(block.topHighX / blockMapW_blocks, 1-(block.topLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x, y+1, -z-1), glm :: vec2(block.topLowX / blockMapW_blocks, 1-(block.topHighY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y+1, -z-1), glm :: vec2(block.topHighX / blockMapW_blocks, 1-(block.topHighY / blockMapH_blocks))));

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
                                verticies.push_back(Vertex(glm :: vec3(x, y, -z-1), glm :: vec2(block.bottomLowX / blockMapW_blocks, 1-(block.bottomLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y, -z-1), glm :: vec2(block.bottomHighX / blockMapW_blocks, 1-(block.bottomLowY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x, y, -z), glm :: vec2(block.bottomLowX / blockMapW_blocks, 1-(block.bottomHighY / blockMapH_blocks))));
                                verticies.push_back(Vertex(glm :: vec3(x+1, y, -z), glm :: vec2(block.bottomHighX / blockMapW_blocks, 1-(block.bottomHighY / blockMapH_blocks))));

                                indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
                                indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
                                vOffset+=4;
                            }
                        }
                    }
                }
            }
        }
        flagByte |= ChunkFlags :: GENERATED;
    }
}

void Chunk :: render(GLuint modelMatLoc, GLuint vpos_location, GLuint vtexPos_location){
    if(!(flagByte & ChunkFlags :: READY)){
        if(!(flagByte & ChunkFlags :: GENERATED)){return;}
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), verticies.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
        glEnableVertexAttribArray(vtexPos_location);
        glVertexAttribPointer(vtexPos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(glm :: vec3));

        flagByte |= ChunkFlags :: READY;
    }

    glm :: mat4 model = glm ::mat4(1.0f);
    model = glm :: translate(model, /*pos_world*/glm :: vec3(-1.5f, 0.f, -0.5f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm :: value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
}