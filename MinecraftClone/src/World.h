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
#include "Player.h"
#include "FileManager.h"

#include <ScuffedMinecraft/TupleHash.h>

using namespace std;


class World{
    public:

        //keep destructer public
        ~World();

        //init to make universal instance of world, access instance, close instance
        static World* init(Shader* shader, int render, int seed, string saveFileName, Player* player){
            if(getInstance()==nullptr){
                world = (new World(shader, render, seed, saveFileName, player));
            }
            return getInstance();
        }
        static World* getInstance(){return world;}
        static bool closeInstance(){
            if(world == nullptr){return false;}
            delete world; return true;
        }

        //delete copy constructors
        World(const World&) = delete;
        World& operator=(const World&) = delete;
        
        //notify saveFileManager, needs to be notified and scheduled for synchronization insetad of just being saved
        void setShouldSave(bool shouldSave = true){saveNeeded = shouldSave;}

        //get block or chunk data
        Chunk* getChunk(int x, int z);
        ChunkData* getChunkData(int x, int z);
        GLubyte getBlock(int x, int y, int z);

        //modify blocks
        bool breakBlock(glm :: ivec3 pos);
        bool placeBlock(glm :: ivec3 pos, GLubyte blockType);

        /**
         * @brief The update thread for the main loop to call which renders the chunks and updates the player position.
         */
        void update(glm :: ivec3 camPos, bool menu, Player* player);

        std :: mutex mute;

    private:

        //private universal instance and therefore private constructor
        static World* world;
        World(Shader* shader, int render, int seed, string saveFileName, Player* player);

        /**
         * @brief The looping update function that runs on a backround thread and handles chunks and chunk data.
         */
        void threadUpdate();
        bool save(Player* player);

        unordered_map<tuple<int, int>, Chunk*> chunks;
        unordered_map<tuple<int, int>, ChunkData*> chunkData;

        chunkList chunkQueue = chunkList();
        queue<tuple<int, int>> modifiedChunks;

        std :: thread updateThread;

        Shader* shader;
        noise :: Fractal* fractal;
        FileManager* file;

        bool shouldEnd=false;
        bool isMenu=false;
        bool playerPositionSet = false;
        bool saveNeeded = false;

        constexpr static const std::chrono::duration normSleepMillis = std::chrono::milliseconds(100);
        constexpr static const std::chrono::duration menuSleepMillis = std::chrono::milliseconds(1000);

        unsigned int numChunks = 0, numChunksRendered = 0, chunksLoading = 0;
        int lastCamX = -100, lastCamZ = -100;
        int camX_chunk = -101, camZ_chunk = -101;

        int renderDistance = 8;
        constexpr static const int modifiedChunkStoreDistance = 10;
        unsigned int chunkSize = 16;
        
        int seed;
};