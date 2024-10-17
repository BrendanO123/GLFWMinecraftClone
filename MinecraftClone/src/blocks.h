#pragma once

#include "block.h"

namespace Blocks{

    const Block blocks[9] = {
        Block(0, 0, 0, 0, true), //air block: tex = na, trans = true
        Block(0, 1, 0, 1), //dirt block: tex = (0,0)
        Block( //grass block (unique faces)
            0, 1, 2, 3, //top: tex = (0,2)
            0, 1, 1, 2, //side: tex = (0,1)
            0, 1, 0, 1 //bottom = dirt: tex = (0,0)
            ),
        Block(1, 2, 0, 1), //stone block: tex = (1,0)
        Block( //oak log (unique faces)
            2, 3, 1, 2, //top: tex = (2,1)
            2, 3, 0, 1, //side: tex = (2,0)
            2, 3, 1, 2 //bottom = top: tex = (2,1)
        ),
        Block(1, 2, 1, 2, true), //oak leaves: tex = (1,1)
        Block(1, 2, 2, 3, true, true), //grass fan
        Block(3, 4, 0, 1, true, true), //tall grass bottom
        Block(3, 4, 1, 2, true, true), //tall grass top
    };

    enum BLOCKS{
        AIR = 0,
        DIRT = 1,
        GRASS = 2,
        STONE = 3,
        LOG_OAK = 4,
        LEAVES_OAK = 5,
        SHORT_GRASS = 6,
        TALL_GRASS_BOTTOM = 7,
        TALL_GRASS_TOP = 8
    };
}