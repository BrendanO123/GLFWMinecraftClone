#pragma once



#include "Noise.h"

namespace noise{
    class Fractals{
        public:
            NoiseTotalSettings settings;
            Fractals(NoiseTotalSettings set) : settings(set){};
            Fractals(){};

            NoiseReturnStruct getNoise(glm :: ivec2 pos);

        private:

            glm :: vec3 FBM(glm :: ivec2 pos, unsigned char settingsIndex);
            float getRain(glm :: ivec2 pos, glm :: vec3 erosion, glm :: vec3 continental);
            float getTemp(glm :: ivec2 pos, float rainfall);
    };
}