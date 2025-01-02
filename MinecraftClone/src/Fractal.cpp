

#include "Fractal.h"

using namespace noise;

NoiseReturnStruct Fractal :: getNoise(glm :: ivec2 pos) const{
    NoiseReturnStruct returnStruct = NoiseReturnStruct();
    returnStruct.pos=pos;

    int index, dispatchSize=16;
    glm :: vec3 erosion, continental;
    glm :: u8vec2 terrain;

    for(int x=0; x<dispatchSize; x++){
        for(int y=dispatchSize; y<dispatchSize*dispatchSize; y+=dispatchSize){
            index=x+y;
            erosion = FBM(glm :: ivec2(pos.x+x, pos.y+y), EROSION_MAP);
            continental = FBM(glm :: ivec2(pos.x+x, pos.y+y), CONTINENTAL_MAP);

            terrain = getTerrain(glm :: ivec2(pos.x+x, pos.y+y), erosion, continental);
            returnStruct.TerrainHeight[index]=terrain.x;
            returnStruct.surfaceType[index]=terrain.y;

            returnStruct.annualRainfall[index]=getRain(glm :: ivec2(pos.x+x, pos.y+y), erosion, continental);
            returnStruct.temperature[index]=getTemp(glm :: ivec2(pos.x+x, pos.y+y), returnStruct.annualRainfall[index]);


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

glm :: vec3 Fractal :: tempFBM(glm :: ivec2 Pos, NoiseMapSettings Settings) const{
    int seed = Settings.seed;
    glm :: vec2 pos = glm :: vec2 (float(Pos.x) * Settings.frequency, float(Pos.y) * Settings.frequency);

    glm :: vec3 sum = glm :: vec3 (0.f, 0.f, 0.f);
    float amplitude = Settings.fractalBounding;

    switch(Settings.fractalType){
        case noise :: FBM:

            sum = genNoiseSingle(pos, seed++, Settings.includePartials, Settings.noiseType) * amplitude;
            amplitude*= Settings.gain;
            pos*=Settings.lacunarity;

            for(int i=1; i<Settings.octaves; i++){
                sum += genNoiseSingle(pos, seed++, false, Settings.noiseType) * amplitude;

                amplitude*= Settings.gain;
                pos*=Settings.lacunarity;
            }

            return sum;
        default:
            return genNoiseSingle(pos, seed, Settings.includePartials, Settings.noiseType);
    }
}

glm :: vec3 Fractal :: FBM(glm :: ivec2 pos, unsigned char settingsIndex) const{
    NoiseMapSettings Settings = settings.settings[settingsIndex];
    return tempFBM(pos, Settings);
}


//TODO Funcs
glm :: u8vec2 Fractal :: getTerrain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental) const{
    return glm :: u8vec2(0, 0);
}

float Fractal :: getRain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental) const{return 1.0f;}
float Fractal :: getTemp(glm :: ivec2 pos, float rainfall) const{return 1.0f;}