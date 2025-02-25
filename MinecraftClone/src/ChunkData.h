#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Layer.h"
#include "Blocks.h"


struct StructNode
{
    GLubyte id;
    glm :: u8vec3 pos;
    StructNode* next;

    StructNode(GLubyte ID, GLubyte x, GLubyte y, GLubyte z, StructNode* pointer = nullptr) : 
        id(ID), pos(glm :: u8vec3(x, y, z)), next(pointer){};
};

struct StructureList{
    int count;
    StructNode* first;
    StructNode* last;

    StructureList(int newCount = 0, StructNode* next = nullptr) : count(newCount), first(next), last(next){}
    ~StructureList();
};

struct ChunkData{

    //data
    vector<Layer> data;
    int xPos, zPos;
    //glm :: ivec2 pos;
    StructureList Structs = StructureList();
    bool hasBuilds = false;
    bool fileStored = false;

    //constructors
    ChunkData() : data(vector<Layer>()), /**/xPos(0), zPos(0)/**//*pos(glm :: ivec2())*/{}
    ChunkData(vector<Layer> Data, glm :: ivec2 loc) : data(Data), /**/xPos(loc.x), zPos(loc.y)/*pos(loc)*/{}
    ~ChunkData(){}

    void place(ChunkData* other, glm :: i8vec2 offset);

    //block fetch for chunk edge face culling
    /**
     * @brief Returns the block type at a given position, returns air if it isn't stored.
     * @param index The index in the layer to find the block = z + x * 16.
     * @param height The y value of the layer to find the block in.
     */
    GLubyte findBlock(GLubyte index, GLubyte height);

    //layer fetch for structure placement
    /**
     * @brief returns a pointer to the layer at the given height, nullptr if it doesn't exist.
     * @param height The y value of the layer that should be returned.
     */
    Layer* getLayer(GLubyte height);

    /**
     * @short Returns the layer with the given y value, places one in data if none exists. 
     * @param height The y value of the deisred layer.
     * @note This function has many checks to keep data sorted and return a valid layer with the given y value even in edge cases. If some of the edge case checks can be skipped, this function might not be preffered.
     * @returns The index of the desired layer.
     */
    GLubyte safeLayerFetch(GLubyte height);

    /**
     * @short Places a new layer while keeping data sorted, should only be used when the layer doesn't already exist and is inbetween existing layers.
     * @param height The y value where the new layer is placed.
     * @param lowerBound The minimum index to consider as a placement option. 
     * @attention Breaks if layer already exists, data is empty, or the layer should be placed at index 0.
     * @returns The index of the new layer.
     */
    GLubyte insert(GLubyte height, GLubyte lowerBound = 0);

    private:

        //layer/block fetch helper (binary search) function
        /**
         * @brief helper function that uses a binary search with resepect to height of the layers to find a layer
         */
        Layer* findLayer(GLubyte target, int low, int high);

        //new layer index helper (binary search) function
        /**
         * @brief helper function that returns the index to insert a new layer of a given y value
         */
        GLubyte findIndex(GLubyte target, int low, int high);

};