#include "World.h"

#include <iostream>

#include "WorldGen.h"

World* World :: world = nullptr;
//costructor: store shader
World :: World(Shader* shader, int render, int Seed, string name, Player* player) : shader(shader), renderDistance(render){

    glm :: ivec3 playerPositionI = glm :: ivec3(8, 135, 8); glm :: vec3 playerPositionF = glm :: vec3(0);
    glm :: vec2 playerRotation = glm :: vec2(0.f, -89.9f);

    file = new FileManager(name, Seed, playerPositionI, playerPositionF, playerRotation);

    player->setPosition(playerPositionI, playerPositionF);
    player->setRotation(playerRotation);

    seed = Seed;
    srand(seed); 
    int i = (rand() & 15) + 1;
    for(int j = 0; j<i; j++){rand();}

    fractal = new noise :: Fractal(rand());

    fractal->settings.settings[noise :: TREE_MAP].frequency = 32 / 1.09617844793f;
    fractal->settings.settings[noise :: TREE_MAP].octaves = 2;
    fractal->settings.settings[noise :: TREE_MAP].fractalType = noise :: FBM;
    fractal->noise.calcFracBounding(fractal->settings.settings[noise :: TREE_MAP]);

    fractal->settings.settings[noise :: GRASS_MAP].frequency = 22/1.09617844793f;
    fractal->settings.settings[noise :: FLOWER_NOISE].frequency = 1.09617844793f / 32.f;
    fractal->settings.settings[noise :: FLOWER_NOISE].fractalType = noise :: NONE;

    fractal->settings.settings[noise :: CONTINENTAL_MAP].includePartials = true;
    fractal->settings.settings[noise :: CONTINENTAL_MAP].fractalType = noise :: NONE;
    fractal->settings.settings[noise :: CONTINENTAL_MAP].frequency = 2.5f/1000;

    fractal->settings.settings[noise :: EROSION_MAP].frequency = 4.f/1000;
    fractal->settings.settings[noise :: EROSION_MAP].includePartials = true;
    /*fractal->settings.settings[noise :: EROSION_MAP].octaves = 3;
    fractal->settings.settings[noise :: EROSION_MAP].gain = 0.5f;
    //fractal->noise.calcFracBounding(fractal->settings.settings[noise :: EROSION_MAP]);*/

    fractal->settings.settings[noise :: HIGH_NOISE].octaves = 5;
    fractal->settings.settings[noise :: HIGH_NOISE].frequency = fractal->settings.settings[noise :: CONTINENTAL_MAP].frequency * fractal->settings.settings[noise :: HIGH_NOISE].lacunarity;
    fractal->noise.calcFracBounding_HL_Noise(fractal->settings.settings[noise :: HIGH_NOISE]);

    fractal->settings.settings[noise :: LOW_NOISE].octaves = 2;
    fractal->settings.settings[noise :: LOW_NOISE].gain = 0.25f;
    fractal->settings.settings[noise :: LOW_NOISE].lacunarity = 1.5f;
    fractal->settings.settings[noise :: LOW_NOISE].frequency = fractal->settings.settings[noise :: CONTINENTAL_MAP].frequency * fractal->settings.settings[noise :: LOW_NOISE].lacunarity;
    fractal->noise.calcFracBounding_HL_Noise(fractal->settings.settings[noise :: LOW_NOISE]);
    fractal->settings.settings[noise :: LOW_NOISE].fractalBounding *= 1.f / 8;

    updateThread = std :: thread(&World :: threadUpdate, this);

    /*float value;
    float stdev = 0.f, mean = 0.f;
    int scale = 5000;
    for(int x = 0; x<scale; x++){
        for(int y = 0; y<scale; y++){
            value = fractal->noise.SinglePerlin(seed, 1.09617844793f / 30 * x, 1.09617844793f / 30 * y);
            mean += value;
        }
    }
    mean /= (scale * scale);
    for(int x = 0; x<scale; x++){
        for(int y = 0; y<scale; y++){
            value = fractal->noise.SinglePerlin(seed, 1.09617844793f / 30 * x, 1.09617844793f / 30 * y) - mean;
            stdev += value * value;
        }
    }
    stdev /= (scale * scale);
    std :: cout << "stdev: " << sqrt(stdev) << std :: endl;
     std :: cout << "mean: " << mean << std :: endl;*/
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
    delete file;
    delete fractal;
}

