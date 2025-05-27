#pragma once

#include <vector>

#include "Structure.h"

using namespace std;

namespace Structures{

    const GLubyte StructureCount = 15;

    using namespace Blocks;

    const vector<vector<GLubyte>> StructsData = {

        {//tree
            AIR, AIR,   GRASS, AIR,   AIR,
            AIR, GRASS, GRASS, AIR,   AIR,  
            AIR, GRASS, DIRT,  GRASS, AIR,  
            AIR, AIR,   GRASS, GRASS, AIR,
            AIR, AIR,   AIR,   AIR,   AIR,

            AIR, AIR, AIR,      AIR,  AIR,//  |
            AIR, AIR, AIR,      AIR,  AIR,//  |
            AIR, AIR, LOG_OAK,  AIR,  AIR,//  V
            AIR, AIR, AIR,      AIR,  AIR,//  
            AIR, AIR, AIR,      AIR,  AIR,//  +X      |    
            //--> +Z                                  |
                                                  //  |
            AIR, AIR, AIR,      AIR,  AIR,        //  V
            AIR, AIR, AIR,      AIR,  AIR,    
            AIR, AIR, LOG_OAK,  AIR,  AIR,        //  +Y
            AIR, AIR, AIR,      AIR,  AIR,
            AIR, AIR, AIR,      AIR,  AIR,

            AIR,            LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     AIR,
            LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,
            LEAVES_OAK,     LEAVES_OAK,     LOG_OAK,        LEAVES_OAK,     LEAVES_OAK,
            LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,
            AIR,            LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     AIR,

            AIR,            LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     AIR,
            LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,
            LEAVES_OAK,     LEAVES_OAK,     LOG_OAK,        LEAVES_OAK,     LEAVES_OAK,
            LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,
            AIR,            LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,     AIR,

            AIR, AIR,            AIR,            AIR,           AIR,
            AIR, LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK, AIR,
            AIR, LEAVES_OAK,     LOG_OAK,        LEAVES_OAK, AIR,
            AIR, LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK, AIR,
            AIR, AIR,            AIR,            AIR,           AIR,

            AIR, AIR,           AIR,            AIR,            AIR,
            AIR, AIR,           LEAVES_OAK,     AIR,            AIR,
            AIR, LEAVES_OAK,    LEAVES_OAK,     LEAVES_OAK,     AIR,
            AIR, AIR,           LEAVES_OAK,     AIR,            AIR,
            AIR, AIR,           AIR,            AIR,            AIR
        },

        //16 z
        //16 x
        {//pond
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   WATER, WATER, AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, WATER, WATER, WATER, WATER, AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   WATER, WATER, AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   WATER, AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR, AIR, AIR,   AIR,   AIR,   AIR,   AIR, AIR, AIR, AIR, AIR, AIR, AIR,

            AIR, AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,    AIR,   AIR,   AIR,   AIR,  AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,    AIR,   AIR,   AIR,   AIR,  AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,    AIR,   AIR,   AIR,   AIR,  AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   AIR,   AIR,   SAND,   SAND,  AIR,   AIR,   AIR,  AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   SAND,  SAND,  SAND,   WATER, SAND,  AIR,   AIR,  AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  SAND,  SAND,  WATER, WATER,  WATER, SAND,  SAND,  AIR,  AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, SAND, SAND,  WATER, WATER, WATER,  WATER, WATER, SAND,  SAND, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, SAND, WATER, WATER, WATER, WATER,  WATER, WATER, WATER, SAND, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  SAND,  WATER, WATER, WATER,  WATER, SAND,   SAND, AIR,  AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  SAND,  SAND,  WATER, WATER,  WATER, SAND,   AIR,   AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   SAND,  WATER, WATER,  SAND,  SAND,   AIR,   AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   AIR,   SAND,  SAND,   SAND,  AIR,    AIR,   AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   AIR,   AIR,   SAND,   AIR,   AIR,    AIR,   AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,    AIR,   AIR,    AIR,   AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,    AIR,   AIR,    AIR,   AIR, AIR, AIR, AIR, AIR,
            AIR, AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,    AIR,   AIR,    AIR,   AIR, AIR, AIR, AIR, AIR,

            AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,   SAND,  SAND,  AIR,   AIR,   AIR,   AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  AIR,   AIR,   SAND,  SAND,  SAND,  SAND,  SAND,  AIR,   AIR,   AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  AIR,   SAND,  SAND,  SAND,  WATER, WATER, SAND,  SAND,  AIR,   AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  SAND,  SAND,  WATER, WATER, WATER, WATER, WATER, SAND,  SAND,  AIR,  AIR,  AIR, AIR,
            AIR, AIR, SAND, SAND,  WATER, WATER, WATER, WATER, WATER, WATER, WATER, SAND,  SAND, AIR,  AIR, AIR,
            AIR, AIR, SAND, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, SAND, SAND, AIR, AIR,
            AIR, AIR, SAND, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, SAND, SAND, AIR, AIR,
            AIR, AIR, SAND, SAND,  WATER, WATER, WATER, WATER, WATER, WATER, WATER, SAND,  SAND, AIR,  AIR, AIR,
            AIR, AIR, AIR,  SAND,  WATER, WATER, WATER, WATER, WATER, WATER, SAND,  SAND,  AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  SAND,  SAND,  WATER, WATER, WATER, WATER, WATER, SAND,  AIR,   AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  AIR,   SAND,  SAND,  WATER, WATER, WATER, SAND,  SAND,  AIR,   AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  AIR,   AIR,   SAND,  SAND,  WATER, SAND,  SAND,  AIR,   AIR,   AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  AIR,   AIR,   AIR,   SAND,  SAND,  SAND,  AIR,   AIR,   AIR,   AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,  AIR,  AIR, AIR,
            AIR, AIR, AIR,  AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,   AIR,  AIR,  AIR, AIR,

            AIR, AIR,  AIR,  AIR,  AIR,  AIR,  SAND, SAND, SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,
            AIR, AIR,  AIR,  AIR,  AIR,  SAND, SAND, AIR,  SAND, SAND, SAND, AIR,  AIR,  AIR,  AIR,  AIR,
            AIR, AIR,  AIR,  AIR,  SAND, AIR,  AIR,  AIR,  AIR,  AIR,  SAND, SAND, AIR,  AIR,  AIR,  AIR,
            AIR, AIR,  AIR,  SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  SAND, SAND, AIR,  AIR,  AIR,
            AIR, AIR,  SAND, SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  SAND, AIR,  AIR,  AIR,
            AIR, SAND, SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  SAND, AIR,  AIR,
            AIR, SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  SAND, AIR,
            AIR, SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  SAND, AIR,
            AIR, SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  SAND, SAND, AIR,
            AIR, AIR,  SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  SAND, SAND, AIR,  AIR,
            AIR, AIR,  AIR,  SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  SAND, SAND, AIR,  AIR,  AIR,
            AIR, AIR,  AIR,  SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  SAND, AIR,  AIR,  AIR,  AIR,
            AIR, AIR,  AIR,  AIR,  SAND, AIR,  AIR,  AIR,  AIR,  SAND, SAND, AIR,  AIR,  AIR,  AIR,  AIR,
            AIR, AIR,  AIR,  AIR,  AIR,  SAND, AIR,  AIR,  SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,
            AIR, AIR,  AIR,  AIR,  AIR,  AIR,  SAND, SAND, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,
            AIR, AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,  AIR,
        },

        //basics

        {
            TALL_GRASS_BOTTOM,
            TALL_GRASS_TOP
        }, {SHORT_GRASS},
        
        {BLUE_LILAC}, {CORNFLOWER}, {ALLIUM}, {TULIP_PINK}, {ROSE}, {TULIP_ORANGE}, {DANDILION}, {TULIP_WHITE},

        {LILAC_BOTTOM, LILAC_TOP}, {PEONY_BOTTOM, PEONY_TOP}, {ROSEBUSH_BOTTOM, ROSEBUSH_TOP}
    };

