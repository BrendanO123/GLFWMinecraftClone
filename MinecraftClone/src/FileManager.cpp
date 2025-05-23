#include "FileManager.h"

#include <filesystem>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

int FileManager :: getInt(char * contents, int offset){
    int output;
    copy(contents + offset, contents + offset + 4, (char*)&output);
    return output;
}
float FileManager :: getFloat(char * contents, int offset){
    float output;
    copy(contents + offset, contents + offset + 4, (char*)&output);
    return output;
}

void FileManager :: setInt(char * contents, int offset, int input){
    copy((char*)&input, ((char*)&input) + 4, contents + offset);
}
void FileManager :: setFloat(char * contents, int offset, float input){
    copy((char*)&input, ((char*)&input) + 4, contents + offset);
}
FileManager :: FileManager(string name, int &seed, glm :: ivec3 &playerPositionI, glm :: vec3 &playerPositionF, glm :: vec2 &playerRoation){
    saveFileName = (savesFolderPath + name);
    string mainPath = saveFileName + "/main";
    ifstream file1(mainPath.c_str());
    if(file1.good()){
        file1.close();
        //reading from save, get values and store into parameters, then return
        ifstream file  = ifstream (mainPath.c_str(), ios::in|ios::binary); 
        if(file.is_open() && file.good()){
            char* contents = new char [mainFileSize];
            file.read(contents, mainFileSize); 
            file.close();

            seed = getInt(contents, 0);
            playerPositionI.x = getInt(contents, sizeof(int32_t) * 1);
            playerPositionI.y = getInt(contents, sizeof(int32_t) * 2);
            playerPositionI.z = getInt(contents, sizeof(int32_t) * 3);

            playerPositionF.x = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*0);
            playerPositionF.y = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*1);
            playerPositionF.z = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*2);

            playerRoation.x = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*3);
            playerRoation.y = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*4);

            delete[] contents;
            return;
        }
        else{file.close(); fprintf(stderr, "FAILED TO OPEN SAVE FILE");}
    }
    else{
        file1.close();
        //writing new save file, create files, store values and return
        if(!std::filesystem::create_directories(saveFileName)){
            /*fprintf(stderr, "FAILED TO MAKE SAVE FILE FOLDER");
            return;*/
        }
        save(seed, playerPositionI, playerPositionF, playerRoation);
    }
}

bool FileManager :: save(int seed, glm :: ivec3 playerPositionI, glm :: vec3 playerPositionF, glm :: vec2  playerRoation){
    ofstream file; file.open((saveFileName + "/main").c_str(), ios::out|ios::binary); 
        if(file.is_open()){
            char * contents = new char [mainFileSize];

            setInt(contents, 0, seed);
            setInt(contents, sizeof(int32_t)*1, playerPositionI.x);
            setInt(contents, sizeof(int32_t)*2, playerPositionI.y);
            setInt(contents, sizeof(int32_t)*3, playerPositionI.z);

            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*0, playerPositionF.x);
            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*1, playerPositionF.y);
            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*2, playerPositionF.z);

            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*3, playerRoation.x);
            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*4, playerRoation.y);

            file.write(contents, mainFileSize);
            file.close();
            delete[] contents;
            return true;
        }
        else{file.close(); fprintf(stderr, "FAILED TO OPEN SAVE FILE");}
        return false;
}

bool FileManager :: save(ChunkData* data){
    int x = data->xPos, y = data->zPos;
    stringstream folderStream;
    folderStream << saveFileName << "/region" << (x>>4) << "_" << (y>>4);
    string name = folderStream.str();
    if(!std::filesystem::create_directories(name.c_str())){
        /*fprintf(stderr, "FAILED TO MAKE SAVE FILE FOLDER");
        return false;*/
    }
    folderStream << "/chunk" << (x & 15) << "_" << (y & 15);
    name = folderStream.str();
    ofstream file; file.open(name.c_str(), ios::out|ios::binary|ios::trunc); 

    if(file.is_open()){
        int layerCount = data->data.size();

        int structCount = 0;
        vector<char> structData = vector<char>();
        structData.reserve(data->Structs.count * 4);

        StructNode* next = data->Structs.first;
        while(next !=nullptr){
            structCount++;
            structData.push_back(next->id);
            structData.push_back(next->pos.x);
            structData.push_back(next->pos.y);
            structData.push_back(next->pos.z);
            next = next->next;
        }

        int byteCount = 2 + layerCount * (256+1) + structCount * 4;
        char* contents = new char[byteCount];

        contents[0] = (unsigned char)layerCount;
        contents[1] = (unsigned char)structCount;
        int offset = 2;
        for(int i=0; i<layerCount; i++){
            Layer layer = data->data.at(i);
            contents[offset++] = layer.y; 
            copy((char*)layer.data.data(), (char*)layer.data.data()+256, contents + offset); offset+=256;
        }

        copy(structData.data(), structData.data()+structCount, contents+offset);

        file.write(contents, byteCount);
        file.close();
        delete[] contents;
        return true;
    }
    else{file.close(); fprintf(stderr, "FAILED TO OPEN SAVE FILE");}
    return false;
}


