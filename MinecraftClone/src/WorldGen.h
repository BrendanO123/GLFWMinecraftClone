#pragma once

#include "Chunk.h"
#include <vector>

namespace WorldGen{
    void generateChunkData(int chunkX, int chunkZ, int chunkSize, std :: vector<Layer>* chunkData);
}