#pragma once

#include <vector>
#include "Layer.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct ChunkData{

    //data
    vector<Layer> data;
    glm :: ivec2 pos;

    //constructors
    ChunkData() : data(vector<Layer>()), pos(glm :: ivec2()){}
    ChunkData(vector<Layer> Data, glm :: ivec2 loc) : data(Data), pos(loc){}

    //block fetch for chunk edge face culling
    GLubyte findBlock(GLubyte index, GLubyte height){
        if(data.size()!=0){
            Layer* layer = findLayer(height, 0, data.size()-1);
            if(layer!=nullptr){return layer->data[index];}
        }
        return -1;
    }

    //layer fetch for structure placement
    Layer* getLayer(GLubyte height){
        if(data.size()!=0){
            return findLayer(height, 0, data.size()-1);
        }
        return nullptr;
    }

    /**
     * @short Returns the layer with the given y value, places one in data if none exists. 
     * @param height The y value of the deisred layer.
     * @note This function has many checks to keep data sorted and return a valid layer with the given y value even in edge cases. If some of the edge case checks can be skipped, this function might not be preffered.
     * @returns The index of the desired layer.
     */
    GLubyte safeLayerFetch(GLubyte height){

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

    /**
     * @short Places a new layer while keeping data sorted, should only be used when the layer doesn't already exist and is inbetween existing layers.
     * @param height The y value where the new layer is placed.
     * @param lowerBound The minimum index to consider as a placement option. 
     * @attention Breaks if layer already exists, data is empty, or the layer should be placed at index 0.
     * @returns The index of the new layer.
     */
    GLubyte insert(GLubyte height, GLubyte lowerBound = 0){
        GLubyte index = findIndex(height, lowerBound, data.size()-1);
        data.emplace(data.begin()+index, height);
        return index;
    }

    private:

        //layer/block fetch helper (binary search) function
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

        //new layer index helper (binary search) function
        GLubyte findIndex(GLubyte target, int low, int high){
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

};