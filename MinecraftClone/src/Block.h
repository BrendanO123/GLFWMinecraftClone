#pragma once

struct Block{
    char topLowX, topHighX, topLowY, topHighY; //top face/quad min and max x and y tex cords (not nomralized) in block map image
    char sideLowX, sideHighX, sideLowY, sideHighY;
    char bottomLowX, bottomHighX, bottomLowY, bottomHighY;
    char flagByte; //header byte with transparent and billoard flag bits

    Block(char minX, char maxX, char minY, char maxY, bool transparent=false, bool billboard=false);
    Block(
    char topMinX, char topMaxX, char topMinY, char topMaxY,
    char sideMinX, char sideMaxX, char sideMinY, char sideMaxY, 
    char bottomMinX, char bottomMaxX, char bottomMinY, char bottomMaxY,
    bool transparent=false, bool billboard=false);
    Block();
};

namespace Blocks{
    enum BlockFlags : unsigned char{
        BILLBOARD_BIT = 1,
        TRANSPARENT_BIT =(unsigned char)(1<<7)
    };

    static const float blockMapW_blocks = 4.f;
    static const float blockMapH_blocks = 4.f;
}