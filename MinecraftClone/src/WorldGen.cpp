#include "WorldGen.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Blocks.h"
#include "Structures.h"

using namespace std;


void WorldGen :: fillLayer(int index, int chunkSize, ChunkData* chunkData, GLubyte type){
    for(int x=0; x<16; x++){
        for(int z=0; z<16; z++){
            chunkData->data.at(index).data[z + (x<<4)] = type;
        }
    }
}

void WorldGen :: placeStruct(ChunkData* chunkData, GLubyte id, GLubyte x, GLubyte y, GLubyte z){
    bool overspill;
    overspill = Structures :: Structs[id].placeSelf(*chunkData, x, y, z);
    if(overspill){
        StructNode* newStruct = new StructNode(id, x, y, z);
        if(chunkData->Structs.count == 0){
            chunkData->Structs.count++;
            chunkData->Structs.first = newStruct;
            chunkData->Structs.last = newStruct;
        }
        else{
            chunkData->Structs.count++;
            chunkData->Structs.last->next = newStruct;
            chunkData->Structs.last = newStruct;
        }
    }
}

void WorldGen :: resolveStructures(ChunkData* target, 
        ChunkData* NW, ChunkData* N, ChunkData* NE, 
        ChunkData* W,                ChunkData* E, 
        ChunkData* SW, ChunkData* S, ChunkData* SE){

            NW->place(target, glm :: i8vec2(-16, 16));
            N->place(target, glm :: i8vec2(0, 16));
            NE->place(target, glm :: i8vec2(16, 16));

            W->place(target, glm :: i8vec2(-16, 0));
            E->place(target, glm :: i8vec2(16, 0));

            SW->place(target, glm :: i8vec2(-16, -16));
            S->place(target, glm :: i8vec2(0, -16));
            SE->place(target, glm :: i8vec2(16, -16));
        }

void WorldGen :: getChunkBasics(int x, int z, int chunkSize, ChunkData* chunkData, noise :: Fractal fractal){
    //TODO: actual world gen
    using namespace noise;
    {
    chunkData->pos=glm :: ivec2(x,z);

    chunkData->data.clear();

    int minHeight = 127, maxHeight = 0, temp;
    int height[chunkSize][chunkSize];

    NoiseMapSettings settings = NoiseMapSettings(1337, false, noise :: PERLIN, noise :: FBM, 0.008f, 0.5f, 2.0f, 5, 1.0f);
    fractal.noise.calcFracBounding(settings);

    for(int iterX = 0; iterX < chunkSize; iterX++){
        for(int iterZ = 0; iterZ < chunkSize; iterZ++){
            temp = int(35 * fractal.tempFBM(glm :: ivec2(iterX + x * chunkSize, z * chunkSize - iterZ), settings).x + 40);
            height[iterZ][iterX] = temp;
            if(temp < minHeight){minHeight = temp;}
            if(temp > maxHeight){maxHeight = temp;}
        }
    }

    chunkData->data.reserve(maxHeight);
    for(int i = 0; i < maxHeight; i++){
        chunkData->data.emplace_back((unsigned char)i);
        if(i < minHeight-3){
            fillLayer(i, chunkSize, chunkData, Blocks :: STONE);
        }
    }

    for(int iterX = 0; iterX < chunkSize; iterX++){
        for(int iterZ = 0; iterZ < chunkSize; iterZ++){
            for(int i = minHeight-3; i<height[iterZ][iterX] - 3; i++){
                chunkData->data.at(i).data[iterZ + (iterX<<4)] = Blocks :: STONE;
            }

            chunkData->data.at(height[iterZ][iterX]-3).data[iterZ + (iterX<<4)] = Blocks :: DIRT;
            chunkData->data.at(height[iterZ][iterX]-2).data[iterZ + (iterX<<4)] = Blocks :: DIRT;
            chunkData->data.at(height[iterZ][iterX]-1).data[iterZ + (iterX<<4)] = Blocks :: GRASS;
        }
    }

    if(height[1][0] == maxHeight){
        chunkData->data.emplace_back((unsigned char)maxHeight);
        chunkData->data.emplace_back((unsigned char)(maxHeight+1));
    }
    else if(
        height[0][0] == maxHeight || height[0][1] == maxHeight || height[1][1] == maxHeight ||
        height[0][2] == maxHeight || height[1][0] == maxHeight-1 || height[1][2] == maxHeight
        ){
            chunkData->data.emplace_back((unsigned char)maxHeight);
        }
    
    chunkData->data.at(height[0][0]).data[0 + (0<<4)] = Blocks :: SHORT_GRASS;
    chunkData->data.at(height[1][0]).data[1 + (0<<4)] = Blocks :: TALL_GRASS_BOTTOM;
    chunkData->data.at(height[0][1]).data[0 + (1<<4)] = Blocks :: ROSE;
    chunkData->data.at(height[1][1]).data[1 + (1<<4)] = Blocks :: TULIP_WHITE;
    chunkData->data.at(height[0][2]).data[0 + (2<<4)] = Blocks :: TULIP_ORANGE;
    chunkData->data.at(height[1][2]).data[1 + (2<<4)] = Blocks :: TULIP_PINK;

    chunkData->data.at(height[1][0]+1).data[1 + (0<<4)] = Blocks :: TALL_GRASS_TOP;

    WorldGen :: placeStruct(chunkData, Structures :: OAK_TREE, 2, height[2][2]-1, 2);
    WorldGen :: placeStruct(chunkData, Structures :: OAK_TREE, 6, height[5][6]-1, 5);
    }
}