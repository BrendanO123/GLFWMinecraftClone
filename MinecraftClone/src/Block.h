#pragma once

/**
 * @brief The block struct which contains texture information for each side and flags such as transparency.
 */
struct Block{
    
    char topLowX, topHighX, topLowY, topHighY; //top face/quad min and max x and y tex cords (not nomralized) in block map image
    char sideLowX, sideHighX, sideLowY, sideHighY;
    char bottomLowX, bottomHighX, bottomLowY, bottomHighY;
    char flagByte; //header byte with transparent and billoard flag bits

    /**
     * @brief The consturctor for a block with each side being the same sprite.
     * @param minX The left bounding wall of the subregion on the texture sheet where the block's sprite can be found (not normalized).
     * @param maxX The right bounding wall of the subregion on the texture sheet where the block's sprite can be found (not normalized).
     * @param minY The lower bounding wall of the subregion on the texture sheet where the block's sprite can be found (not normalized).
     * @param maxY The upper bounding wall of the subregion on the texture sheet where the block's sprite can be found (not normalized).
     */
    Block(char minX, char maxX, char minY, char maxY, bool transparent=false, bool billboard=false, bool waterLogable = false);


    /**
     * @brief The consturctor for a block with a different top, side, or bottom texture.
     * @param _minX The left bounding wall of the subregion on the texture sheet where the texture for a given face (top, side, bottom) can be found (not normalized).
     * @param _maxX The right bounding wall of the subregion on the texture sheet where the texture for a given face (top, side, bottom) can be found (not normalized).
     * @param _minY The lower bounding wall of the subregion on the texture sheet where the texture for a given face (top, side, bottom) can be found (not normalized).
     * @param _maxY The upper bounding wall of the subregion on the texture sheet where the texture for a given face (top, side, bottom) can be found (not normalized).
     */
    Block(
    char topMinX, char topMaxX, char topMinY, char topMaxY,
    char sideMinX, char sideMaxX, char sideMinY, char sideMaxY, 
    char bottomMinX, char bottomMaxX, char bottomMinY, char bottomMaxY,
    bool transparent=false, bool billboard=false, bool waterLogable = false);


    /**
     * @brief The default constructor.
     */
    Block();
};

/**
 * @brief The Blocks namespace contains the flag bit masks for the blocks struct such as the transparency flag bit and contains size information for the block sprite sheet.
 */
namespace Blocks{
    enum BlockFlags : unsigned char{
        BILLBOARD_BIT = 1,
        WATER_LOGABLE_BIT = 2,
        TRANSPARENT_BIT =(unsigned char)(1<<7)
    };

    static const float blockMapW_blocks = 4.f;
    static const float blockMapH_blocks = 4.f;
}