    const vector<vector<bool>> StructsForcedArr = {

        {//tree
           false, false, false, false, false,
           false, false, false, false, false, 
           false, false, true,  false, false, 
           false, false, false, false, false,
           false, false, false, false, false,


           false, false, false, false, false,//  |
           false, false, false, false, false,//  |
           false, false, true,  false, false,//  V
           false, false, false, false, false,// 
           false, false, false, false, false,//  +X      |   
           //--> +Z                                      |
                                                     //  |
           false, false, false, false, false,        //  V
           false, false, false, false, false,   
           false, false, true,  false, false,        // +Y
           false, false, false, false, false,
           false, false, false, false, false,


           false, true, true, true, false,
           true,  true, true, true, true,
           true,  true, true, true, true,
           true,  true, true, true, true,
           false, true, true, true, false,


           false, true, true, true, false,
           true,  true, true, true, true,
           true,  true, true, true, true,
           true,  true, true, true, true,
           false, true, true, true, false,


           false, false, false, false, false,
           false, true,  true,  true,  false,
           false, true,  true,  true,  false,
           false, true,  true,  true,  false,
           false, false, false, false, false,


           false, false, false, false, false,
           false, false, true,  false, false,
           false, true,  true,  true,  false,
           false, false, true,  false, false,
           false, false, false, false, false
        },

        //16 z
        //16 x
        {//pond
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, true,  true,  false, false, false, false, false, false, false, false,
            false, false, false, false, false, true,  true,  true,  true,  false, false, false, false, false, false, false,
            false, false, false, false, false, false, true,  true,  false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, true,  false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,


            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, true,  true,  false, false, false, false, false, false, false,
            false, false, false, false, false, true,  true,  true,  true,  true,  false, false, false, false, false, false,
            false, false, false, false, true,  true,  true,  true,  true,  true,  true,  false, false, false, false, false,
            false, false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false, false, false,
            false, false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false, false, false,
            false, false, false, false, true,  true,  true,  true,  true,  true,  true,  false, false, false, false, false,
            false, false, false, false, true,  true,  true,  true,  true,  true,  false, false, false, false, false, false,
            false, false, false, false, false, true,  true,  true,  true,  true,  false, false, false, false, false, false,
            false, false, false, false, false, false, true,  true,  true,  false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,


            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, true,  true,  false, false, false, false, false, false, false,
            false, false, false, false, false, false, true,  true,  true,  true,  false, false, false, false, false, false,
            false, false, false, false, false, true,  true,  true,  true,  true,  true,  false, false, false, false, false,
            false, false, false, false, true,  true,  true,  true,  true,  true,  true,  true,  false, false, false, false,
            false, false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false, false,
            false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false, false,
            false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false,
            false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false, false,
            false, false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false, false, false,
            false, false, false, true,  true,  true,  true,  true,  true,  true,  true,  false, false, false, false, false,
            false, false, false, false, true,  true,  true,  true,  true,  true,  true,  false, false, false, false, false,
            false, false, false, false, false, true,  true,  true,  true,  true,  false, false, false, false, false, false,
            false, false, false, false, false, false, true,  true,  true,  false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,


            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, true,  false, false, false, false, false, false, false, false,
            false, false, false, false, false, true,  true,  true,  true,  true,  false, false, false, false, false, false,
            false, false, false, false, true,  true,  true,  true,  true,  true,  true,  false, false, false, false, false,
            false, false, false, false, true,  true,  true,  true,  true,  true,  true,  true,  false, false, false, false,
            false, false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false, false,
            false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false,
            false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false,
            false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false, false,
            false, false, false, true,  true,  true,  true,  true,  true,  true,  true,  true,  false, false, false, false,
            false, false, false, false, true,  true,  true,  true,  true,  true,  true,  false, false, false, false, false,
            false, false, false, false, true,  true,  true,  true,  true,  true,  true,  false, false, false, false, false,
            false, false, false, false, false, true,  true,  true,  true,  false, false, false, false, false, false, false,
            false, false, false, false, false, false, true,  true,  false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
        },

        //basics

        {
            true,
            true
        },

        {true}, {true}, {true}, {true}, {true}, {true}, {true}, {true}, {true},

        {true, true}, {true, true}, {true, true}


    };

