#pragma once

#include <vector>

#include "Structure.h"

using namespace std;

namespace Structures{

    const GLubyte NormStructureCount = 1;
    const GLubyte PartialFillStructureCount = 0;

    using namespace Blocks;
    const vector<vector<GLubyte>> NStructsData = {

        {//tree
            AIR,    AIR,    AIR,      AIR,  AIR,//  |
            AIR,    AIR,    AIR,      AIR,  AIR,//  |
            AIR,    AIR,    LOG_OAK,  AIR,  AIR,//  V
            AIR,    AIR,    AIR,      AIR,  AIR,//  
            AIR,    AIR,    AIR,      AIR,  AIR,//  +X      |    
            //--> +Z                                        |
                                                        //  |
            AIR,    AIR,    AIR,      AIR,  AIR,        //  V
            AIR,    AIR,    AIR,      AIR,  AIR,    
            AIR,    AIR,    LOG_OAK,  AIR,  AIR,        //  +Y
            AIR,    AIR,    AIR,      AIR,  AIR,
            AIR,    AIR,    AIR,      AIR,  AIR,

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

            AIR,     AIR,            AIR,            AIR,           AIR,
            AIR,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,    AIR,
            AIR,     LEAVES_OAK,     LOG_OAK,        LEAVES_OAK,    AIR,
            AIR,     LEAVES_OAK,     LEAVES_OAK,     LEAVES_OAK,    AIR,
            AIR,     AIR,            AIR,            AIR,           AIR,

            AIR,     AIR,           AIR,            AIR,            AIR,
            AIR,     AIR,           LEAVES_OAK,     AIR,            AIR,
            AIR,     LEAVES_OAK,    LEAVES_OAK,     LEAVES_OAK,     AIR,
            AIR,     AIR,           LEAVES_OAK,     AIR,            AIR,
            AIR,     AIR,           AIR,            AIR,            AIR
        }


    };
    const NormStructure NStructs[NormStructureCount] = {
        NormStructure(5, 6, 5, NStructsData[0].data())
    };

    
    const PartialFillStructure PFStructs[PartialFillStructureCount]={};

    void init();

    enum NORM_STRUCT_ASSETS : unsigned char{
        OAK_TREE = 0
    };
    enum PARTIAL_STRUCT_ASSETS : unsigned char{

    };
};