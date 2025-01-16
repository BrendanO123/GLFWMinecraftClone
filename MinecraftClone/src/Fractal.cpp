#include <iostream>

#include "Fractal.h"
#include "Structures.h"

using namespace noise;

NoiseReturnStruct Fractal :: getNoise(glm :: ivec2 pos) const{
    NoiseReturnStruct returnStruct = NoiseReturnStruct();
    returnStruct.pos=pos;

    int index, dispatchSize=16;
    int minHeight = 255, maxHeight = 0;
    glm :: vec3 erosion, continental;
    glm :: u8vec2 terrain;

    for(int x=0; x<dispatchSize; x++){
        for(int z=0; z<dispatchSize; z++){
            index= dispatchSize-z-1 + x*dispatchSize;
            erosion = FBM(glm :: ivec2(pos.x * dispatchSize + x, pos.y * dispatchSize + z), settings.settings[EROSION_MAP]);
            continental = FBM(glm :: ivec2(pos.x * dispatchSize + x, pos.y * dispatchSize + z), settings.settings[CONTINENTAL_MAP]);

            terrain = getTerrain(glm :: ivec2(pos.x * dispatchSize + x, pos.y * dispatchSize + z), erosion, continental);
            returnStruct.TerrainHeight[index]=terrain.x;
            returnStruct.surfaceType[index]=terrain.y;

            if(terrain.x < minHeight){minHeight = terrain.x;}
            if(terrain.x > maxHeight){maxHeight = terrain.x;}

            returnStruct.annualRainfall[index]=getRain(glm :: ivec2(pos.x * dispatchSize + x, pos.y * dispatchSize + z), erosion, continental);
            returnStruct.temperature[index]=getTemp(glm :: ivec2(pos.x * dispatchSize + x, pos.y * dispatchSize + z), returnStruct.annualRainfall[index]);

            returnStruct.foliage[index] = getFoliage(glm :: ivec2(pos.x * dispatchSize + x, pos.y * dispatchSize + z), terrain.y, returnStruct.annualRainfall[index], returnStruct.temperature[index]);
        }
    }
    return returnStruct;
}

glm :: vec3 Fractal :: genNoiseSingle(glm :: vec2 pos, int seed, bool includePartials, unsigned char noiseType) const{
    switch(noiseType){
        case PERLIN:
            if(includePartials){
                return noise.analyticalPerlin(seed, pos.x, pos.y);
            }
            return glm :: vec3(noise.SinglePerlin(seed, pos.x, pos.y), 0.f, 0.f);
        case VALUE_CUBIC:
            //TODO:
            return noise.analyticalPerlin(seed, pos.x, pos.y);
            break;
        case WHITE:
            //Default
        default:
            //default to perlin for now but should be white noise
            if(includePartials){
                return noise.analyticalPerlin(seed, pos.x, pos.y);
            }
            return glm :: vec3(noise.SinglePerlin(seed, pos.x, pos.y), 0.f, 0.f);
            //TODO WHITE
            break;
    }
}

glm :: vec3 Fractal :: FBM(glm :: ivec2 Pos, NoiseMapSettings Settings) const{
    int seed = Settings.seed;
    glm :: vec2 pos = glm :: vec2 (float(Pos.x + Settings.xOffset) * Settings.frequency, float(Pos.y + Settings.yOffset) * Settings.frequency);

    glm :: vec3 sum = glm :: vec3 (0.f, 0.f, 0.f);
    float amplitude = Settings.fractalBounding;

    switch(Settings.fractalType){
        case noise :: FBM:

            sum = genNoiseSingle(pos, seed++, Settings.includePartials, Settings.noiseType) * amplitude;
            amplitude *= Settings.gain;
            pos *= Settings.lacunarity;

            for(int i=1; i<Settings.octaves; i++){
                sum += genNoiseSingle(pos, seed++, false, Settings.noiseType) * amplitude;

                amplitude *= Settings.gain;
                pos *= Settings.lacunarity;
            }

            return sum;
        default:
            return genNoiseSingle(pos, seed, Settings.includePartials, Settings.noiseType);
    }
}




inline float SCurve(float t) { return t * t * (3 - 2 * t); }


const float flowerChance = 1 - 0.3f;
const float threshold = 0.65f;
GLubyte Fractal :: getFoliage(glm :: ivec2 pos, GLubyte surfaceType, float rain, float temp) const{
    if(surfaceType != Blocks :: GRASS){return (unsigned char)(-1);}
    
    float treeValue = /*(noise.GradCoord(settings.settings[noise :: TREE_MAP].seed, pos.x * noise.PrimeX, pos.y * noise.PrimeY) + */FBM(glm :: ivec2(pos.x, pos.y), settings.settings[noise :: TREE_MAP]).x/*/2)/(1+1.f/2)*/;
    float grassValue =/*(noise.ValCoord(settings.settings[noise :: GRASS_MAP].seed, pos.x * noise.PrimeX, pos.y * noise.PrimeY) + */FBM(glm :: ivec2(pos.x, pos.y), settings.settings[noise :: GRASS_MAP]).x/*/3)/(1+1/3.f)*/;

    if(treeValue >= threshold){return Structures :: OAK_TREE;}
    else if(grassValue >= 0.6f){return Structures :: TALL_GRASS;}
    else if(grassValue >= 0.25f){
        if(noise.ValCoord(settings.settings[noise :: GRASS_MAP].seed+1, pos.x * noise.PrimeX, pos.y * noise.PrimeY) >= flowerChance){
            switch(int(SCurve((noise.SinglePerlin(
                        settings.settings[noise :: GRASS_MAP].seed+
                            settings.settings[noise :: GRASS_MAP].octaves+
                            1, 
                        pos.x * settings.settings[noise :: GRASS_MAP].frequency / 2.5f, 
                        pos.y * settings.settings[noise :: GRASS_MAP].frequency / 2.5f)
                     + 1) / 2.0f) * 5)){
                case 1:
                    return Structures :: ROSE_STRUCT;
                
                case 2:
                    return Structures :: TULIP_PINK_STRUCT;

                case 3:
                    return Structures :: TULIP_ORANGE_STRUCT;

                default:
                    return Structures :: TULIP_WHITE_STRUCT;
            }
        }
        return Structures :: SHORT_GRASS_STRUCT;
    }
    return (unsigned char)(-1);


}


