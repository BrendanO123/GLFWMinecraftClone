#pragma once

#include <glm/glm.hpp>
#include "Blocks.h"


struct raycastReturnStruct{
    glm :: ivec3 pos;
    unsigned char blockType;
    glm :: i8vec3 normal;

    raycastReturnStruct(){}
    raycastReturnStruct(glm :: ivec3 location, unsigned char BlockType, glm :: i8vec3 normalDirection) :
        pos(location), blockType(BlockType), normal(normalDirection){}
};

class Raycaster{
    private:
        unsigned char (*checkVoxel)(int, int, int);
        int reachDist;

    public:
        Raycaster(int maxReach = 12, unsigned char (*voxelHitCheck)(int, int, int) = nullptr);
        Raycaster(unsigned char (*voxelHitCheck)(int, int, int));
        bool setLookupCallback(unsigned char (*voxelHitCheck)(int, int, int));
        bool setMaxReach(int maxReach);

        /**
         * @brief The main function that raycasts a given look direction against a map of voxels to check for the first hit block.
         * @param originInt The integer component of the camera position, which must be less than or equal to the camera position.
         * @param originFloat The floating point component of the camera position. Must be in [0 1).
         * @param direction The direction the camera is facing that must be a normalized vector3.
         * @param voxelHitCheck The lookup function for the voxel at a given integer position that returns te block type at the position.
         */
        raycastReturnStruct unitVoxelRaycast(glm :: ivec3 originInt, glm :: vec3 originFloat, glm :: vec3 direction, int maxReach = -1, unsigned char (*voxelHitCheck)(int, int, int) = nullptr);
};