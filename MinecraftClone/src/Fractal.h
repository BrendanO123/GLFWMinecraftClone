#pragma once



#include "Noise.h"

namespace noise{
    class Fractal{
        public:
            NoiseTotalSettings settings = NoiseTotalSettings(0);
            Noise noise = Noise();

            static const unsigned char waterLevel = 95;
            static const unsigned char sandLevel = waterLevel+2;
            static const unsigned char gravelLevel = waterLevel-5;

            Fractal(NoiseTotalSettings set) : settings(set){calcBoundings();};
            Fractal(int seed){
                int i = (rand() & 15) + 1;
                for(int j = 0; j<i; j++){rand();}
                settings = NoiseTotalSettings(rand());
                calcBoundings();
            };

            NoiseReturnStruct getNoise(glm :: ivec2 pos) const;
            glm :: vec3 FBM(glm :: ivec2 pos, const NoiseMapSettings setting) const;

            void calcBoundings(){
                for(int i = 0; i < noise :: mapCount; i++){
                    noise.calcFracBounding(settings.settings[i]);
                }
            }

        private:

            glm :: u8vec2 getTerrain(glm :: ivec2 pos, float erosionS, glm :: vec3 continental) const;

            float getRain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental) const;
            float getTemp(glm :: ivec2 pos, float rainfall) const;

            GLubyte getFoliage(glm :: ivec2 pos, GLubyte surfaceType, float rain, float temp) const;

            glm :: vec3 genNoiseSingle(glm :: vec2 pos, int seed, bool includePartials, unsigned char noiseType) const;
    };
}