bool FileManager :: hasFile(int x, int z){
    stringstream folderStream; folderStream << saveFileName << "/region" << (x>>4) << "_" << (z>>4) << "/chunk" << (x & 15) << "_" << (z & 15);
    string name = folderStream.str();
    ifstream file(name.c_str());
    if(file.is_open()){file.close(); return true;}
    file.close(); return false;
}


ChunkData* FileManager :: load(string path){
    int regionNameIndex = path.find("/region");
    if(regionNameIndex == -1){return nullptr;}
    path = path.substr(regionNameIndex);
    int chunkNameIndex = path.find("/chunk");
    if(chunkNameIndex == -1){return nullptr;}


    string region = path.substr(7, chunkNameIndex-7);
    string chunk = path = path.substr(chunkNameIndex+6);

    int regionSeperatorIndex = region.find("_"); 
    int chunkSeperatorIndex = chunk.find("_");

    int RX, RY, CX, CY;
    stringstream stream;
    stream << region.substr(0, regionSeperatorIndex);
    stream >> RX; if(stream.bad()){return nullptr;}
    stream.clear();
    stream << region.substr(regionSeperatorIndex+1);
    stream >> RY; if(stream.bad()){return nullptr;}

    stream.clear();
    stream << chunk.substr(0, chunkSeperatorIndex);
    stream >> CX; if(stream.bad()){return nullptr;}
    stream.clear();
    stream << chunk.substr(chunkSeperatorIndex+1);
    stream >> CY; if(stream.bad()){return nullptr;}

    return load(RX * 16 + CX, RY * 16 + CY);
}

ChunkData* FileManager :: load(int x, int z){
    stringstream folderStream;
    folderStream << saveFileName << "/region" << (x>>4) << "_" << (z>>4) << "/chunk" << (x & 15) << "_" << (z & 15);
    string name = folderStream.str();

    ifstream file; file.open(name.c_str(), ios::in|ios::binary); 

    if(file.is_open() && file.good()){
        char * sizes = new char[2];
        file.read(sizes, 2);
        int layerCount = (unsigned char)(sizes[0]), structCount = (unsigned char)(sizes[1]);
        int length = layerCount * 257 + structCount * 4;
        delete[] sizes;
        char * contents = new char[length];
        file.read(contents, length);
        file.close();

        //push bask layers so that order does not reverse
        ChunkData* data = new ChunkData();
        data->data.reserve(layerCount);
        GLubyte arr[256] = {0};
        GLubyte y;
        int offset = 0;
        int index;
        //bool airOnly = true;
        //data->fileStored = true;
        for(int i = 0; i < layerCount; i++){
            //airOnly = true;
            y=contents[offset++];
            index = data->safeLayerFetch(y);

            data->data.at(index).data.reserve(256);
            copy(contents + offset, contents + offset + 256, arr); offset+=256;
            for(int j=0; j<256; j++){data->data.at(index).data.at(j) = arr[j];/*if(arr[j]){airOnly = false;}*/}
            /*if(airOnly){
                data->data.erase(data->data.begin() + index);
                i--;
                data->fileStored = false;
            }*/
        }
        data->data.shrink_to_fit();

        data->Structs.count = structCount;
        if(structCount !=0){
            data->Structs.first = data->Structs.last = new StructNode((GLubyte)contents[offset], (GLubyte)contents[offset+1], (GLubyte)contents[offset+2], (GLubyte)contents[offset+3]); offset+=4; 
            for(int i = 1; i<structCount; i++){
                data->Structs.last->next = new StructNode((GLubyte)contents[offset], (GLubyte)contents[offset+1], (GLubyte)contents[offset+2], (GLubyte)contents[offset+3]); offset+=4; 
                data->Structs.last = data->Structs.last->next;
            }
        }

        delete[] contents;
        data->hasBuilds = true; data->fileStored = true;
        data->xPos = x; data->zPos = z;
        return data;
    }
    else{file.close(); std :: cout << "FAILED TO OPEN SAVE FILE: " << name << std :: endl;}
    return nullptr;
}