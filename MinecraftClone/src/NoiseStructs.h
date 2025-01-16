#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cstdlib>

#include "ChunkData.h"

using namespace std;

namespace noise{
    struct NoiseReturnStruct{
        glm :: ivec2 pos;
        GLubyte surfaceType[256];
        GLubyte surfaceDepth[256];
        float temperature[256];
        float annualRainfall[256];
        GLubyte TerrainHeight[256];
        GLubyte biome[256];
         
        GLubyte foliage[256];
        StructureList Structures = StructureList();

        GLubyte minHeight, maxHeight;

        NoiseReturnStruct(){}
    };

    enum noiseTypes : unsigned char{
        PERLIN = 0,
        VALUE_CUBIC = 1,
        WHITE = 2
    };
    enum fractalTypes : unsigned char{
        NONE = 0,
        FBM = 1
    };

    struct NoiseMapSettings{
        int seed = 1337;
        bool includePartials = false;
        unsigned char noiseType = noiseTypes :: PERLIN;
        unsigned char fractalType = fractalTypes :: NONE;
        
        float frequency = 1.0f/100;
        float gain = 0.5f;
        float lacunarity = 2.0f;

        int octaves = 3;
        float fractalBounding = 1/1.75f;

        int xOffset = 1337;
        int yOffset = 19;

        NoiseMapSettings(){}
        NoiseMapSettings(int Seed, bool partials, unsigned char type, unsigned char fractalMode, float f, float g, float l, int o, float bounding)
         : seed(Seed), includePartials(partials), noiseType(type), fractalType(fractalMode), 
         frequency(f), gain(g), lacunarity(l), octaves(o), fractalBounding(bounding){}
    };

    const unsigned char mapCount = 7;
    enum noiseSettings : unsigned char{
        TEMP_NOISE = 0,
        RAIN_NOISE = 1,
        EROSION_MAP = 2,
        CONTINENTAL_MAP = 3,
        STRUCT_MAP = 4,
        GRASS_MAP = 5,
        TREE_MAP = 6
    };
    struct NoiseTotalSettings{
        int terrainSeed = 1337;
        float terrainFrequency = 0.01f;
        NoiseMapSettings settings[mapCount] = 
        {NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings()};

        NoiseTotalSettings(int seed){
            for(int i = 0; i < mapCount; i++){
                settings[i].seed = rand(); 
                settings[i].xOffset = (rand() & 1023) + 1;
                settings[i].yOffset = (rand() & 1023) + 1;
            }
            terrainSeed = rand(); 
        }
    };

}