//handle player movement and gen new chunks
void World :: update(glm :: ivec3 camPos, bool menu, Player* player){

    mute.lock();
    isMenu=menu;

    //get float cam pos into int chunk pos
    camX_chunk = floor(camPos.x/float(chunkSize));
    camZ_chunk = floor(camPos.z/float(chunkSize));
    playerPositionSet = true;

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
            if(chunkData.find(tuple<int, int>(chunkX, chunkZ)) == chunkData.end() && chunks.find(tuple<int, int>(chunkX, chunkZ)) != chunks.end()){
                std :: cout << "Found Missing ChunkData at: (" << chunkX << ", " << chunkZ << ")" << std :: endl;
            }

            //if it is ready to render
            if(iterate->second->flagByte & ChunkFlags :: RENDERABLE){
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
    mute.lock();
    player->resolveClicks();
    if(saveNeeded){save(player); saveNeeded = false;}
    mute.unlock();
}

bool World :: save(Player* player){
    while(!modifiedChunks.empty()){
        tuple<int, int> i = modifiedChunks.front();
        modifiedChunks.pop();
        if(chunkData.find(i) != chunkData.end()){
            ChunkData* data = chunkData.at(i);
            if(!data->fileStored){
                data->fileStored = true;
                if(chunks.find(i) != chunks.end()){chunks.at(i)->flagByte |= ChunkFlags :: FILE_STORED;}
                file->save(chunkData.at(i));
            }
        }
    }
    return file->save(seed, player->getPosition(), player->getFPosition(), player->getRotation());
}

//handle player movement and gen new chunks
void World :: threadUpdate(){

    while(!shouldEnd){

        if(!isMenu){ //if stuff is happening

            //if player moves into new chunk
            mute.lock();
            if(playerPositionSet && (camX_chunk != lastCamX || camZ_chunk != lastCamZ)){

                //move stored player location
                lastCamX = camX_chunk; lastCamZ = camZ_chunk;

                //loop through chunks in render
                for (int x = camX_chunk - renderDistance; x<= camX_chunk + renderDistance; x++){
                    for (int z = camZ_chunk - renderDistance; z<= camZ_chunk + renderDistance; z++){

                        //if we don't have chunk, add to rendering queue
                        if(chunks.find({x, z}) == chunks.end()){
                            chunkQueue.pushBack(x, z);
                        }
                    }
                }
            }
            mute.unlock();
        }

        mute.lock();
        //if we aren't yet rendering anything and we have things we want to render
        if(!chunkQueue.empty()){

            //remove next chunk and add get its location
            glm :: ivec2 next = chunkQueue.popFront();
            mute.unlock();

            //turn chunk location into tuple for lookup
            std :: tuple<int, int> chunkTuple{next.x, next.y};

            mute.lock();

            //if it is not in the chunks map
            if(chunks.find(chunkTuple) != chunks.end()){
                Chunk* chunk = chunks.at(chunkTuple);
                if(chunk->flagByte & ChunkFlags :: MODIFIED){

                    if(chunkData.find(tuple<int, int>(next.x, next.y))!=chunkData.end()){chunk->data=chunkData.at(tuple<int,int>(next.x, next.y));}
                    if(chunkData.find(tuple<int, int>(next.x+1, next.y))!=chunkData.end()){chunk->right=chunkData.at(tuple<int,int>(next.x+1, next.y));}
                    if(chunkData.find(tuple<int, int>(next.x-1, next.y))!=chunkData.end()){chunk->left=chunkData.at(tuple<int,int>(next.x-1, next.y));}
                    if(chunkData.find(tuple<int, int>(next.x, next.y+1))!=chunkData.end()){chunk->front=chunkData.at(tuple<int,int>(next.x, next.y+1));}
                    if(chunkData.find(tuple<int, int>(next.x, next.y-1))!=chunkData.end()){chunk->back=chunkData.at(tuple<int,int>(next.x, next.y-1));}
                    
                    chunk->genChunkMesh();

                    chunk->flagByte |= ChunkFlags :: HAS_MESH;
                    chunk->flagByte = chunk->flagByte & ~(ChunkFlags :: MODIFIED | ChunkFlags :: RENDERABLE);
                    chunks[chunkTuple] = chunk;
                    mute.unlock();
                }
                else{mute.unlock();}
            }
            else{
                //add to map, therefore init, therefore gen
                mute.unlock();
                Chunk* chunk = new Chunk(0, next);

                mute.lock();
                //center
                if(chunkData.find(chunkTuple)==chunkData.end()){
                    ChunkData* newChunkData;
                    if(file->hasFile(next.x, next.y)){
                        newChunkData = file->load(next.x, next.y);
                        chunk->data=newChunkData;
                        chunk->flagByte |= (ChunkFlags :: FILE_STORED | ChunkFlags :: CONTAINS_BUILDS);
                        mute.unlock();
                    }
                    else{
                        mute.unlock();
                        

                        newChunkData = new ChunkData();
                        WorldGen :: getChunkBasics(next.x, next.y, 16, newChunkData, fractal);

                        chunk->data=newChunkData;
                    }
                    mute.lock();
                    chunkData[chunkTuple] = newChunkData;
                    mute.unlock();

                }
                else{chunk->data=chunkData.at(chunkTuple); if(chunk->data->hasBuilds){chunk->flagByte |= ChunkFlags :: CONTAINS_BUILDS;} mute.unlock();}

                mute.lock();
                //EAST
                if(chunkData.find(tuple<int,int>(next.x+1, next.y))==chunkData.end()){
                    ChunkData* newChunkData;
                    if(file->hasFile(next.x+1, next.y)){
                        newChunkData = file->load(next.x+1, next.y);
                        chunk->right=newChunkData;
                        mute.unlock();
                    }
                    else{
                        mute.unlock();
                        

                        newChunkData = new ChunkData();
                        WorldGen :: getChunkBasics(next.x+1, next.y, 16, newChunkData, fractal);

                        chunk->right=newChunkData;
                    }

                    mute.lock();
                    chunkData[tuple<int,int>(next.x+1, next.y)] = newChunkData;
                    mute.unlock();

                }
                else{chunk->right=chunkData.at(tuple<int,int>(next.x+1, next.y)); mute.unlock();}

                mute.lock();
                //WEST
                if(chunkData.find(tuple<int,int>(next.x-1, next.y))==chunkData.end()){
                    ChunkData* newChunkData;
                    if(file->hasFile(next.x-1, next.y)){
                        newChunkData = file->load(next.x-1, next.y);
                        chunk->left=newChunkData;
                        mute.unlock();
                    }
                    else{
                        mute.unlock();
                        

                        newChunkData = new ChunkData();
                        WorldGen :: getChunkBasics(next.x-1, next.y, 16, newChunkData, fractal);

                        chunk->left=newChunkData;
                    }

                    mute.lock();
                    chunkData[tuple<int,int>(next.x-1, next.y)] = newChunkData;
                    mute.unlock();

                }
                else{chunk->left=chunkData.at(tuple<int,int>(next.x-1, next.y)); mute.unlock();}

                mute.lock();
                //NORTH
                if(chunkData.find(tuple<int,int>(next.x, next.y+1))==chunkData.end()){
                    ChunkData* newChunkData;
                    if(file->hasFile(next.x, next.y+1)){
                        newChunkData = file->load(next.x, next.y+1);
                        chunk->front=newChunkData;
                        mute.unlock();
                    }
                    else{
                        mute.unlock();
                        

                        newChunkData = new ChunkData();
                        WorldGen :: getChunkBasics(next.x, next.y+1, 16, newChunkData, fractal);

                        chunk->front=newChunkData;
                    }

                    mute.lock();
                    chunkData[tuple<int,int>(next.x, next.y+1)] = newChunkData;
                    mute.unlock();

                }
                else{chunk->front=chunkData.at(tuple<int,int>(next.x, next.y+1)); mute.unlock();}

                mute.lock();
                //SOUTH
                if(chunkData.find(tuple<int,int>(next.x, next.y-1))==chunkData.end()){
                    ChunkData* newChunkData;
                    if(file->hasFile(next.x, next.y-1)){
                        newChunkData = file->load(next.x, next.y-1);
                        chunk->back=newChunkData;
                        mute.unlock();
                    }
                    else{
                        mute.unlock();
                        

                        newChunkData = new ChunkData();
                        WorldGen :: getChunkBasics(next.x, next.y-1, 16, newChunkData, fractal);

                        chunk->back=newChunkData;
                    }

                    mute.lock();
                    chunkData[tuple<int,int>(next.x, next.y-1)] = newChunkData;
                    mute.unlock();

                }
                else{chunk->back=chunkData.at(tuple<int,int>(next.x, next.y-1)); mute.unlock();}

                mute.lock();
                chunk->flagByte |= ChunkFlags :: HAS_BASICS;
                if(chunk->flagByte & ChunkFlags :: HAS_STRUCTURES){
                    mute.unlock();

                    chunk->genChunkMesh();

                    mute.lock();
                    chunk->flagByte |= ChunkFlags :: HAS_MESH;
                    chunks[chunkTuple] = chunk;
                    mute.unlock();
                }
                else{
                    ChunkData* NW;
                    //NW
                    if(chunkData.find(tuple<int,int>(next.x-1, next.y+1))==chunkData.end()){
                        if(file->hasFile(next.x-1, next.y+1)){
                            NW = file->load(next.x-1, next.y+1);
                            mute.unlock();
                        }
                        else{
                            mute.unlock();
                            

                            NW = new ChunkData();
                            WorldGen :: getChunkBasics(next.x-1, next.y+1, 16, NW, fractal);
                        }

                        mute.lock();
                        chunkData[tuple<int,int>(next.x-1, next.y+1)] = NW;
                        mute.unlock();

                    }
                    else{NW=chunkData.at(tuple<int,int>(next.x-1, next.y+1)); mute.unlock();}

                    mute.lock();
                    ChunkData* NE;
                    //NE
                    if(chunkData.find(tuple<int,int>(next.x+1, next.y+1))==chunkData.end()){
                        if(file->hasFile(next.x+1, next.y+1)){
                            NE = file->load(next.x+1, next.y+1);
                            mute.unlock();
                        }
                        else{
                            mute.unlock();
                            

                            NE = new ChunkData();
                            WorldGen :: getChunkBasics(next.x+1, next.y+1, 16, NE, fractal);
                        }

                        mute.lock();
                        chunkData[tuple<int,int>(next.x+1, next.y+1)] = NE;
                        mute.unlock();

                    }
                    else{NE=chunkData.at(tuple<int,int>(next.x+1, next.y+1)); mute.unlock();}

                    mute.lock();
                    ChunkData* SW;
                    //SW
                    if(chunkData.find(tuple<int,int>(next.x-1, next.y-1))==chunkData.end()){
                        if(file->hasFile(next.x-1, next.y-1)){
                            SW = file->load(next.x-1, next.y-1);
                            mute.unlock();
                        }
                        else{
                            mute.unlock();
                            

                            SW = new ChunkData();
                            WorldGen :: getChunkBasics(next.x-1, next.y-1, 16, SW, fractal);
                        }

                        mute.lock();
                        chunkData[tuple<int,int>(next.x-1, next.y-1)] = SW;
                        mute.unlock();

                    }
                    else{SW=chunkData.at(tuple<int,int>(next.x-1, next.y-1)); mute.unlock();}

                    mute.lock();
                    ChunkData* SE;
                    //SE
                    if(chunkData.find(tuple<int,int>(next.x+1, next.y-1))==chunkData.end()){
                        if(file->hasFile(next.x+1, next.y-1)){
                            SE = file->load(next.x+1, next.y-1);
                            mute.unlock();
                        }
                        else{
                            mute.unlock();
                            

                            SE = new ChunkData();
                            WorldGen :: getChunkBasics(next.x+1, next.y-1, 16, SE, fractal);
                        }

                        mute.lock();
                        chunkData[tuple<int,int>(next.x+1, next.y-1)] = SE;
                        mute.unlock();

                    }
                    else{SE=chunkData.at(tuple<int,int>(next.x+1, next.y-1)); mute.unlock();}

                    mute.lock();
                    WorldGen :: resolveStructures(chunk->data, NW, chunk->back, NE, chunk->left, chunk->right, SW, chunk->front, SE);
                    chunk->flagByte |= ChunkFlags :: HAS_STRUCTURES;
                    mute.unlock();

                    chunk->genChunkMesh();

                    mute.lock();
                    chunk->flagByte |= ChunkFlags :: HAS_MESH;
                    chunks[chunkTuple] = chunk;
                    mute.unlock();
                }
            }
        }
        else{
            /*using namespace std :: chrono;
            {
            mute.unlock();
            if(!isMenu){
                bool urgent = false;
                std :: chrono :: time_point start = chrono::steady_clock::now();
                while(chrono::steady_clock::now() - start < chunkLoadSleepMillis){
                    std::this_thread::sleep_for(std::chrono::milliseconds(clickSleepMillis));
                    mute.lock();
                    urgent = chunkQueue.hasUrgent();
                    mute.unlock(); 
                    if(urgent){break;}
                }
            }
            else{std::this_thread::sleep_for(std::chrono::milliseconds(2000));} //effects the cpu time taken up as a background task 
                //TODO: (change to a real function of time since last input eventually)
            };*/
            mute.unlock();
            if(!isMenu){std::this_thread::sleep_for(std::chrono::milliseconds(normSleepMillis));}
            else{std::this_thread::sleep_for(std::chrono::milliseconds(menuSleepMillis));}
        }

        if(!isMenu){//if stuff is happening
            mute.lock();
            for (auto iterate = chunkData.begin(); iterate != chunkData.end();)
            {
                //glm :: ivec2 chunkPos = iterate->second->pos;
                glm :: ivec2 chunkPos = glm :: ivec2(iterate->second->xPos, iterate->second->zPos);
                
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
                    if(iterate->second->hasBuilds){
                        //if(playerPositionSet && (abs(chunkPos.x - camX_chunk) > modifiedChunkStoreDistance || abs(chunkPos.y - camZ_chunk) > modifiedChunkStoreDistance)){

                            if(!iterate->second->fileStored){file->save(iterate->second);}
                            delete chunkData.at(iterate->first);
                            iterate = chunkData.erase(iterate);
                        //}
                    }
                    else{
                        //if(playerPositionSet && (abs(chunkPos.x - camX_chunk) > renderDistance || abs(chunkPos.y - camZ_chunk) > renderDistance)){
                            delete chunkData.at(iterate->first);
                            iterate = chunkData.erase(iterate);
                        //}
                    }
                }
                else{iterate++;}
            }
            mute.unlock();
        }
    }
}

