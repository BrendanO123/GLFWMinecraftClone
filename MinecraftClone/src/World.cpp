#include "World.h"
#include "WorldGen.h"

#include <iostream>

World* World :: world = nullptr;
//costructor: store shader
World :: World(Shader* shader) : shader(shader){
    updateThread = std :: thread(&World :: threadUpdate, this);
}

//destructor
World :: ~World(){
    shouldEnd=true;
    updateThread.join();
    for(auto iterate = chunks.begin(); iterate!=chunks.end();){
        delete iterate->second;
        iterate = chunks.erase(iterate);
    }
    for(auto iterate = chunkData.begin(); iterate!=chunkData.end();){
        delete iterate->second;
        iterate = chunkData.erase(iterate);
    }
}

//handle player movement and gen new chunks
void World :: update(glm :: vec3 camPos, bool menu){

    mute.lock();
    isMenu=menu;

    //get float cam pos into int chunk pos
    camX_chunk = Floor(camPos.x/chunkSize);
    camZ_chunk = Floor(camPos.z/chunkSize);

    //reset attributes
    chunksLoading = numChunks = numChunksRendered = 0;

    //iterate over stored chunks
    queue<Chunk*> renderables;
    for(auto iterate = chunks.begin(); iterate != chunks.end();){
        numChunks++;

        //if the chunk is not ready but stored it must be loading
        if(!(iterate->second->flagByte & ChunkFlags :: HAS_STRUCTURES)){continue;}
        if(!(iterate->second->flagByte & ChunkFlags :: HAS_MESH)){chunksLoading++;}
        else{

            //get location of chunk     
            int chunkX, chunkZ; iterate->second->getPos(chunkX, chunkZ);

            //if it is ready to render
            if(((iterate->second->flagByte & ChunkFlags :: LAND_RENDERABLE) != 0) && ((iterate->second->flagByte & ChunkFlags :: WATER_RENDERABLE) != 0)){
                //if it has moved out of render
                if((abs(chunkX - camX_chunk) > renderDistance || abs(chunkZ - camZ_chunk) > renderDistance)){

                    //remove from chunk map
                    delete iterate->second;
                    iterate = chunks.erase(iterate);
                }
                //if it still needs to be rendered
                else{

                    numChunksRendered++; //inc num rendered

                    iterate->second->render(*shader); //render it
                    renderables.push(iterate->second);

                    //continue
                    ++iterate;
                }
            }
            else{
                numChunksRendered++; //inc num rendered

                iterate->second->render(*shader); //render it
                renderables.push(iterate->second);

                //continue
                ++iterate;
            }
        }
    }
    while(!renderables.empty()){
        Chunk* chunk = renderables.front();
        renderables.pop();
        chunk->renderWater(*shader);
    }
    mute.unlock();
}

