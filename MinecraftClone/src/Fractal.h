#pragma once



#include "Noise.h"

namespace noise{
    class Fractal{
        public:
            NoiseTotalSettings settings;
            Noise noise = Noise();

            static const unsigned char waterLevel = 63;
            static const unsigned char sandLevel = waterLevel+2;

            Fractal(NoiseTotalSettings set) : settings(set){calcBoundings();};
            Fractal(int seed) : settings(NoiseTotalSettings(seed)){
                calcBoundings(); 
                settings.settings[noise :: TREE_MAP].gain = 0.6f;
                settings.settings[noise :: TREE_MAP].lacunarity = 2.5f;
                settings.settings[noise :: TREE_MAP].octaves = 2;

                settings.settings[noise :: GRASS_MAP].octaves = 3;
            };

            NoiseReturnStruct getNoise(glm :: ivec2 pos) const;
            glm :: vec3 FBM(glm :: ivec2 pos, NoiseMapSettings setting) const;

            void calcBoundings(){
                for(int i = 0; i < noise :: mapCount; i++){
                    noise.calcFracBounding(settings.settings[i]);
                }
            }

        private:

            glm :: u8vec2 getTerrain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental) const;


            float midlineFactorErosion(float e) const;
            float midlineFactorContinental(float c) const;
            float amplitudeFactorErosion(float e) const;
            float amplitudeFactorContinental(float c) const;

            float detailToLFunc(float e) const;
            float detailToGFunc(float e) const;
            float detailFactorContinental(float c) const;


            float getRain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental) const;
            float getTemp(glm :: ivec2 pos, float rainfall) const;

            GLubyte getFoliage(glm :: ivec2 pos, GLubyte surfaceType, float rain, float temp) const;

            glm :: vec3 genNoiseSingle(glm :: vec2 pos, int seed, bool includePartials, unsigned char noiseType) const;
    };
}