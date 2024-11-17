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
     * @brief The main worldGen call which fills in a chunk given its world position (the actual cordinates are divided by chunk size).
     * @param chunkX The x cordinate of the chunk divided by the standard chunk size (16).
     * @param chunkZ The z cordinate of the chunk divided by the standard chunk size (16).
     * @param chunkData The target chunk for the generation function.
     */
    void generateChunkData(int chunkX, int chunkZ, int chunkSize, ChunkData* chunkData);
}