#include "WorldGen.h"

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

            NW->place(target, glm :: i8vec2(-16, -16));
            N->place(target, glm :: i8vec2(0, 16));
            NE->place(target, glm :: i8vec2(16, -16));

            W->place(target, glm :: i8vec2(-16, 0));
            E->place(target, glm :: i8vec2(16, 0));

            SW->place(target, glm :: i8vec2(-16, 16));
            S->place(target, glm :: i8vec2(0, -16));
            SE->place(target, glm :: i8vec2(16, 16));
        }

void WorldGen :: getChunkBasics(int x, int z, int chunkSize, ChunkData* chunkData, noise :: Fractal fractal){
    //TODO: actual world gen
    using namespace noise;
    {
    chunkData->pos=glm :: ivec2(x,z);

    chunkData->data.clear();
    NoiseReturnStruct noiseValues = fractal.getNoise(glm :: ivec2(x, z));
    int minHeight = noiseValues.minHeight;
    int maxHeight = noiseValues.maxHeight;

    for(int iterX =0; iterX < chunkSize; iterX++){
        for(int iterZ=0; iterZ<chunkSize; iterZ++){
            if(noiseValues.TerrainHeight[iterZ + int(iterX << 4)] < minHeight){minHeight = noiseValues.TerrainHeight[iterZ + int(iterX << 4)];}
            if(noiseValues.TerrainHeight[iterZ + int(iterX << 4)] > maxHeight){maxHeight = noiseValues.TerrainHeight[iterZ + int(iterX << 4)];}
        }
    }
    if(maxHeight < noise :: Fractal :: waterLevel){maxHeight = noise :: Fractal :: waterLevel;}

    constexpr int partialStone_Thickness = 7;
    int lowest;
    if(fullStone){
        lowest = 0;
        chunkData->data.reserve(maxHeight);
        for(int i = 0; i < maxHeight; i++){
            chunkData->data.emplace_back((unsigned char)i);
            if(i < minHeight-3){
                fillLayer(i, chunkSize, chunkData, Blocks :: STONE);
            }
        }
    }
    else{
        lowest = max(0, minHeight-partialStone_Thickness);
        chunkData->data.reserve(maxHeight - lowest);
        for(int i = lowest; i < maxHeight; i++){
            chunkData->data.emplace_back((unsigned char)i);
        }
    }

    for(int iterX = 0; iterX < chunkSize; iterX++){
        for(int iterZ = 0; iterZ < chunkSize; iterZ++){
            if(fullStone){
                for(int i = minHeight-3; i<noiseValues.TerrainHeight[iterZ + int(iterX << 4)] - 3; i++){
                    chunkData->data.at(i).data[iterZ + (iterX<<4)] = Blocks :: STONE;
                }
            }
            else{
                for(int i = max(0, noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-partialStone_Thickness) - lowest; i<noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-3 - lowest; i++){
                    chunkData->data.at(i).data[iterZ + (iterX<<4)] = Blocks :: STONE;
                }
            }

            for(int i = noiseValues.TerrainHeight[iterZ + int(iterX << 4)] - lowest; i < noise :: Fractal :: waterLevel - lowest; i++){
                    chunkData->data.at(i).data[iterZ + (iterX<<4)] = Blocks :: WATER;
            }

            if(noiseValues.surfaceType[iterZ + int(iterX << 4)] == Blocks :: GRASS){
                chunkData->data.at(noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-3 - lowest).data[iterZ + (iterX<<4)] = Blocks :: DIRT;
                chunkData->data.at(noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-2 - lowest).data[iterZ + (iterX<<4)] = Blocks :: DIRT;
                chunkData->data.at(noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-1 - lowest).data[iterZ + (iterX<<4)] = Blocks :: GRASS;
                
                
                /*if(iterX == 0 || iterX == 15 || iterZ == 0 || iterZ == 15){
                    chunkData->data.at(noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-1).data[iterZ + (iterX<<4)] = Blocks :: DIRT;
                }*/
            }
            else{
                chunkData->data.at(noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-3 - lowest).data[iterZ + (iterX<<4)] = noiseValues.surfaceType[iterZ + int(iterX << 4)];
                chunkData->data.at(noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-2 - lowest).data[iterZ + (iterX<<4)] = noiseValues.surfaceType[iterZ + int(iterX << 4)];
                chunkData->data.at(noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-1 - lowest).data[iterZ + (iterX<<4)] = noiseValues.surfaceType[iterZ + int(iterX << 4)];

                /*if(iterX == 0 || iterX == 15 || iterZ == 0 || iterZ == 15){
                    chunkData->data.at(noiseValues.TerrainHeight[iterZ + int(iterX << 4)]-1).data[iterZ + (iterX<<4)] = Blocks :: DIRT;
                }*/
            }
        }
    }
    //chunkData->data.at(noiseValues.TerrainHeight[1 + int(2 << 4)]-1).data[1 + (2<<4)] = Blocks :: STONE;
    

    for(int iterX = 0; iterX < chunkSize; iterX++){
        for(int iterZ = 0; iterZ < chunkSize; iterZ++){
            GLubyte type = noiseValues.foliage[iterZ + int(iterX << 4)];
            if(type != (unsigned char) 255){
                int offset = (type == Structures :: OAK_TREE ? -1 : 0);
                WorldGen :: placeStruct(
                    chunkData, 
                    type, 
                    iterX, 
                    noiseValues.TerrainHeight[iterZ + int(iterX << 4)] + offset, 
                    iterZ
                );
                
            }
        }
    }

    }
}