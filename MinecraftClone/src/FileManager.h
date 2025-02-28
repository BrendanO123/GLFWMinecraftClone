#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>

#include "ChunkData.h"

using namespace std;

const string savesFolderPath = "MinecraftClone/saves/";

class FileManager{
    private:
        string saveFileName;
        constexpr static const int mainFileSize = sizeof(int32_t) * 4 + sizeof(float)* 5;
        static inline int getInt(char * contents, int offset);
        static inline float getFloat(char * contents, int offset);
        static inline void setInt(char * contents, int offset, int input);
        static inline void setFloat(char * contents, int offset, float input);

    public:
        FileManager(string name, int &seed, glm :: ivec3 &playerPositionI, glm :: vec3 &playerPositionF, glm :: vec2 &playerRoation);

        bool save(ChunkData* data);
        bool save(ChunkData* blocks, ChunkData* Structs);
        bool save(int seed, glm :: ivec3 playerPositionI, glm :: vec3 playerPositionF, glm :: vec2 playerRoation);

        ChunkData* load(int x, int z);
        ChunkData* load(string path);
        bool hasFile(int x, int z);
};
