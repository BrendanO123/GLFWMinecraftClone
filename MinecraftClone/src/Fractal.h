#pragma once



#include "Noise.h"

namespace noise{
    class Fractal{
        public:
            NoiseTotalSettings settings;
            Noise noise = Noise();
            Fractal(NoiseTotalSettings set) : settings(set){calcBoundings();};
            Fractal(){calcBoundings();};

            NoiseReturnStruct getNoise(glm :: ivec2 pos) const;
            glm :: vec3 tempFBM(glm :: ivec2 pos, NoiseMapSettings setting) const;

        private:

            void calcBoundings(){
                for(int i = 0; i < noise :: mapCount; i++){
                    noise.calcFracBounding(settings.settings[i]);
                }
            }
            glm :: vec3 FBM(glm :: ivec2 pos, unsigned char settingsIndex) const;
            glm :: u8vec2 getTerrain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental) const;

            float getRain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental) const;
            float getTemp(glm :: ivec2 pos, float rainfall) const;

            glm :: vec3 genNoiseSingle(glm :: vec2 pos, int seed, bool includePartials, unsigned char noiseType) const;
    };
}