#pragma once

#include "Chunk.h"
#include "ChunkData.h"
#include "Camera.h"
#include "Blocks.h"

#include <vector>
#include <unordered_map>
#include <queue>
#include <glm/glm.hpp>
#include <mutex>

#include <ScuffedMinecraft/TupleHash.h>

using namespace std;
class World{
    public:
        World(Shader* shader);
        ~World();
        
        Chunk* getChunk(int x, int z);
        ChunkData* getChunkData(int x, int z); // i like the threading ideas, I don't think I want vertical chunks, 
        void update(glm :: vec3 camPos);

        static inline int Floor(float a){return (a<0 ? (int(a)-1) : int(a));}
        void Lock(){mute.try_lock();}
        void Unlock(){mute.unlock();}

        static World* world;
        std :: mutex mute;

    private:
        void threadUpdate();

        unordered_map<tuple<int, int>, Chunk*> chunks;
        unordered_map<tuple<int, int>, ChunkData*> chunkData;

        queue<glm::vec2> chunkQueue;

        std :: thread updateThread;

        Shader* shader;

        bool shouldEnd=false;

        unsigned int numChunks = 0, numChunksRendered = 0, chunksLoading = 0;
        int lastCamX = -100, lastCamZ = -100;
        int camX_chunk = -101, camZ_chunk = -101;

        int renderDistance = 3;
        unsigned int chunkSize = 16;
};