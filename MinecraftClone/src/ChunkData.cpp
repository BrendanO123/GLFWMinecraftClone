#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "ChunkData.h"
#include "Structures.h"

using namespace std;

StructureList :: ~StructureList(){
    StructNode* iterate = first;
    StructNode* next;
    while(iterate != nullptr){
        next = iterate->next;
        delete iterate;
        iterate = next;
    }
}

void ChunkData :: place(ChunkData* target, glm :: i8vec2 offset){
    StructNode* iterate = Structs.first;
    //for(int i = 0; i<Structs.count; i++){
    while(iterate != nullptr){
        Structure iterateActual = Structures :: Structs[iterate->id];

        if((offset.x + iterate->pos.x + (iterateActual.sizeX >> 1) + (iterateActual.sizeX & 1) - 1) >= 0 && (offset.x + iterate->pos.x - (iterateActual.sizeX>>1)) <= 15){
            if((offset.y +iterate->pos.z + (iterateActual.sizeZ >> 1) + (iterateActual.sizeZ & 1) - 1) >= 0 && (offset.y + iterate->pos.z - (iterateActual.sizeZ>>1)) <= 15){
                Structures :: Structs[iterate->id].placeSelf(*target, iterate->pos.x + offset.x, iterate->pos.y, iterate->pos.z + offset.y);
            }
        }
        iterate = iterate->next;
    }
}

GLubyte ChunkData :: findBlock(GLubyte index, GLubyte height){
    if(data.size()!=0){
        Layer* layer = findLayer(height, 0, data.size()-1);
        if(layer!=nullptr){return layer->data[index];}
    }
    return Blocks :: AIR;
}

//layer fetch for structure placement
Layer* ChunkData :: getLayer(GLubyte height){
    if(data.size()!=0){
        return findLayer(height, 0, data.size()-1);
    }
    return nullptr;
}

GLubyte ChunkData :: safeLayerFetch(GLubyte height){

    if(data.size() == 0){data.emplace_back(height); return 0;}
    if(data.back().y < height){data.emplace_back(height); return data.size()-1;}
    if(data.front().y > height){data.emplace(data.begin(), height); return 0;}

    GLubyte y;
    int low = 0, high = data.size()-1;
    while(high>low){
        int mid = (low+high)>>1;

        y = data[mid].y;
        if(y==height){return mid;}
        if(y<height){low=mid+1; continue;}
        if(y>height){high=mid-1; continue;}
    }

    y = data[high].y;
    if(y==height){return high;}
    if(y<height){data.emplace(data.begin()+high+1, height); return high+1;}
    data.emplace(data.begin()+high, height); return high;
}

GLubyte ChunkData :: insert(GLubyte height, GLubyte lowerBound){
    GLubyte index = findIndex(height, lowerBound, data.size()-1);
    data.emplace(data.begin()+index, height);
    return index;
}

//layer/block fetch helper (binary search) function
Layer* ChunkData :: findLayer(GLubyte target, int low, int high){
    while(high>=low){
        int mid = (low+high)>>1;

        GLubyte y = data[mid].y;
        if(y==target){return &data[mid];}
        if(y<target){low=mid+1; continue;}
        if(y>target){high=mid-1; continue;}
    }
    
    return nullptr;
}

//new layer index helper (binary search) function
GLubyte ChunkData :: findIndex(GLubyte target, int low, int high){
    GLubyte y;
    while(high>low){
        int mid = (low+high)>>1;

        y = data[mid].y;
        if(y<target){low=mid+1; continue;}
        if(y>target){high=mid-1; continue;}
    }
    y = data[high].y;
    if(y<target){return high+1;}
    return high;
}