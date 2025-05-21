#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Blocks.h"
#include "ChunkData.h"

using namespace std;

/**
 * @brief The class describing sturcture assets.
 */
class Structure{

    public:
        /**
         * @brief Specifies if the structure should try to water log blocks when placing water.
         */
        const bool shouldWaterLog;
        const int sizeX, sizeY, sizeZ;
        /**
         * @brief A bool array that specififes where to carve away terrain with air and where to leave it be, unimplemented.
         */
        const vector<bool> forcedBlocks;
        /**
         * @brief The blocks that compose the structure.
         */
        const GLubyte *contents;

        /**
         * @param sX The size of the structure along the x axis.
         * @param sY The size of the structure along the y axis.
         * @param sZ The size of the structure along the z axis.
         * @param blocks The flattened array of block types that define the structure.
         * @param isForced The flattened bool array that specifies where the structure should carve out existing blocks.
         * @param waterLogged Specifies if the structure should attempt to waterlog blocks when placing water, unimplemented.
         */
        Structure(
            GLubyte sX, GLubyte sY, GLubyte sZ,
            GLubyte blocks[],
            vector<bool> isForced,  
            bool waterLoged = false
        ) : 
            shouldWaterLog(waterLoged),     sizeX(sX), sizeY(sY), sizeZ(sZ), 
            forcedBlocks(isForced),     contents(blocks){};

        /**
         * @param sX The size of the structure along the x axis.
         * @param sY The size of the structure along the y axis.
         * @param sZ The size of the structure along the z axis.
         * @param blocks The flattened array of block types that define the structure.
         * @param isForced The flattened bool array that specifies where the structure should carve out existing blocks.
         * @param waterLogged Specifies if the structure should attempt to waterlog blocks when placing water, unimplemented.
         */
        Structure(
            GLubyte sX, GLubyte sY, GLubyte sZ,
            const GLubyte blocks[],
            const vector<bool> isForced,  
            bool waterLoged = false
        ) : 
            shouldWaterLog(waterLoged),     sizeX(sX), sizeY(sY), sizeZ(sZ), 
            forcedBlocks(isForced),     contents(blocks){};

        /**
         * @brief Places a const structure object in a chunk at a position. Used for structures that need to create non-cuboid caves.
         * @param target The chunk (chunkData) to place the structure in.
         * @param pX The position in chunk space along the x axis.
         * @param pY The position in chunk space along the y axis.
         * @param pZ The position in chunk space along the z axis.
         * @return A boolean storing wether the structure extrudes past the targeted chunks edges. Used to create structure list for chunk. 
         */
        bool placeSelf(ChunkData &target, GLbyte pX, GLbyte pY, GLbyte pZ) const;
};