GLubyte World :: getBlock(int x, int y, int z){
    //TODO LOD SYSTEM

    ChunkData* data = getChunkData(floor(x / float(chunkSize)), floor((z-1) / float(chunkSize))+1);
    if(data == nullptr){return Blocks :: AIR;}

    //does not work if chunk size changes
    GLubyte block = data->findBlock(((-z & 15) + ((x & 15)<<4) & 255), y);
    return block;
}
bool World :: breakBlock(glm :: ivec3 pos){
    Chunk* chunk = getChunk(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1);
    if(chunk == nullptr){return false;}
    if(((chunk->flagByte & ChunkFlags :: HAS_STRUCTURES)==0)){return false;}

    //does not work if chunk size changes
    //TODO update adjacent chunk if on border
    Layer* layer = chunk->data->getLayer(pos.y);
    if(layer == nullptr){return false;}

    layer->data[((-pos.z & 15) + ((pos.x & 15)<<4) & 255)] = Blocks :: AIR;

    if((pos.x & 15) == 15){
        Chunk* chunkXUp = getChunk(floor(pos.x / float(chunkSize))+1, floor((pos.z-1) / float(chunkSize))+1);
        if(chunkXUp != nullptr){
            if(chunkXUp->flagByte & ChunkFlags :: HAS_MESH){
                chunkXUp->flagByte |= ChunkFlags :: MODIFIED;
                //chunkXUp -> left = chunk -> data;
                chunks[tuple<int, int>(floor(pos.x / float(chunkSize))+1, floor((pos.z-1) / float(chunkSize))+1)] = chunkXUp;
                chunkQueue.pushFront(floor(pos.x / float(chunkSize))+1, floor((pos.z-1) / float(chunkSize))+1);
                //std :: cout << "Pushed Secondary Chunk" << std :: endl;
            }
        }
    }
    else if ((pos.x & 15) == 0){
        Chunk* chunkXDown = getChunk(floor(pos.x / float(chunkSize))-1, floor((pos.z-1) / float(chunkSize))+1);
        if(chunkXDown != nullptr){
            if(chunkXDown->flagByte & ChunkFlags :: HAS_MESH){
                chunkXDown->flagByte |= ChunkFlags :: MODIFIED;
                //chunkXDown -> right = chunk -> data;
                chunks[tuple<int, int>(floor(pos.x / float(chunkSize))-1, floor((pos.z-1) / float(chunkSize))+1)] = chunkXDown;
                chunkQueue.pushFront(floor(pos.x / float(chunkSize))-1, floor((pos.z-1) / float(chunkSize))+1);
                //std :: cout << "Pushed Secondary Chunk" << std :: endl;
            }
        }
    }
    if((-pos.z & 15) == 15){
        Chunk* chunkZUp = getChunk(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize)));
        if(chunkZUp != nullptr){
            if(chunkZUp->flagByte & ChunkFlags :: HAS_MESH){
                chunkZUp->flagByte |= ChunkFlags :: MODIFIED;
                //chunkZUp -> front = chunk -> data;
                chunks[tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize)))] = chunkZUp;
                chunkQueue.pushFront(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize)));
                //std :: cout << "Pushed Secondary Chunk" << std :: endl;
            }
        }
    }
    else if((-pos.z & 15) == 0){
        Chunk* chunkZDown = getChunk(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+2);
        if(chunkZDown != nullptr){
            if(chunkZDown->flagByte & ChunkFlags :: HAS_MESH){
                chunkZDown->flagByte |= ChunkFlags :: MODIFIED;
                //chunkZDown -> back = chunk -> data;
                chunks[tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+2)] = chunkZDown;
                chunkQueue.pushFront(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+2);
                //std :: cout << "Pushed Secondary Chunk" << std :: endl;
            }
        }
    }
    

    if(chunk != nullptr){

        /*if(chunkData.find(tuple<int, int>(floor(pos.x / float(chunkSize))+1, floor((pos.z-1) / float(chunkSize))+1)) != chunkData.end()){
            chunk->right = chunkData.at(tuple<int, int>(floor(pos.x / float(chunkSize))+1, floor((pos.z-1) / float(chunkSize))+1));
            //std :: cout << "Updated Chunk Side: Right" << std :: endl;
        }
        if(chunkData.find(tuple<int, int>(floor(pos.x / float(chunkSize))-1, floor((pos.z-1) / float(chunkSize))+1)) != chunkData.end()){
            chunk->left = chunkData.at(tuple<int, int>(floor(pos.x / float(chunkSize))-1, floor((pos.z-1) / float(chunkSize))+1));
            //std :: cout << "Updated Chunk Side: Left" << std :: endl;
        }
        if(chunkData.find(tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+2)) != chunkData.end()){
            chunk->front = chunkData.at(tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+2));
            //std :: cout << "Updated Chunk Side: Front" << std :: endl;
        }
        if(chunkData.find(tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize)))) != chunkData.end()){
            chunk->back = chunkData.at(tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))));
            //std :: cout << "Updated Chunk Side: Back" << std :: endl;
        }*/

        chunk->flagByte |= (ChunkFlags :: MODIFIED | ChunkFlags :: CONTAINS_BUILDS);
        chunk->flagByte &= ~(ChunkFlags :: FILE_STORED);
        chunk->data->fileStored = false; chunk->data->hasBuilds = true;
        chunks[tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1)] = chunk;
        chunkData[tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1)] = chunk->data;
        chunkQueue.pushFront(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1);
        modifiedChunks.push(tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1));
        //std :: cout << "Pushed Main Chunk" << std :: endl;
        return true;
    }
    else{return false;}
}

