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
        FBM = 1,
        FBM_PARTIALS = 2,
        ERROSION = 3
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
            NoiseMapSettings(false, noiseTypes :: PERLIN, fractalTypes :: NONE, 1.0f/1000, 0.5f, 2.0f, 3, 1/1.75f);
        }
        NoiseMapSettings(bool partials, unsigned char type, unsigned char fractalMode, float f, float g, float l, int o, float bounding)
         : includePartials(partials), noiseType(type), fractalType(fractalMode), 
         frequency(f), gain(g), lacunarity(l), octaves(o), fractalBounding(bounding){}
    };

    const unsigned char mapCount = 6;
    enum noiseSettings : unsigned char{
        tempNoise = 0,
        rainNoise = 1,
        errosionMap = 2,
        continentalMap = 3,
        StructMaop = 4,
        FoliageMap = 5
    };
    struct NoiseTotalSettings{
        NoiseMapSettings settings[mapCount] = 
        {NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings(), NoiseMapSettings()};

        NoiseTotalSettings(){}
    };

}