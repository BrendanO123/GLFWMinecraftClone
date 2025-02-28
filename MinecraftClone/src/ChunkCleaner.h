#pragma once

#include <filesystem>
#include <string>

#include "FileManager.h"
#include "ChunkData.h"

#include "WorldGen.h"
#include "Fractal.h"
#include "WorldGenSettings.h"

constexpr const bool adjustStructs = true;
constexpr const bool replaceAllStructs = true && adjustStructs;
constexpr const bool checkStructsEqual = false && adjustStructs && !replaceAllStructs;
constexpr const bool checkStructsDuplicate = false && adjustStructs && !replaceAllStructs;
constexpr const bool deleteNaturalChunks = false;

namespace Cleaner{
    void cleanChunk(string name);
}