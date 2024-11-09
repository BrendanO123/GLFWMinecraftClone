#pragma once

#include "Chunk.h"
#include "ChunkData.h"
#include <vector>

namespace WorldGen{
    void generateChunkData(int chunkX, int chunkZ, int chunkSize, ChunkData* chunkData);
}