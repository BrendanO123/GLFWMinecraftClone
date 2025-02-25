#include "FileManager.h"

#include <filesystem>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

int FileManager :: getInt(char * contents, int offset){
    /*int output;
    *((char*)(&output) + 0) = contents[offset];
    *((char*)(&output) + 1) = contents[offset+1];
    *((char*)(&output) + 2) = contents[offset+2];
    *((char*)(&output) + 3) = contents[offset+3];
    return output;*/
    /*int signAdjustment = 0;
    if(contents[offset+3] & 128){signAdjustment = (-1 & (1 << 31));}
    std :: cout << signAdjustment << std :: endl;
    return signAdjustment + ((unsigned int)((unsigned char)(contents[offset+0])) << 0) + ((unsigned int)((unsigned char)(contents[offset+1])) << 8) + ((unsigned int)((unsigned char)(contents[offset+2])) << 16) + ((unsigned int)((unsigned char)(contents[offset+3] & 127)) << 24);*/

    int output;
    copy(contents + offset, contents + offset + 4, (char*)&output);
    return output;
    /*int output = (int)(contents[offset]) | ((int)(contents[offset+1])) << 8 | ((int)(contents[offset+2])) << 16 | ((int)(contents[offset+3])) << 24;
    return output;*/
}
float FileManager :: getFloat(char * contents, int offset){
    /*float output;
    *((GLubyte*)(&output) + 3) = contents[offset];
    *((GLubyte*)(&output) + 2) = contents[offset+1];
    *((GLubyte*)(&output) + 1) = contents[offset+2];
    *((GLubyte*)(&output) + 0) = contents[offset+3];
    return output;*/
    /*int output = (unsigned char)(contents[offset]) | ((unsigned int)(contents[offset+1])) << 8 | ((unsigned int)(contents[offset+2])) << 16 | ((unsigned int)(contents[offset+3])) << 24;
    return *((float *) &output);*/
    float output;
    copy(contents + offset, contents + offset + 4, (char*)&output);
    return output;
}

void FileManager :: setInt(char * contents, int offset, int input){
    copy((char*)&input, ((char*)&input) + 4, contents + offset);
    /*for(int i = 0; i<4; i++){
        contents[offset] = (input & 255);
        input >>= 8; offset++;
    }*/
    /*contents[offset] = *((char*)(&input) + 0);
    contents[offset+1] = *((char*)(&input) + 1);
    contents[offset+2] = *((char*)(&input) + 2);
    contents[offset+3] = *((char*)(&input) + 3);*/
}
void FileManager :: setFloat(char * contents, int offset, float input){
    /*contents[offset] = *((GLubyte*)(&input) + 0);
    contents[offset+1] = *((GLubyte*)(&input) + 1);
    contents[offset+2] = *((GLubyte*)(&input) + 2);
    contents[offset+3] = *((GLubyte*)(&input) + 3);*/copy((char*)&input, ((char*)&input) + 4, contents + offset);
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

            /*for(int i =0; i< mainFileSize; i++){cout << int(contents[i]) << " | ";}
            cout << endl;*/

            seed = getInt(contents, 0);
            playerPositionI.x = getInt(contents, sizeof(int32_t) * 1);
            playerPositionI.y = getInt(contents, sizeof(int32_t) * 2);
            playerPositionI.z = getInt(contents, sizeof(int32_t) * 3);

            playerPositionF.x = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*0);
            playerPositionF.y = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*1);
            playerPositionF.z = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*2);

            playerRoation.x = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*3);
            playerRoation.y = getFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*4);

            /*std :: cout << "Seed: " << seed << std :: endl;
            std :: cout << "Position: (" << playerPositionI.x << ", " <<  playerPositionI.y << ", " << playerPositionI.z << ") | " << std :: endl;
            std :: cout << "\t(" << playerPositionF.x << ", " <<  playerPositionF.y << ", " << playerPositionF.z << ")" << std :: endl;
            std :: cout << "Rotation: (" << playerRoation.x << ", " <<  playerRoation.y << ")" << std :: endl;*/

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
    //mofstream file;// = ofstream ((saveFileName + "/main").c_str(), ios::out|ios::binary);
    ofstream file; file.open((saveFileName + "/main").c_str(), ios::out|ios::binary); 
        if(file.is_open()){
            char * contents = new char [mainFileSize];

            /*std :: cout << "Seed: " << seed << std :: endl;
            std :: cout << "Position: (" << playerPositionI.x << ", " <<  playerPositionI.y << ", " << playerPositionI.z << ") | " << std :: endl;
            std :: cout << "\t(" << playerPositionF.x << ", " <<  playerPositionF.y << ", " << playerPositionF.z << ")" << std :: endl;
            std :: cout << "Rotation: (" << playerRoation.x << ", " <<  playerRoation.y << ")" << std :: endl;*/

            setInt(contents, 0, seed);
            setInt(contents, sizeof(int32_t)*1, playerPositionI.x);
            setInt(contents, sizeof(int32_t)*2, playerPositionI.y);
            setInt(contents, sizeof(int32_t)*3, playerPositionI.z);

            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*0, playerPositionF.x);
            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*1, playerPositionF.y);
            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*2, playerPositionF.z);

            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*3, playerRoation.x);
            setFloat(contents, sizeof(int32_t) * 4 + sizeof(float)*4, playerRoation.y);

            /*for(int i =0; i< mainFileSize; i++){cout << int(contents[i]) << " | ";}
            cout << endl;*/

            file.write(contents, mainFileSize);
            //file << seed << playerPositionI.x << playerPositionI.y << playerPositionI.z << playerPositionF.x << playerPositionF.y << playerPositionF.z << playerRoation.x << playerRoation.y << std :: endl;
            file.close();
            delete[] contents;
            return true;
        }
        else{file.close(); fprintf(stderr, "FAILED TO OPEN SAVE FILE");}
        return false;
}

bool FileManager :: save(ChunkData* data){
    //glm :: ivec2 pos = data->pos;
    int x = data->xPos, y = data->zPos;
    stringstream folderStream;
    folderStream << saveFileName << "/region" << (/*pos.x*/x>>4) << "_" << (/*pos.y*/y>>4);
    string name = folderStream.str();
    if(!std::filesystem::create_directories(name.c_str())){
        /*fprintf(stderr, "FAILED TO MAKE SAVE FILE FOLDER");
        return false;*/
    }
    folderStream << "/chunk" << (/*pos.x*/x & 15) << "_" << (/*pos.y*/y & 15);
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
            //for(int j = 0; j<256; j++){contents[offset++] = layer.data[j];}
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
        for(int i = 0; i <layerCount; i++){
            y=contents[offset++];
            //data->data.emplace_back(y);
            //index = i;
            index = data->safeLayerFetch(y);
            data->data.at(index).data.reserve(256);
            copy(contents + offset, contents + offset + 256, /*data->data.data()*/arr); offset+=256;
            for(int j=0; j<256; j++){data->data.at(index).data.at(j) = arr[j];}
        }
        //for(int i=0; i< data->data.size(); i++){std :: cout << int(data->data.at(i).y) << std :: endl;}

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
        //data->pos = glm :: ivec2(x, z);
        data->xPos = x; data->zPos = z;
        return data;
    }
    else{file.close(); fprintf(stderr, "FAILED TO OPEN SAVE FILE");}
    return nullptr;
}