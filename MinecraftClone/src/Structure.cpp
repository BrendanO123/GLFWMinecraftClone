

#include "Structure.h"
#include "Layer.h"

using namespace std;

void NormStructure :: placeSelf(ChunkData &target, GLubyte pX, GLubyte pY, GLubyte pZ) const{
    unsigned char i = target.safeLayerFetch(pY);
    Layer* layer = &target.data.at(i);

    bool forced = (flags & Structures :: FORCED);
    //bool shouldWaterLog = (flags & Structures :: SHOULD_WATER_LOG);

    GLubyte id;
    int yChunk, xChunk, zChunk;
    for(char y = 0; y < sizeY; y++){

        yChunk = int(y)+pY;

        for(char x = 0; x < sizeX; x++){

            xChunk = int(pX)-(sizeX>>1)+x;
            if(xChunk > 15){break;}
            if(xChunk < 0){continue;}

            for(char z = 0; z < sizeZ; z++){

                zChunk = int(pZ)-(sizeZ>>1)+z;
                if(zChunk > 15){break;}
                if(zChunk < 0){continue;}

                id = contents[z+(int(x)*sizeZ)+(int(y)*sizeZ*sizeX)];
                if(id == Blocks :: AIR && !forced){continue;}

                layer->data[zChunk+(int(xChunk)<<4)]=id;
            }
        }

        if(y==sizeY-1){break;} //at the end of structure and will end up breaking if continue is called anyways
        if(yChunk==255){break;} // at world height so stop

        //at the highest point in the data so next y value will be at a new layer on top of the existing chunk
        if(i==target.data.size()-1){target.data.emplace_back(yChunk+1); layer = &target.data.at(++i); continue;} //place layer at i+1
        if(target.data.at(i+1).y == yChunk+1){layer = &target.data.at(++i);} //next layer in chunk is already what we want, get layer i+1

        //next y value is valid, i+1 is not out of bounds on data, layer will be after index i bc sorted, next layer is not next y
        //therefore, desired layer should be placed at i+1

        //data:
        //next y-1, a, b, c, d, e... where a: is an int, is greater than next y-1, is not next y, therefore must be atleast next y+1
        else{target.data.emplace(target.data.begin() + (++i), yChunk+1); layer = &target.data.at(i); continue;} //place layer at i+1
    }
};

void PartialFillStructure :: placeSelf(ChunkData &target, GLubyte pX, GLubyte pY, GLubyte pZ) const{

};