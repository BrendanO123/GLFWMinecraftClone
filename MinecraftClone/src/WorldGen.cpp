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

using namespace std;

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

void WorldGen :: getChunkBasics(int x, int z, int chunkSize, ChunkData* chunkData){
    //TODO: actual world gen

    chunkData->pos=glm :: ivec2(x,z);

    chunkData->data.clear();
    chunkData->data.reserve(12);

    chunkData->data.emplace_back((unsigned char)0); fillLayer(0, chunkSize, chunkData, Blocks :: STONE);
    chunkData->data.emplace_back((unsigned char)1); fillLayer(1, chunkSize, chunkData, Blocks :: STONE);
    chunkData->data.emplace_back((unsigned char)2); fillLayer(2, chunkSize, chunkData, Blocks :: STONE);
    chunkData->data.emplace_back((unsigned char)3); fillLayer(3, chunkSize, chunkData, Blocks :: DIRT);
    chunkData->data.emplace_back((unsigned char)4); fillLayer(4, chunkSize, chunkData, Blocks :: DIRT);
    chunkData->data.emplace_back((unsigned char)5); fillLayer(5, chunkSize, chunkData, Blocks :: GRASS);
    chunkData->data.emplace_back((unsigned char)6);
    chunkData->data.at(6).data[0 + (0<<4)] = Blocks :: SHORT_GRASS;
    chunkData->data.at(6).data[1 + (0<<4)] = Blocks :: TALL_GRASS_BOTTOM;
    chunkData->data.at(6).data[0 + (1<<4)] = Blocks :: ROSE;
    chunkData->data.at(6).data[1 + (1<<4)] = Blocks :: TULIP_WHITE;
    chunkData->data.at(6).data[0 + (2<<4)] = Blocks :: TULIP_ORANGE;
    chunkData->data.at(6).data[1 + (2<<4)] = Blocks :: TULIP_PINK;


    chunkData->data.emplace_back((unsigned char)7);
    chunkData->data.at(7).data[1 + (0<<4)] = Blocks :: TALL_GRASS_TOP;
    chunkData->data.emplace_back((unsigned char)8);
    chunkData->data.emplace_back((unsigned char)9);
    chunkData->data.emplace_back((unsigned char)10);
    chunkData->data.emplace_back((unsigned char)11);

    placeStruct(chunkData, Structures :: OAK_TREE, 2, 5, 2);
    placeStruct(chunkData, Structures :: OAK_TREE, 6, 5, 5);

    placeStruct(chunkData, Structures :: POND, 12, 3, 14);

}