bool World :: placeBlock(glm :: ivec3 pos, GLubyte blockType){
    Chunk* chunk = getChunk(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1);
    if(chunk == nullptr){return false;}
    if(((chunk->flagByte & ChunkFlags :: HAS_STRUCTURES)==0)){return false;}

    //does not work if chunk size changes
    Layer* layer = &(chunk->data->data.at(chunk->data->safeLayerFetch(pos.y)));
    if(layer->data[((-pos.z & 15) + ((pos.x & 15)<<4) & 255)]){return false;} //return false unless placing in air

    layer->data[((-pos.z & 15) + ((pos.x & 15)<<4) & 255)] = blockType;

    if(chunk != nullptr){
        chunk->flagByte |= (ChunkFlags :: MODIFIED | ChunkFlags :: CONTAINS_BUILDS);
        chunk->flagByte &= ~(ChunkFlags :: FILE_STORED);
        chunk->data->fileStored = false; chunk->data->hasBuilds = true;
        chunks[tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1)] = chunk;
        chunkData[tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1)] = chunk->data;
        chunkQueue.pushFront(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1);
        modifiedChunks.push(tuple<int, int>(floor(pos.x / float(chunkSize)), floor((pos.z-1) / float(chunkSize))+1));
        return true;
    }
    else{return false;}
}

//get chunk data (vector<Layer> in chunk.data) by chunk cords
ChunkData* World :: getChunkData(int x, int z){

    tuple<int, int> chunkTuple{x, z};

    if(chunkData.find(chunkTuple) != chunkData.end()){

        //is not in map
        return chunkData.at(chunkTuple); return nullptr;
    }

    //return chunk data
    return nullptr;
}

//get chunk object from cords
Chunk* World :: getChunk(int x, int z){

    //make cords into tuple for lookup
    tuple<int, int> chunkTuple{x, z};

    //check to see if it is in the chunks map
    if(chunkData.find(chunkTuple) != chunkData.end()){

        //is not in map
        return chunks.at(chunkTuple);
    }
    else{

        //is in map, return chunk
        return nullptr;
    }
}