    /**
     * @brief The const list of all implemented structures that do require the ability to selectivly delete blocks.
     */
    const Structure Structs[StructureCount]={
        Structure(5, 7, 5, 0, StructsData[0].data(), StructsForcedArr[0]), Structure(16, 4, 16, 1, StructsData[1].data(), StructsForcedArr[1]),
        Structure(1, 2, 1, 2, StructsData[2].data(), StructsForcedArr[2]), Structure(1, 1, 1, 3, StructsData[3].data(), StructsForcedArr[3]),

        Structure(1, 1, 1, 4, StructsData[4].data(), StructsForcedArr[4]), Structure(1, 1, 1, 5, StructsData[5].data(), StructsForcedArr[5]),
        Structure(1, 1, 1, 6, StructsData[6].data(), StructsForcedArr[6]), Structure(1, 1, 1, 7, StructsData[7].data(), StructsForcedArr[7]),
        Structure(1, 1, 1, 8, StructsData[8].data(), StructsForcedArr[8]), Structure(1, 1, 1, 9, StructsData[9].data(), StructsForcedArr[9]),
        Structure(1, 1, 1, 10, StructsData[10].data(), StructsForcedArr[10]), Structure(1, 1, 1, 11, StructsData[11].data(), StructsForcedArr[11]),

        Structure(1, 2, 1, 12, StructsData[12].data(), StructsForcedArr[12]), Structure(1, 2, 1, 13, StructsData[13].data(), StructsForcedArr[13]),
        Structure(1, 2, 1, 14, StructsData[14].data(), StructsForcedArr[14])
    };

    /**
     * @brief The name of all variable fill structures and their index in the constant list.
     */
    /*enum STRUCT_ASSETS : unsigned char{
        OAK_TREE = 0,
        POND = 1,

        TALL_GRASS = 2,
        SHORT_GRASS_STRUCT = 3,

        BLUE_LILAC_STRUCT = 4,
        CORNFLOWER_STRUCT = 5,
        ALLIUM_STRUCT = 6,
        TULIP_PINK_STRUCT = 7,
        ROSE_STRUCT = 8,
        TULIP_ORANGE_STRUCT = 9,
        DANDILION_STRUCT = 10,
        TULIP_WHITE_STRUCT = 11,

        LILAC = 12,
        PEONY = 13,
        ROSEBUSH = 14
    };*/
};