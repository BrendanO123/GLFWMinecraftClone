#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "UnitVoxelRaycasting.h"

unsigned char blockLookUpRight(int x, int y, int z){
    if(x > 6){return Blocks :: STONE;}
    return Blocks :: AIR;
}
unsigned char blockLookUpFar(int x, int y, int z){
    return Blocks :: AIR;
}
TEST_CASE("Testing Voxel Raycast") {
    Raycaster RaycasterRight = Raycaster(15, &blockLookUpRight);
    Raycaster RaycasterFar = Raycaster(15, &blockLookUpFar);

    raycastReturnStruct Right45Cast = RaycasterRight.unitVoxelRaycast(glm :: ivec3(0, 0, 0), glm :: vec3(0.f, 0.f, -0.1f), glm :: vec3(1.f/sqrt(2), 0.f, 1.f/sqrt(2)));
    raycastReturnStruct Right345Cast = RaycasterRight.unitVoxelRaycast(glm :: ivec3(0, 0, 0), glm :: vec3(0.f, 0.f, 0.f), glm :: vec3(4.f/5, 0.f, 3.f/5));
    raycastReturnStruct FarCast = RaycasterFar.unitVoxelRaycast(glm :: ivec3(0, 0, 0), glm :: vec3(0.5f, 0.5f, 0.5f), glm :: vec3(4.f/5, 0.f, 3.f/5));

    CHECK(Right45Cast.blockType == Blocks :: STONE);
    CHECK(Right45Cast.normal.x == -1);
    CHECK(Right45Cast.normal.y == 0);
    CHECK(Right45Cast.normal.z == 0);
    CHECK(Right45Cast.pos.x == 7);
    CHECK(Right45Cast.pos.y == 0);
    CHECK(Right45Cast.pos.z == 6);

    CHECK(Right345Cast.blockType == Blocks :: STONE);
    CHECK(Right45Cast.normal.x == -1);
    CHECK(Right45Cast.normal.y == 0);
    CHECK(Right45Cast.normal.z == 0);
    CHECK(Right345Cast.pos.x == 7);
    CHECK(Right345Cast.pos.y == 0);
    CHECK(Right345Cast.pos.z == 5);

    CHECK(FarCast.blockType == Blocks :: AIR);
    CHECK(FarCast.normal.x == 0);
    CHECK(FarCast.normal.y == 0);
    CHECK(FarCast.normal.z == 0);
}

/*TEST_CASE("Testing Voxel Raycast Debug Checks") {
    RaycasterRight(15, blockLookUpRight);
    raycastReturnStruct ZeroCast = RaycasterRight.unitVoxelRaycast(glm :: ivec3(0, 0, 0), glm :: vec3(0.f, 0.f, 0.f), glm :: vec3(0.f, 0.f, 0.f));
    CHECK(FarCast.normal == glm :: i8vec3(0, 0, 0));
}*/