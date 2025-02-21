#pragma once

#include <glad/gl.h>


#include "Block.h"

namespace Blocks{

    const GLubyte blockCount = 36;


    /**
     * @brief the list of all blocks currently implemented indexed by the values given in the BLOCKS enum.
     */
    const Block blocks[blockCount] = {
        Block(0, 0, 0, 0, true, false, false, true), //air block: tex = na, trans = true, waterLog = true
        Block(0, 1, 0, 1), //dirt block: tex = (0,0)
        Block( //grass block (unique faces)
            1, 2, 1, 2, //top: tex = (0,2)
            1, 2, 0, 1, //side: tex = (0,1)
            0, 1, 0, 1 //bottom = dirt: tex = (0,0)
            ),
        Block(0, 1, 1, 2), //stone block: tex = (1,0)
        Block( //oak log (unique faces)
            3, 4, 0, 1, //top: tex = (2,1)
            2, 3, 0, 1, //side: tex = (2,0)
            3, 4, 0, 1 //bottom = top: tex = (2,1)
        ),
        Block(0, 1, 2, 3, true, false, false), //oak leaves: tex = (1,1)
        Block(1, 2, 2, 3, true, true, false), //grass fan

        Block(5, 6, 1, 2, true, true, false), //tall grass bottom
        Block(5, 6, 2, 3, true, true, false), //tall grass top

        Block(2, 3, 1, 2, true, true, false), //lilac bottom
        Block(2, 3, 2, 3, true, true, false), //lilac top

        Block(3, 4, 1, 2, true, true, false), //peony bottom
        Block(3, 4, 2, 3, true, true, false), //peony top

        Block(4, 5, 1, 2, true, true, false), //rosebush bottom
        Block(4, 5, 2, 3, true, true, false), //rosebush top

        Block(0, 1, 3, 4, true, true, false), //blue lilac
        Block(1, 2, 3, 4, true, true, false), //cornflower
        Block(2, 3, 3, 4, true, true, false), //allium
        Block(3, 4, 3, 4, true, true, false), //pink tulip
        Block(4, 5, 3, 4, true, true, false), //rose/poppy
        Block(5, 6, 3, 4, true, true, false), //orange tulip
        Block(6, 7, 3, 4, true, true, false), //dandilion
        Block(7, 8, 3, 4, true, true, false), //white tulip


        Block( //water
            6, 7, 2, 3, //top: tex = (2,1)
            6, 7, 1, 2, //side: tex = (2,0)
            6, 7, 0, 1, //bottom: tex = (2,1)
            false, false, false, false, true), 
        Block(4, 5, 0, 1), //sand
        Block(5, 6, 0, 1), //gravel
        Block(7, 8, 1, 2, true), //glass
        Block(7, 8, 2, 3), //cobble
        Block(8, 9, 3, 4), //brick
        Block(8, 9, 2, 3), //oak planks
        Block(8, 9, 1, 2), //polished andesite
        Block(8, 9, 0, 1), //coarse dirt

        Block(9, 10, 0, 1), //dark oak planks
        Block( //spruce log (unique faces)
            9, 10, 2, 3, //top: tex = (2,1)
            9, 10, 1, 2, //side: tex = (2,0)
            9, 10, 2, 3 //bottom = top: tex = (2,1)
        ),
        Block( //podzol block (unique faces)
            10, 11, 1, 2, //top: tex = (0,2)
            10, 11, 0, 1, //side: tex = (0,1)
            0, 1, 0, 1 //bottom = dirt: tex = (0,0)
        ),
        Block(10, 11, 2, 3) //rooted dirt
    };


    /**
     * @brief The block type values (also indicies in the blocks array) that are actually stored in chunks and their corresponding name.
     */
    enum BLOCKS : unsigned char{
        AIR = 0,
        DIRT = 1,
        GRASS = 2,
        STONE = 3,
        LOG_OAK = 4,
        LEAVES_OAK = 5,

        SHORT_GRASS = 6,
        TALL_GRASS_BOTTOM = 7,
            TALL_GRASS_TOP = 8,
        LILAC_BOTTOM = 9,
            LILAC_TOP = 10,
        PEONY_BOTTOM = 11,
            PEONY_TOP= 12,
        ROSEBUSH_BOTTOM = 13,
            ROSEBUSH_TOP = 14,

        BLUE_LILAC = 15,
        CORNFLOWER = 16,
        ALLIUM = 17,
        TULIP_PINK = 18,
        ROSE = 19,
        TULIP_ORANGE = 20,
        DANDILION = 21,
        TULIP_WHITE = 22,
        
        WATER = 23,
        SAND = 24,
        GRAVEL = 25,
        GLASS = 26,
        COBBLE_STONE = 27,
        BRICK = 28, 
        OAK_PLANKS = 29,
        SMOOTH_ANDESITE = 30,
        COARSE_DIRT = 31,
        DARK_PLANKS = 32,
        DARK_LOG = 33,
        PODZOL = 34,
        ROOTED_DIRT = 35
    };
}