//handle player movement and gen new chunks
void World :: threadUpdate(){

    while(!shouldEnd){

        if(!isMenu){ //if stuff is happening
            //if player moves into new chunk
            mute.lock();
            if(camX_chunk != lastCamX || camZ_chunk != lastCamZ){

                //move stored player location
                lastCamX = camX_chunk; lastCamZ = camZ_chunk;

                //loop through chunks in render
                for (int x = camX_chunk - renderDistance; x<= camX_chunk + renderDistance; x++){
                    for (int z = camZ_chunk - renderDistance; z<= camZ_chunk + renderDistance; z++){

                        //if we don't have chunk, add to rendering queue
                        if(chunks.find({x, z}) == chunks.end()){chunkQueue.push({x, z});}
                    }
                }
            }
            mute.unlock();
        }

        mute.lock();
        //if we aren't yet rendering anything and we have things we want to render
        if(chunksLoading == 0 && !chunkQueue.empty()){

            //remove next chunk and add get its location
            glm :: vec2 next = chunkQueue.front();
            chunkQueue.pop();
            mute.unlock();

            //turn chunk location into tuple for lookup
            std :: tuple<int, int> chunkTuple{next.x, next.y};

            mute.lock();

            //if it is not in the chunks map
            if(chunks.find(chunkTuple) == chunks.end()){

                //add to map, therefore init, therefore gen
                mute.unlock();
                Chunk* chunk = new Chunk(0, next);

                mute.lock();
                //center
                if(chunkData.find(chunkTuple)==chunkData.end()){
                    mute.unlock();

                    ChunkData* newChunkData = new ChunkData();
                    WorldGen :: getChunkBasics(next.x, next.y, 16, newChunkData);

                    chunk->data=newChunkData;

                    mute.lock();
                    chunkData[chunkTuple] = newChunkData;
                    mute.unlock();

                }
                else{chunk->data=chunkData.at(chunkTuple); mute.unlock();}

                mute.lock();
                //EAST
                if(chunkData.find(tuple<int,int>(next.x+1, next.y))==chunkData.end()){
                    mute.unlock();

                    ChunkData* newChunkData = new ChunkData();
                    WorldGen :: getChunkBasics(next.x+1, next.y, 16, newChunkData);

                    chunk->right=newChunkData;

                    mute.lock();
                    chunkData[tuple<int,int>(next.x+1, next.y)] = newChunkData;
                    mute.unlock();

                }
                else{chunk->right=chunkData.at(tuple<int,int>(next.x+1, next.y)); mute.unlock();}

                mute.lock();
                //WEST
                if(chunkData.find(tuple<int,int>(next.x-1, next.y))==chunkData.end()){
                    mute.unlock();

                    ChunkData* newChunkData = new ChunkData();
                    WorldGen :: getChunkBasics(next.x-1, next.y, 16, newChunkData);

                    chunk->left=newChunkData;

                    mute.lock();
                    chunkData[tuple<int,int>(next.x-1, next.y)] = newChunkData;
                    mute.unlock();

                }
                else{chunk->left=chunkData.at(tuple<int,int>(next.x-1, next.y)); mute.unlock();}

                mute.lock();
                //NORTH
                if(chunkData.find(tuple<int,int>(next.x, next.y+1))==chunkData.end()){
                    mute.unlock();

                    ChunkData* newChunkData = new ChunkData();
                    WorldGen :: getChunkBasics(next.x, next.y+1, 16, newChunkData);

                    chunk->back=newChunkData;

                    mute.lock();
                    chunkData[tuple<int,int>(next.x, next.y+1)] = newChunkData;
                    mute.unlock();

                }
                else{chunk->back=chunkData.at(tuple<int,int>(next.x, next.y+1)); mute.unlock();}

                mute.lock();
                //SOUTH
                if(chunkData.find(tuple<int,int>(next.x, next.y-1))==chunkData.end()){
                    mute.unlock();

                    ChunkData* newChunkData = new ChunkData();
                    WorldGen :: getChunkBasics(next.x, next.y-1, 16, newChunkData);

                    chunk->front=newChunkData;

                    mute.lock();
                    chunkData[tuple<int,int>(next.x, next.y-1)] = newChunkData;
                    mute.unlock();

                }
                else{chunk->front=chunkData.at(tuple<int,int>(next.x, next.y-1)); mute.unlock();}

                mute.lock();
                chunk->flagByte |= ChunkFlags :: HAS_BASICS;
                if(chunk->flagByte & ChunkFlags :: HAS_STRUCTURES){
                    mute.unlock();

                    chunk->genChunkMesh();

                    mute.lock();
                    cout << "inserted chunk" << endl;
                    chunks[chunkTuple] = chunk;
                    mute.unlock();
                }
                else{
                    mute.unlock();

                    mute.lock();
                    ChunkData* NW;
                    //NW
                    if(chunkData.find(tuple<int,int>(next.x-1, next.y+1))==chunkData.end()){
                        mute.unlock();

                        NW = new ChunkData();
                        WorldGen :: getChunkBasics(next.x-1, next.y+1, 16, NW);

                        mute.lock();
                        chunkData[tuple<int,int>(next.x-1, next.y+1)] = NW;
                        mute.unlock();

                    }
                    else{NW=chunkData.at(tuple<int,int>(next.x-1, next.y+1)); mute.unlock();}

                    mute.lock();
                    ChunkData* NE;
                    //NE
                    if(chunkData.find(tuple<int,int>(next.x+1, next.y+1))==chunkData.end()){
                        mute.unlock();

                        NE = new ChunkData();
                        WorldGen :: getChunkBasics(next.x+1, next.y+1, 16, NE);

                        mute.lock();
                        chunkData[tuple<int,int>(next.x+1, next.y+1)] = NE;
                        mute.unlock();

                    }
                    else{NE=chunkData.at(tuple<int,int>(next.x+1, next.y+1)); mute.unlock();}

                    mute.lock();
                    ChunkData* SW;
                    //SW
                    if(chunkData.find(tuple<int,int>(next.x-1, next.y-1))==chunkData.end()){
                        mute.unlock();

                        SW = new ChunkData();
                        WorldGen :: getChunkBasics(next.x-1, next.y-1, 16, SW);

                        mute.lock();
                        chunkData[tuple<int,int>(next.x-1, next.y-1)] = SW;
                        mute.unlock();

                    }
                    else{SW=chunkData.at(tuple<int,int>(next.x-1, next.y-1)); mute.unlock();}

                    mute.lock();
                    ChunkData* SE;
                    //SE
                    if(chunkData.find(tuple<int,int>(next.x+1, next.y-1))==chunkData.end()){
                        mute.unlock();

                        SE = new ChunkData();
                        WorldGen :: getChunkBasics(next.x+1, next.y-1, 16, SE);

                        mute.lock();
                        chunkData[tuple<int,int>(next.x+1, next.y-1)] = SE;
                        mute.unlock();

                    }
                    else{SE=chunkData.at(tuple<int,int>(next.x+1, next.y-1)); mute.unlock();}

                    WorldGen :: resolveStructures(chunk->data, NW, chunk->back, NE, chunk->left, chunk->right, SW, chunk->front, SE);
                    chunk->genChunkMesh();

                    mute.lock();
                    chunk->flagByte |= ChunkFlags :: HAS_STRUCTURES;
                    chunks[chunkTuple] = chunk;
                    mute.unlock();
                }
            }
        }
        else{
            mute.unlock();
            if(!isMenu){std::this_thread::sleep_for(std::chrono::milliseconds(1000));}
            else{std::this_thread::sleep_for(std::chrono::milliseconds(2000));}
        }

        if(!isMenu){//if stuff is happening
            mute.lock();
            for (auto iterate = chunkData.begin(); iterate != chunkData.end();)
            {
                glm :: ivec2 chunkPos = iterate->second->pos;

                if (
                    (chunks.find(tuple<int, int>(chunkPos.x, chunkPos.y)) == chunks.end()) &&


                    ((chunks.find(tuple<int, int>(chunkPos.x+1, chunkPos.y+1)) == chunks.end()) || 
                        ((chunks.at(tuple<int, int>(chunkPos.x+1, chunkPos.y+1))->flagByte & ChunkFlags :: HAS_STRUCTURES) != 0)) &&
                        
                    ((chunks.find(tuple<int, int>(chunkPos.x+1, chunkPos.y)) == chunks.end()) || 
                        ((chunks.at(tuple<int, int>(chunkPos.x+1, chunkPos.y))->flagByte & ChunkFlags :: HAS_MESH) != 0)) &&

                    ((chunks.find(tuple<int, int>(chunkPos.x+1, chunkPos.y-1)) == chunks.end()) || 
                        ((chunks.at(tuple<int, int>(chunkPos.x+1, chunkPos.y-1))->flagByte & ChunkFlags :: HAS_STRUCTURES) != 0)) &&


                    ((chunks.find(tuple<int, int>(chunkPos.x, chunkPos.y+1)) == chunks.end()) || 
                        ((chunks.at(tuple<int, int>(chunkPos.x, chunkPos.y+1))->flagByte & ChunkFlags :: HAS_MESH) != 0)) &&

                    ((chunks.find(tuple<int, int>(chunkPos.x, chunkPos.y-1)) == chunks.end()) || 
                        ((chunks.at(tuple<int, int>(chunkPos.x, chunkPos.y-1))->flagByte & ChunkFlags :: HAS_MESH) != 0)) &&


                    ((chunks.find(tuple<int, int>(chunkPos.x-1, chunkPos.y+1)) == chunks.end()) || 
                        ((chunks.at(tuple<int, int>(chunkPos.x-1, chunkPos.y+1))->flagByte & ChunkFlags :: HAS_STRUCTURES) != 0)) &&
                        
                    ((chunks.find(tuple<int, int>(chunkPos.x-1, chunkPos.y)) == chunks.end()) || 
                        ((chunks.at(tuple<int, int>(chunkPos.x-1, chunkPos.y))->flagByte & ChunkFlags :: HAS_MESH) != 0)) &&
                    
                    ((chunks.find(tuple<int, int>(chunkPos.x-1, chunkPos.y-1)) == chunks.end()) || 
                        ((chunks.at(tuple<int, int>(chunkPos.x-1, chunkPos.y-1))->flagByte & ChunkFlags :: HAS_STRUCTURES) != 0))
                )
                {
                    delete chunkData.at(iterate->first);
                    iterate = chunkData.erase(iterate);
                }
                else{iterate++;}
            }
            mute.unlock();
        }
    }
}

//get chunk data (vector<Layer> in chunk.data) by chunk cords
ChunkData* World :: getChunkData(int x, int z){

    tuple<int, int> chunkTuple{x, z};

    if(chunks.find(chunkTuple) == chunks.end()){

        //is not in map
        return nullptr;
    }

    //return chunk data
    return chunkData.at(chunkTuple);
}

//get chunk object from cords
Chunk* World :: getChunk(int x, int z){

    //make cords into tuple for lookup
    tuple<int, int> chunkTuple{x, z};

    //check to see if it is in the chunks map
    if(chunkData.find(chunkTuple) == chunkData.end()){

        //is not in map
        return nullptr;
    }
    else{

        //is in map, return chunk
        return chunks.at(chunkTuple);
    }
}