#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
        int seed;
        bool includePartials;
        unsigned char noiseType;
        unsigned char fractalType;
        
        float frequency;
        float gain;
        float lacunarity;

        int octaves;
        float fractalBounding;

        NoiseMapSettings(){
            NoiseMapSettings(1337, false, noiseTypes :: PERLIN, fractalTypes :: NONE, 1.0f/1000, 0.5f, 2.0f, 3, 1/1.75f);
        }
        NoiseMapSettings(int Seed, bool partials, unsigned char type, unsigned char fractalMode, float f, float g, float l, int o, float bounding)
         : seed(Seed), includePartials(partials), noiseType(type), fractalType(fractalMode), 
         frequency(f), gain(g), lacunarity(l), octaves(o), fractalBounding(bounding){}
    };

    const unsigned char mapCount = 6;
    enum noiseSettings : unsigned char{
        TEMP_NOISE = 0,
        RAIN_NOISE = 1,
        EROSION_MAP = 2,
        CONTINENTAL_MAP = 3,
        STRUCT_MAP = 4,
        FOLIAGE_MAP = 5
    };
    struct NoiseTotalSettings{
        NoiseMapSettings settings[mapCount] = 
        {NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings()};

        NoiseTotalSettings(){}
    };

}