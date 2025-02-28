#include "ChunkCleaner.h"

using namespace std;

void Cleaner :: cleanChunk(string saveFileName){
    ifstream file1(("MinecraftClone/saves/" + saveFileName + "/main").c_str());
    if(file1.is_open()){file1.close(); //exists

        int seed = 0; glm :: ivec3 ipos = glm :: ivec3(0); glm :: vec3 fpos = glm :: vec3(0); glm :: vec2 rot = glm :: vec2(0);
        FileManager* fileManager = new FileManager(saveFileName, seed, ipos, fpos, rot);
        noise :: Fractal* fractal = new noise :: Fractal(seed);
        GenerationSettings :: getSettings(fractal);


        for(const auto & directory : std::filesystem::directory_iterator(("MinecraftClone/saves/" + saveFileName + "/"))){ //regions

            if(directory.is_directory()){

                for(const auto & entry : std::filesystem::directory_iterator(directory)){ //chunks
                    ChunkData* data = fileManager->load(entry.path());
                    if(data == nullptr){continue;}
                    std :: cout << "\tMy Count: " << data->Structs.count << std :: endl;
                    std :: cout << (data->Structs.first == nullptr || data->Structs.last == nullptr ? "\tMy Structs Nullptr" : "\tMy Structs Fine") << std :: endl;
                    vector<Layer> list = data->data;

                    Layer* naturalLayer;
                    ChunkData* naturalData = new ChunkData();
                    if(adjustStructs || deleteNaturalChunks){
                        WorldGen :: getChunkBasics(data->xPos, data->zPos, 16, naturalData, fractal);

                        std :: cout << "\tOther Count: " << naturalData->Structs.count << std :: endl;
                        std :: cout << (naturalData->Structs.first == nullptr || naturalData->Structs.last == nullptr ? "\tOther Structs Nullptr" : "\tOther Structs Fine") << std :: endl;
                    }

                    bool needsResave = false, airOnly = true, modifiedLayer = false, naturalChunk = true;
                    for(int i = 0; i < data->data.size(); i++){ //layers

                        airOnly = true; 
                        
                        if(deleteNaturalChunks){
                            modifiedLayer = false;
                            int y = data->data.at(i).y;
                            naturalLayer = naturalData->getLayer(y);
                        }

                        for(int j = 0; j < 256; j++){

                            // check if the layer is only air, if so it should be deleted
                            if(data->data.at(i).data.at(j)){airOnly = false; if(!deleteNaturalChunks){break;}}

                            //if the data is unequal to the natural version of the data and we are still unsure if the chunk has been modified
                            if(deleteNaturalChunks && naturalChunk && naturalLayer != nullptr && data->data.at(i).data.at(j) != naturalLayer->data.at(j)){
                                modifiedLayer = true; //store this fact and stop checking for inequalities
                            }

                            //if both are true then we are done checks
                            if(!airOnly && (!deleteNaturalChunks || !naturalChunk || naturalLayer == nullptr || modifiedLayer)){break;}

                        } //blocks
                        if(airOnly){
                            data->data.erase(data->data.begin() + i);
                            i--;
                            needsResave = true;
                        }
                        if(deleteNaturalChunks && modifiedLayer){naturalChunk = false;}

                    }
                    if(replaceAllStructs || (checkStructsDuplicate && data->Structs.removeDuplicates()) || (checkStructsEqual && data->Structs != naturalData->Structs)){
                        needsResave = true;

                        std :: cout << "Setting Structs" << std :: endl;
                        data->Structs.setList(naturalData->Structs);
                        std :: cout << "\tSet" << std :: endl;
                    }

                    if(deleteNaturalChunks && naturalChunk){
                        //TEMP TODO delete chunk
                    }
                    if(needsResave){data->data.shrink_to_fit(); fileManager->save(data);}
                    if(adjustStructs || deleteNaturalChunks){
                        naturalData->Structs.clear();
                    }
                    delete naturalData;
                    data->Structs.clear();
                    delete data;
                }
            }
        }
        delete fileManager;
        delete fractal;
    }
    else{file1.close(); cout << "Save File Not Found" << endl;}
}