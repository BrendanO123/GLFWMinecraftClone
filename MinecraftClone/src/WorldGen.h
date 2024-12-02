#pragma once

#include "Chunk.h"
#include "ChunkData.h"
#include <vector>

namespace WorldGen{

    /**
     * @brief Fills the layer at an index in a chunkData with one block type.
     * @param index The index of the layer to fill in.
     * @param chunkSize An early framework for a LOD system, please leave as 16 for now.
     * @param chunkData A pointer to the chunkData object to modify.
     * @param type The block type to fill the layer with.
     */
    void fillLayer(int index, int chunkSize, ChunkData* chunkData, GLubyte type);

    /**
     * @brief Calls the placement functions and adds to the strcutre list of the chunk if the structure spans a chunk edge.
     * @param chunkData The target chunk to work on.
     * @param id The index in the const structure arr found in the structures.h file where the actual structure can be found.
     * @param x The position along the x axis of the center of the structure in chunk space.
     * @param y The position along the y axis of the botom of the structure in chunk space.
     * @param z The position along the z axis of the center of the structure in chunk space. 
     */
    inline void placeStruct(ChunkData* chunkData, GLubyte id, GLubyte x, GLubyte y, GLubyte z);

    void resolveStructures(ChunkData* target, 
        ChunkData* NW, ChunkData* N, ChunkData* NE, 
        ChunkData* W,                ChunkData* E, 
        ChunkData* SW, ChunkData* S, ChunkData* SE);


    /**
     * @brief The main worldGen call which fills in a chunk given its world position (the actual cordinates are divided by chunk size).
     * @param chunkX The x cordinate of the chunk divided by the standard chunk size (16).
     * @param chunkZ The z cordinate of the chunk divided by the standard chunk size (16).
     * @param chunkData The target chunk for the generation function.
     */
    void getChunkBasics(int chunkX, int chunkZ, int chunkSize, ChunkData* chunkData);
}