#include "WorldGen.h"

#include "Blocks.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

using namespace std;


void fillLayer(int index, int chunkSize, vector<Layer>* chunkData, GLubyte type){
    for(int x=0; x<16; x++){
        for(int z=0; z<16; z++){
            chunkData->at(index).data[z + (x<<4)] = type;
        }
    }
}

void WorldGen :: generateChunkData(int x, int z, int chunkSize, vector<Layer>* chunkData){
    //TODO: actual world gen

    chunkData->clear();
    chunkData->reserve(5);

    chunkData->push_back((unsigned char)0); fillLayer(0, chunkSize, chunkData, Blocks :: STONE);
    chunkData->push_back((unsigned char)1); fillLayer(1, chunkSize, chunkData, Blocks :: DIRT);
    chunkData->push_back((unsigned char)2); fillLayer(2, chunkSize, chunkData, Blocks :: GRASS);
    chunkData->push_back((unsigned char)3);
    chunkData->at(3).data[0 + (0<<4)] = Blocks :: SHORT_GRASS;
    chunkData->at(3).data[1 + (0<<4)] = Blocks :: TALL_GRASS_BOTTOM;
    chunkData->at(3).data[0 + (1<<4)] = Blocks :: ROSE;
    chunkData->at(3).data[1 + (1<<4)] = Blocks :: TULIP_WHITE;
    chunkData->at(3).data[0 + (2<<4)] = Blocks :: TULIP_ORANGE;
    chunkData->at(3).data[1 + (2<<4)] = Blocks :: TULIP_PINK;
    chunkData->at(3).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->push_back((unsigned char)4);
    chunkData->at(4).data[1 + (0<<4)] = Blocks :: TALL_GRASS_TOP;
    chunkData->at(4).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->push_back((unsigned char)5);
    chunkData->at(5).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->at(5).data[1 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[2 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[3 + (0<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(5).data[0 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[1 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[2 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[3 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[4 + (1<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(5).data[0 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[1 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[3 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[4 + (2<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(5).data[0 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[1 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[2 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[3 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[4 + (3<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(5).data[1 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[2 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(5).data[3 + (4<<4)] = Blocks :: LEAVES_OAK;

    chunkData->push_back((unsigned char)6);
    chunkData->at(6).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->at(6).data[0 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[1 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[2 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[3 + (0<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[4 + (0<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(6).data[0 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[1 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[2 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[3 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[4 + (1<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(6).data[0 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[1 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[3 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[4 + (2<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(6).data[0 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[1 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[2 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[3 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[4 + (3<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(6).data[0 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[1 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[2 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[3 + (4<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(6).data[4 + (4<<4)] = Blocks :: LEAVES_OAK;

    chunkData->push_back((unsigned char)7);
    chunkData->at(7).data[2 + (2<<4)] = Blocks :: LOG_OAK;

    chunkData->at(7).data[1 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(7).data[2 + (1<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(7).data[3 + (1<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(7).data[1 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(7).data[3 + (2<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(7).data[1 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(7).data[2 + (3<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(7).data[3 + (3<<4)] = Blocks :: LEAVES_OAK;

    chunkData->push_back((unsigned char)8);
    chunkData->at(8).data[2 + (1<<4)] = Blocks :: LEAVES_OAK;

    chunkData->at(8).data[1 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(8).data[2 + (2<<4)] = Blocks :: LEAVES_OAK;
    chunkData->at(8).data[3 + (2<<4)] = Blocks :: LEAVES_OAK;
    
    chunkData->at(8).data[2 + (3<<4)] = Blocks :: LEAVES_OAK;

}