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

        ~Structure(){
            delete [] contents;
            forcedBlocks.clear();
        }
        /**
         * @brief Specifies if the structure should try to water log blocks when placing water.
         */
        const bool shouldWaterLog;
        const int sizeX, sizeY, sizeZ, id;

        /**
         * @brief A bool array that specififes where to carve away terrain with air and where to leave it be, unimplemented.
         */
        vector<bool> forcedBlocks;
        /**
         * @brief The blocks that compose the structure.
         */
        GLubyte* contents;

        /**
         * @param sX The size of the structure along the x axis.
         * @param sY The size of the structure along the y axis.
         * @param sZ The size of the structure along the z axis.
         * @param blocks The flattened array of block types that define the structure.
         * @param isForced The flattened bool array that specifies where the structure should carve out existing blocks.
         * @param waterLogged Specifies if the structure should attempt to waterlog blocks when placing water, unimplemented.
         */
        Structure(
            GLubyte sX, GLubyte sY, GLubyte sZ, int ID, 
            char* blocks,
            char* isForced,  
            bool waterLoged = false
        ) : 
            shouldWaterLog(waterLoged),     sizeX(sX), sizeY(sY), sizeZ(sZ),    id(ID)
            {
                int arraySize = sX * sY * sZ;
                forcedBlocks=vector<bool>();
                forcedBlocks.reserve(arraySize);
                for(int i=0; i<arraySize; i++){
                    forcedBlocks.push_back(isForced[i>>3] >> (i&7));
                }
                //for(int i=0; i<arraySize; i++){forcedBlocks.push_back(isForced+i);}

                contents = new GLubyte[arraySize];
                copy((GLubyte*)blocks, (GLubyte*)(blocks+arraySize), contents);
            };

        /**
         * @param sX The size of the structure along the x axis.
         * @param sY The size of the structure along the y axis.
         * @param sZ The size of the structure along the z axis.
         * @param blocks The flattened array of block types that define the structure.
         * @param isForced The flattened bool array that specifies where the structure should carve out existing blocks.
         * @param waterLogged Specifies if the structure should attempt to waterlog blocks when placing water, unimplemented.
         */
        Structure(
            GLubyte sX, GLubyte sY, GLubyte sZ, int ID,
            const GLubyte blocks[],
            const vector<bool> isForced,  
            bool waterLoged = false
        ) : 
            shouldWaterLog(waterLoged),     sizeX(sX), sizeY(sY), sizeZ(sZ),    id(ID),
            forcedBlocks(isForced){
                contents = new GLubyte[sX*sY*sZ];
                copy(blocks, blocks + sX*sY*sZ, contents);
            };

        /**
         * @brief Places a const structure object in a chunk at a position. Used for structures that need to create non-cuboid caves.
         * @param target The chunk (chunkData) to place the structure in.
         * @param pX The position in chunk space along the x axis.
         * @param pY The position in chunk space along the y axis.
         * @param pZ The position in chunk space along the z axis.
         * @return A boolean storing wether the structure extrudes past the targeted chunks edges. Used to create structure list for chunk. 
         */
        bool placeSelf(ChunkData &target, GLbyte pX, GLbyte pY, GLbyte pZ) const;

        bool operator==(const Structure& other) const{
            if(id!=other.id){return false;}
            if(sizeX != other.sizeX || sizeY != other.sizeY || sizeZ != other.sizeZ){return false;}
            int arraySize = sizeX * sizeY * sizeZ;
            for(int i=0; i<arraySize; i++){
                if(contents[i] != other.contents[i] || forcedBlocks.at(i) != other.forcedBlocks.at(i)){return false;}
            }
            return true;
        }
        bool operator!=(const Structure& other) const{return !this->operator==(other);}
};