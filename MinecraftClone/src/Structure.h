#pragma once

#include <glm/glm.hpp>
#include "Blocks.h"
#include "ChunkData.h"

using namespace std;

/**
 * @brief This is only meant to be used as a parent class not an independent object.
 */
class Structure{

    public:
        const int sizeX, sizeY, sizeZ;
        const GLubyte *contents;

        Structure(
            const GLubyte blocks[], 
            GLubyte sX, GLubyte sY, GLubyte sZ
        ) : sizeX(sX), sizeY(sY), sizeZ(sZ), contents(blocks){};

        void placeSelf(ChunkData &target, GLubyte pX, GLubyte pY, GLubyte pZ) const;
};

namespace Structures{
    enum STRUCTURE_FLAGS : unsigned char{
        FORCED = 1,
        SHOULD_WATER_LOG = 2
    };
};
class NormStructure : Structure{

    public:
        const GLubyte flags;

        NormStructure( 
            GLubyte sX, GLubyte sY, GLubyte sZ, 
            const GLubyte blocks[],
            bool forced = false, bool waterLoged = false
        ) :
            Structure(blocks, sX, sY, sZ),
            flags((GLubyte)((forced ? Structures :: FORCED : 0) + (waterLoged ? Structures :: SHOULD_WATER_LOG : 0))){};
        
        void placeSelf(ChunkData &target, GLubyte pX, GLubyte pY, GLubyte pZ) const;
};


class PartialFillStructure : Structure{

    public:
        const bool shouldWaterLog;
        const bool *forcedBlocks;

        PartialFillStructure(
            const GLubyte blocks[],
            bool isForced[], 
            GLubyte sX, GLubyte sY, GLubyte sZ, 
            bool waterLoged = false
        ) : 
            Structure(blocks,   sX, sY, sZ),
            shouldWaterLog(waterLoged), forcedBlocks(isForced){};

        void placeSelf(ChunkData &target, GLubyte pX, GLubyte pY, GLubyte pZ) const;
};