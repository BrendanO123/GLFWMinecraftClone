#include "WorldGen.h"

#include "Blocks.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

using namespace std;


void fillLayer(int index, int chunkSize, ChunkData* chunkData, GLubyte type){
    for(int x=0; x<16; x++){
        for(int z=0; z<16; z++){
            chunkData->data.at(index).data[z + (x<<4)] = type;
        }
    }
}

void WorldGen :: generateChunkData(int x, int z, int chunkSize, ChunkData* chunkData){
    //TODO: actual world gen

    chunkData->pos=glm :: ivec2(x,z);

    chunkData->data.clear();
    chunkData->data.reserve(5);

    chunkData->data.push_back((unsigned char)0); fillLayer(0, chunkSize, chunkData, Blocks :: STONE);
    chunkData->data.push_back((unsigned char)1); fillLayer(1, chunkSize, chunkData, Blocks :: DIRT);
    chunkData->data.push_back((unsigned char)2); fillLayer(2, chunkSize, chunkData, Blocks :: GRASS);
    chunkData->data.push_back((unsigned char)3);
    chunkData->data.at(3).data[0 + (0<<4)] = Blocks :: SHORT_GRASS;
    chunkData->data.at(3).data[1 + (0<<4)] = Blocks :: TALL_GRASS_BOTTOM;
    chunkData->data.at(3).data[0 + (1<<4)] = Blocks :: ROSE;
    chunkData->data.at(3).data[1 + (1<<4)] = Blocks :: TULIP_WHITE;
    chunkData->data.at(3).data[0 + (2<<4)] = Blocks :: TULIP_ORANGE;
    chunkData->data.at(3).data[1 + (2<<4)] = Blocks :: TULIP_PINK;
    chunkData->data.at(3).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->data.push_back((unsigned char)4);
    chunkData->data.at(4).data[1 + (0<<4)] = Blocks :: TALL_GRASS_TOP;
    chunkData->data.at(4).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->data.push_back((unsigned char)5);
    chunkData->data.at(5).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->data.at(5).data[1 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[2 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[3 + (0<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(5).data[0 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[1 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[2 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[3 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[4 + (1<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(5).data[0 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[1 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[3 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[4 + (2<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(5).data[0 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[1 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[2 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[3 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[4 + (3<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(5).data[1 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[2 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(5).data[3 + (4<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.push_back((unsigned char)6);
    chunkData->data.at(6).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->data.at(6).data[0 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[1 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[2 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[3 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[4 + (0<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(6).data[0 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[1 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[2 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[3 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[4 + (1<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(6).data[0 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[1 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[3 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[4 + (2<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(6).data[0 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[1 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[2 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[3 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[4 + (3<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(6).data[0 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[1 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[2 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[3 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(6).data[4 + (4<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.push_back((unsigned char)7);
    chunkData->data.at(7).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->data.at(7).data[1 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(7).data[2 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(7).data[3 + (1<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(7).data[1 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(7).data[3 + (2<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(7).data[1 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(7).data[2 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(7).data[3 + (3<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.push_back((unsigned char)8);
    chunkData->data.at(8).data[2 + (1<<4)] = Blocks :: LEAVES_OAK;

    chunkData->data.at(8).data[1 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(8).data[2 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->data.at(8).data[3 + (2<<4)] = Blocks :: LEAVES_OAK;
    
    chunkData->data.at(8).data[2 + (3<<4)] = Blocks :: LEAVES_OAK;

}