#pragma once



#include "Fractal.h"

namespace GenerationSettings{
    inline void getSettings(noise :: Fractal* fractal){
        fractal->settings.settings[noise :: TREE_MAP].frequency = 32 / 1.09617844793f;
        fractal->settings.settings[noise :: TREE_MAP].octaves = 2;
        fractal->settings.settings[noise :: TREE_MAP].fractalType = noise :: FBM;
        fractal->noise.calcFracBounding(fractal->settings.settings[noise :: TREE_MAP]);

        fractal->settings.settings[noise :: GRASS_MAP].frequency = 22/1.09617844793f;
        fractal->settings.settings[noise :: FLOWER_NOISE].frequency = 1.09617844793f / 32.f;
        fractal->settings.settings[noise :: FLOWER_NOISE].fractalType = noise :: NONE;

        fractal->settings.settings[noise :: CONTINENTAL_MAP].includePartials = true;
        fractal->settings.settings[noise :: CONTINENTAL_MAP].fractalType = noise :: NONE;
        fractal->settings.settings[noise :: CONTINENTAL_MAP].frequency = 2.5f/1000;

        fractal->settings.settings[noise :: EROSION_MAP].frequency = 4.f/1000;
        fractal->settings.settings[noise :: EROSION_MAP].includePartials = true;
        //TEMP TESTING
        /*fractal->settings.settings[noise :: EROSION_MAP].octaves = 3;
        fractal->settings.settings[noise :: EROSION_MAP].gain = 0.5f;
        //fractal->noise.calcFracBounding(fractal->settings.settings[noise :: EROSION_MAP]);*/

        fractal->settings.settings[noise :: HIGH_NOISE].octaves = 5;
        fractal->settings.settings[noise :: HIGH_NOISE].frequency = fractal->settings.settings[noise :: CONTINENTAL_MAP].frequency * fractal->settings.settings[noise :: HIGH_NOISE].lacunarity;
        fractal->noise.calcFracBounding_HL_Noise(fractal->settings.settings[noise :: HIGH_NOISE]);

        fractal->settings.settings[noise :: LOW_NOISE].octaves = 2;
        fractal->settings.settings[noise :: LOW_NOISE].gain = 0.25f;
        fractal->settings.settings[noise :: LOW_NOISE].lacunarity = 1.5f;
        fractal->settings.settings[noise :: LOW_NOISE].frequency = fractal->settings.settings[noise :: CONTINENTAL_MAP].frequency * fractal->settings.settings[noise :: LOW_NOISE].lacunarity;
        fractal->noise.calcFracBounding_HL_Noise(fractal->settings.settings[noise :: LOW_NOISE]);
        fractal->settings.settings[noise :: LOW_NOISE].fractalBounding *= 1.f / 8;
    }
}