#pragma once

#include "Chunk.h"
#include "Camera.h"
#include "Blocks.h"

#include <vector>
#include <unordered_map>
#include <queue>
#include <glm/glm.hpp>

#include <ScuffedMinecraft/TupleHash.h>

using namespace std;
class World{
    public:
        World(Shader* shader);
        ~World();
        
        vector<Layer> getChunkData(int x, int z);
        void update(glm :: vec3 camPos);
        Chunk* getChunk(int x, int z);

        static World* world;
        static inline int Floor(float a){return (a<0 ? (int(a)-1) : int(a));}

    private:
        Shader* shader;
        unsigned int numChunks = 0, numChunksRendered = 0;
        unordered_map<tuple<int, int>, Chunk> chunks;
        queue<glm::vec2> chunkQueue;
        int renderDistance = 3;
        unsigned int chunkSize = 16;
        unsigned int chunksLoading = 0;
        int lastCamX = -100, lastCamZ = -100;

};