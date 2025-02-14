#include "UnitVoxelRaycaster.h"

#include <iostream>
#include <limits>

Raycaster :: Raycaster(int maxReach, unsigned char (*voxelHitCheck)(int, int, int)){checkVoxel = voxelHitCheck; reachDist = maxReach;}
Raycaster :: Raycaster(unsigned char (*voxelHitCheck)(int, int, int)){checkVoxel = voxelHitCheck; reachDist = 12;}
bool Raycaster :: setLookupCallback(unsigned char (*voxelHitCheck)(int, int, int)){
    if(voxelHitCheck == nullptr){return false;}
    else{checkVoxel = voxelHitCheck; return true;}
}
bool Raycaster :: setMaxReach(int maxReach){
    if(maxReach <= 0){return false;}
    else{reachDist = maxReach; return true;}
}

raycastReturnStruct Raycaster :: unitVoxelRaycast(glm :: ivec3 originInt, glm :: vec3 originFloat, glm :: vec3 direction, int maxReach, unsigned char (*voxelHitCheck)(int, int, int)){
    /*#ifndef NDEBUG
        if(direction.length() == 0){
            printf("CANNOT RAYCAST ALONG VECTOR OF LENGTH ZERO\n", stderr);
            exit(EXIT_FAILURE);
        }
        else if(direction.length() > 1.0001f || direction.length() < 0.9999f){
            printf("RAYCAST LOOK VECTOR SHOULD BE NORMALIZED\n", stdout);
        }
        if(originFloat.x > 1.0f || originFloat.x < 0.f || originFloat.y > 1.0f || originFloat.y < 0.f || originFloat.z > 1.0f || originFloat.z < 0.f){
            printf("FLOATING POINT COMPONENT OF CAMERA POSITION SHOULD BE IN [0, 1) FOR RAYCAST\n", stderr);
        }
        if(voxelHitCheck == nullptr && checkVoxel == nullptr){
            printf("RAYCAST FUNCTION NEEDS A VOXEL LOOKUP FUNCTION\n", stderr);
            exit(EXIT_FAILURE);
        }
    #endif*/
    if(maxReach > 0){reachDist = maxReach;}
    if(voxelHitCheck != nullptr){checkVoxel = voxelHitCheck;}

    
    glm :: vec3 timeInc1 = glm :: vec3(
        (direction.x != 0 ? 1/direction.x : std::numeric_limits<float>::infinity()), 
        (direction.y != 0 ? 1/direction.y : std::numeric_limits<float>::infinity()), 
        (direction.z != 0 ? 1/direction.z : std::numeric_limits<float>::infinity())
    );
    glm :: i8vec3 step = glm :: i8vec3(
        (direction.x > 0 ? 1 : (direction.x < 0 ? -1 : 0)), 
        (direction.y > 0 ? 1 : (direction.y < 0 ? -1 : 0)), 
        (direction.z > 0 ? 1 : (direction.z < 0 ? -1 : 0))
    );
    glm :: vec3 dt = glm :: vec3(
        timeInc1.x * (step.x == 1 ? 1-originFloat.x : (step.x == 0 ? std::numeric_limits<float>::infinity() : originFloat.x)), 
        timeInc1.y * (step.y == 1 ? 1-originFloat.y : (step.y == 0 ? std::numeric_limits<float>::infinity() : originFloat.y)), 
        timeInc1.z * (step.z == 1 ? 1-originFloat.z : (step.z == 0 ? std::numeric_limits<float>::infinity() : originFloat.z))
    );
    glm :: ivec3 lookPositionInt = originInt;

    unsigned char blockType;

    while(true){
        if(dt.x <= dt.y){
            if(dt.x <= dt.z){
                lookPositionInt.x+=step.x;
                dt.y -= dt.x; dt.z -= dt.x;
                dt.x = timeInc1.x;

                blockType = checkVoxel(lookPositionInt.x, lookPositionInt.y, lookPositionInt.z);
                if(blockType){
                    return raycastReturnStruct(lookPositionInt, blockType, glm :: i8vec3(-step.x, 0, 0));
                }
                if(abs(lookPositionInt.x-originInt.x) >= reachDist){
                    return raycastReturnStruct(lookPositionInt, Blocks :: AIR, glm :: i8vec3(0, 0, 0));
                }
            }
            else{
                lookPositionInt.z+=step.z;
                dt.x -= dt.z; dt.y -= dt.z;
                dt.z = timeInc1.z;

                blockType = checkVoxel(lookPositionInt.x, lookPositionInt.y, lookPositionInt.z);
                if(blockType){
                    return raycastReturnStruct(lookPositionInt, blockType, glm :: i8vec3(0, 0, -step.z));
                }
                if(abs(lookPositionInt.z-originInt.z) >= reachDist){
                    return raycastReturnStruct(lookPositionInt, Blocks :: AIR, glm :: i8vec3(0, 0, 0));
                }
            }
        }
        else{
            if(dt.y <= dt.z){
                lookPositionInt.y+=step.y;
                dt.x -= dt.y; dt.z -= dt.y;
                dt.y = timeInc1.y;

                blockType = checkVoxel(lookPositionInt.x, lookPositionInt.y, lookPositionInt.z);
                if(blockType){
                    return raycastReturnStruct(lookPositionInt, blockType, glm :: i8vec3(0, -step.y, 0));
                }
                if(abs(lookPositionInt.y-originInt.y) >= reachDist){
                    return raycastReturnStruct(lookPositionInt, Blocks :: AIR, glm :: i8vec3(0, 0, 0));
                }
            }
            else{
                lookPositionInt.z+=step.z;
                dt.x -= dt.z; dt.y -= dt.z;
                dt.z = timeInc1.z;

                blockType = checkVoxel(lookPositionInt.x, lookPositionInt.y, lookPositionInt.z);
                if(blockType){
                    return raycastReturnStruct(lookPositionInt, blockType, glm :: i8vec3(0, 0, -step.z));
                }
                if(abs(lookPositionInt.z-originInt.z) >= reachDist){
                    return raycastReturnStruct(lookPositionInt, Blocks :: AIR, glm :: i8vec3(0, 0, 0));
                }
            }
        }
    }

}