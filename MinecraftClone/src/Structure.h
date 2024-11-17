#pragma once

#include <glm/glm.hpp>
#include "Blocks.h"
#include "ChunkData.h"

using namespace std;

/**
 * @brief A parent class for structure asssets.
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

/**
 * @brief Namespace containing the header byte flags for the NormStructure class.
 */
namespace Structures{
    enum STRUCTURE_FLAGS : unsigned char{
        FORCED = 1,
        SHOULD_WATER_LOG = 2
    };
};
class NormStructure : Structure{

    public:

        /**
         * @brief The flag byte containing information such as if air in the structure should replace terrain.
         */
        const GLubyte flags;

        /**
         * @param sX The size of the structure along the x axis.
         * @param sY The size of the structure along the y axis.
         * @param sZ The size of the structure along the z axis.
         * @param blocks The flattened array of block types that define the structure.
         * @param forced Specifies if the structure should attempt to remove terrain in its bounding box.
         * @param waterLogged Specifies if the structure should attempt to waterlog blocks when placing water, unimplemented.
         */
        NormStructure( 
            GLubyte sX, GLubyte sY, GLubyte sZ, 
            const GLubyte blocks[],
            bool forced = false, bool waterLoged = false
        ) :
            Structure(blocks, sX, sY, sZ),
            flags((GLubyte)((forced ? Structures :: FORCED : 0) + (waterLoged ? Structures :: SHOULD_WATER_LOG : 0))){};
        
        /**
         * @brief Places a const structure object in a chunk at a position.
         * @param target The chunk (chunkData) to place the structure in.
         * @param pX The position in chunk space along the x axis.
         * @param pY The position in chunk space along the y axis.
         * @param pZ The position in chunk space along the z axis.
         */
        void placeSelf(ChunkData &target, GLubyte pX, GLubyte pY, GLubyte pZ) const;
};


class PartialFillStructure : Structure{

    public:
        /**
         * @brief Specifies if the structure should try to water log blocks when placing water.
         */
        const bool shouldWaterLog;
        /**
         * @brief A bool array that specififes where to carve away terrain with air and where to leave it be, unimplemented.
         */
        const bool *forcedBlocks;

        /**
         * @param sX The size of the structure along the x axis.
         * @param sY The size of the structure along the y axis.
         * @param sZ The size of the structure along the z axis.
         * @param blocks The flattened array of block types that define the structure.
         * @param isForced The flattened bool array that specifies where the structure should carve out existing blocks.
         * @param waterLogged Specifies if the structure should attempt to waterlog blocks when placing water, unimplemented.
         */
        PartialFillStructure(
            GLubyte sX, GLubyte sY, GLubyte sZ,
            const GLubyte blocks[],
            bool isForced[],  
            bool waterLoged = false
        ) : 
            Structure(blocks,   sX, sY, sZ),
            shouldWaterLog(waterLoged), forcedBlocks(isForced){};

        /**
         * @brief Places a const structure object in a chunk at a position. Used for structures that need to create non-cuboid caves.
         * @param target The chunk (chunkData) to place the structure in.
         * @param pX The position in chunk space along the x axis.
         * @param pY The position in chunk space along the y axis.
         * @param pZ The position in chunk space along the z axis.
         */
        void placeSelf(ChunkData &target, GLubyte pX, GLubyte pY, GLubyte pZ) const;
};