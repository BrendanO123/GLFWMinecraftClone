#pragma once

#include <vector>

#include "Structure.h"

using namespace std;

namespace Structures{

    const GLubyte StructureCount = 2;


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
            //--> +Z                                        |
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
        }


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
                                                    //   |
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
        }


    };

    /**
     * @brief The const list of all implemented structures that do require the ability to selectivly delete blocks.
     */
    const Structure Structs[StructureCount]={
        Structure(5, 7, 5, StructsData[0].data(), StructsForcedArr[0]), Structure(16, 4, 16, StructsData[1].data(), StructsForcedArr[1])
    };

    /**
     * @brief The name of all variable fill structures and their index in the constant list.
     */
    enum STRUCT_ASSETS : unsigned char{
        OAK_TREE = 0,
        POND = 1
    };
};