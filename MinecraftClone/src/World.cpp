#include "World.h"

#include <iostream>

World* World :: world = nullptr;
//costructor: store shader
World :: World(Shader* shader){
    //store shader
    this->shader = shader;
}

//destructor
World :: ~World(){}

//get chunk data (vector<Layer> in chunk.data) by chunk cords
vector<Layer> World :: getChunkData(int x, int z){

    //get chunk from other method
    Chunk* chunk = getChunk(x, z);

    if(chunk!=nullptr){return chunk->data;} //return data
    else{return vector<Layer>{};} //nullptr
}

//get chunk object from cords
Chunk* World :: getChunk(int x, int z){

    //make cords into tuple for lookup
    tuple<int, int> chunkTuple{x, z};

    //check to see if it is in the chunks map
    if(chunks.find(chunkTuple) == chunks.end()){

        //is not in map
        return nullptr;
    }
    else{

        //is in map, return chunk
        return &chunks.at(chunkTuple);
    }
}

//handle player movement and gen new chunks
void World :: update(glm :: vec3 camPos){

    //get float cam pos into int chunk pos
    int camX_chunk = Floor(camPos.x/chunkSize);
    int camZ_chunk = Floor(camPos.z/chunkSize);

    //if player moves into new chunk
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

    //if we aren't yet rendering anything and we have things we want to render
    if(chunksLoading == 0 && !chunkQueue.empty()){

        //remove next chunk and add get its location
        glm :: vec2 next = chunkQueue.front();
        chunkQueue.pop();

        //turn chunk location into tuple for lookup
        std :: tuple<int, int>chunkTuple{next.x, next.y};

        //if it is not in the chunks map
        if(chunks.find(chunkTuple) == chunks.end()){

            //add to map, therefore init, therefore gen
            chunks.try_emplace(chunkTuple, 0, next);
        }
    }

    //reset attributes
    chunksLoading = numChunks = numChunksRendered = 0;

    //iterate over stored chunks
    for(auto iterate = chunks.begin(); iterate != chunks.end();){
        numChunks++;

        //if the chunk is not ready but stored it must be loading
        if(!(iterate->second.flagByte & ChunkFlags :: GENERATED)){chunksLoading++;}
        else{

            //get location of chunk     
            int chunkX, chunkZ; iterate->second.getPos(chunkX, chunkZ);

            //if it has moved out of render
            if(iterate->second.flagByte & ChunkFlags :: READY){
                if((abs(chunkX - camX_chunk) > renderDistance || abs(chunkZ - camZ_chunk) > renderDistance)){

                    //remove from chunk map
                    iterate = chunks.erase(iterate);
                    if (iterate == chunks.end()){break;} //check if this means we have checked everything
                }
                //if it still needs to be rendered
                else{

                    numChunksRendered++; //inc num rendered
                    iterate->second.render(*shader); //render it

                    //continue
                    ++iterate;
                }
            }
            else{
                numChunksRendered++; //inc num rendered
                iterate->second.render(*shader); //render it

                //continue
                ++iterate;
            }
        }
    }
}