//e to midline variables
const float eMidlineFactorMin = 0.7f;
const float eMidlineFactorMax = 1.5f;
const float eMidlineFactorLeftBound = -0.75f;
const float eMidlineFactorRightBound = 0.75f;

inline float Fractal :: midlineFactorErosion(const float e) const{
    return 
        (e >= eMidlineFactorRightBound ? eMidlineFactorMin : 
            (e <= eMidlineFactorLeftBound ? eMidlineFactorMax : 
                (
                (eMidlineFactorMax - eMidlineFactorMin) * 
                SCurve((eMidlineFactorRightBound - e) / (eMidlineFactorRightBound - eMidlineFactorLeftBound))
                + eMidlineFactorMin
                ) / eMidlineFactorMax
            )
        );
}


//c to midline variables
const float cMidlineFactorLeftBound = -0.75f;
const float cMidlineFactorRightBound = 0.75f;

inline float Fractal :: midlineFactorContinental(const float c) const{
    return 
    (c <= cMidlineFactorLeftBound ? -1 : 
        (c >= cMidlineFactorRightBound ? 1 : 
            (
            2 * 
            SCurve((c + cMidlineFactorRightBound) / (cMidlineFactorRightBound - cMidlineFactorLeftBound)) 
            - 1
            )
        )
    );
}


//e to amplitude
const float eToAmpFactorLeftBound = -0.75f;
const float eToAmpFactorRightBound = 0.75f;
const float eToAmpFactorMin = 0.1875f;

inline float Fractal :: amplitudeFactorErosion(const float e) const{
    return 
        (e <= eToAmpFactorLeftBound ? 1 : 
            (e >= eToAmpFactorRightBound ? eToAmpFactorMin : 
                (
                (1 - eToAmpFactorMin) * 
                SCurve((eToAmpFactorRightBound - e) / (eToAmpFactorRightBound - eToAmpFactorLeftBound))
                + eToAmpFactorMin
                )
            )
        );
}


//c to amplitude variables
const float cToAmpFactorBoundDist = 0.625f;

inline float Fractal :: amplitudeFactorContinental(const float c) const{
    float C = noise.FastAbs(c);
    return (C >= cToAmpFactorBoundDist ? 1 : SCurve(C / cToAmpFactorBoundDist));
}


//detail control variables
const float DetailLeftBound = -0.75f;
const float DetailRightBound = 0.75f;

//L of fractal
const float MinL = 1.5f;
const float MaxL = 2.0f;

inline float Fractal :: detailToLFunc(const float e) const{
    return 
        (e >= DetailRightBound ? MinL : 
            (e <= DetailLeftBound ? MaxL : 
                (
                (MaxL - MinL) *
                SCurve((e + DetailLeftBound) / (DetailLeftBound - DetailRightBound))
                + MinL
                )
            )
        ); 
}

//Gain of fractal
const float MinG = 0.25f;
const float MaxG = 0.5f;

inline float Fractal :: detailToGFunc(const float e) const{
    return 
        (e >= DetailRightBound ? MinG : 
            (e <= DetailLeftBound ? MaxG : 
                (
                (MaxG - MinG) *
                SCurve((e + DetailLeftBound) / (DetailLeftBound - DetailRightBound))
                + MinG
                )
            )
        ); 
}


//c to L and G
const float cToLGBoundDist = 0.35f;
const float cToLGMinFactor = 0.6f;
inline float Fractal :: detailFactorContinental(const float c) const{
    float C = noise.FastAbs(c);
    return (C >= cToLGBoundDist ? 1 : (1 - cToLGMinFactor) * SCurve(C / cToLGBoundDist) + cToLGMinFactor);
}


//world amplitude
const float worldAmplitude = 40;

glm :: u8vec2 Fractal :: getTerrain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental) const{

    /*unsigned char midline = (unsigned char)(int(midlineFactorErosion(erosion.x) * midlineFactorErosion(continental.x) * (worldAmplitude / 1.2f)) + 63);
    float gain = detailToLFunc(detailFactorContinental(continental.x) * (erosion.x + 1) - 1);
    float lacunarity = detailToGFunc(detailFactorContinental(continental.x) * (erosion.x + 1) - 1);
    
    
    NoiseMapSettings set = NoiseMapSettings(settings.terrainSeed, false, noise :: PERLIN, noise :: FBM, settings.terrainFrequency, gain, lacunarity, 6, 1.0f);
    noise.calcFracBounding(set);

    unsigned char height = (unsigned char) (FBM(pos, set).x * (amplitudeFactorErosion(erosion.x) * amplitudeFactorContinental(continental.x) * (worldAmplitude / 6.f)) + midline);*/
    unsigned char height = (unsigned char)(int((SCurve(erosion.x * 0.5f + 0.5f) * 2.f - 1.f) * worldAmplitude)+63);
    return 
    glm :: u8vec2(
        height, 
        (height <= sandLevel ? Blocks :: SAND : Blocks :: GRASS)
    );
}

//TODO
float Fractal :: getRain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental) const{return 1.0f;}
float Fractal :: getTemp(glm :: ivec2 pos, float rainfall) const{return 1.0f;}