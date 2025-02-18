#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <glm/glm.hpp>
#include <mutex>

#include "Chunk.h"
#include "ChunkData.h"
#include "Camera.h"
#include "Blocks.h"
#include "Fractal.h"
#include "ChunkList.h"

#include <ScuffedMinecraft/TupleHash.h>

using namespace std;


class World{
    public:
        World(Shader* shader, int render, int seed);
        ~World();
        
        Chunk* getChunk(int x, int z);
        ChunkData* getChunkData(int x, int z);

        GLubyte getBlock(int x, int y, int z);
        bool breakBlock(glm :: ivec3 pos);
        bool placeBlock(glm :: ivec3 pos, GLubyte blockType);

        /**
         * @brief The update thread for the main loop to call which renders the chunks and updates the player position.
         */
        void update(glm :: ivec3 camPos, bool menu);

        static World* world;
        std :: mutex mute;

    private:
        /**
         * @brief The looping update function that runs on a backround thread and handles chunks and chunk data.
         */
        void threadUpdate();

        unordered_map<tuple<int, int>, Chunk*> chunks;
        unordered_map<tuple<int, int>, ChunkData*> chunkData;

        chunkList chunkQueue = chunkList();

        std :: thread updateThread;

        Shader* shader;

        noise :: Fractal fractal;

        bool shouldEnd=false;
        bool isMenu=false;
        bool playerPositionSet = false;

        unsigned int numChunks = 0, numChunksRendered = 0, chunksLoading = 0;
        int lastCamX = -100, lastCamZ = -100;
        int camX_chunk = -101, camZ_chunk = -101;

        int renderDistance = 8;
        unsigned int chunkSize = 16;
};