#include "Block.h"

Block :: Block(char minX, char maxX, char minY, char maxY, bool transparent, bool billboard, bool solid, bool waterLoggable, bool translucent){
    topLowX=sideLowX=bottomLowX=minX;
    topHighX=sideHighX=bottomHighX=maxX;
    topLowY=sideLowY=bottomLowY=minY;
    topHighY=sideHighY=bottomHighY=maxY;
    flagByte = 
        (transparent ? Blocks :: TRANSPARENT_BIT : 0) + 
        (billboard ? Blocks :: BILLBOARD_BIT : 0) + 
        (solid ? Blocks :: SOLID_BIT : 0) + 
        (waterLoggable ? Blocks :: WATER_LOGGABLE_BIT : 0) + 
        (translucent ? Blocks :: TRANSLUCENT_BIT : 0);
}

Block :: Block(
    char topMinX, char topMaxX, char topMinY, char topMaxY,
    char sideMinX, char sideMaxX, char sideMinY, char sideMaxY, 
    char bottomMinX, char bottomMaxX, char bottomMinY, char bottomMaxY,
    bool transparent, bool billboard, bool solid, bool waterLoggable, bool translucent){

    topLowX=topMinX; topHighX=topMaxX; topLowY=topMinY; topHighY=topMaxY;
    sideLowX=sideMinX; sideHighX=sideMaxX; sideLowY=sideMinY; sideHighY=sideMaxY;
    bottomLowX=bottomMinX; bottomHighX=bottomMaxX; bottomLowY=bottomMinY; bottomHighY=bottomMaxY;
    
    flagByte = 
        (transparent ? Blocks :: TRANSPARENT_BIT : 0) + 
        (billboard ? Blocks :: BILLBOARD_BIT : 0)+ 
        (solid ? Blocks :: SOLID_BIT : 0) + 
        (waterLoggable ? Blocks :: WATER_LOGGABLE_BIT : 0) + 
        (translucent ? Blocks :: TRANSLUCENT_BIT : 0);
}
Block :: Block(){}