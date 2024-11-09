#pragma once

#include <vector>
#include "Layer.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct ChunkData{
    vector<Layer> data;
    glm :: ivec2 pos;
    ChunkData() : data(vector<Layer>()), pos(glm :: ivec2()){}
    ChunkData(vector<Layer> Data, glm :: ivec2 loc) : data(Data), pos(loc){}

    GLubyte findBlock(GLubyte index, GLubyte height){
        if(data.size()!=0){
            Layer* layer = findLayer(height, 0, data.size()-1);
            if(layer!=nullptr){return layer->data[index];}
        }
        return -1;
    }
    private:
        Layer* findLayer(GLubyte target, int low, int high){
            while(high>=low){
                int mid = (low+high)>>1;

                GLubyte y = data[mid].y;
                if(y==target){return &data[mid];}
                if(y<target){low=mid+1; continue;}
                if(y>target){high=mid-1; continue;}
            }
            
            return nullptr;
        }
};