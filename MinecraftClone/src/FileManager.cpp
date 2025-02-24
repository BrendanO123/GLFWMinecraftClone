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
            char * contents = new char [mainFileSize];
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
        else{fprintf(stderr, "FAILED TO OPEN SAVE FILE");}
    }
    else{
        file1.close();
        //writing new save file, create files, store values and return
        if(!std::filesystem::create_directories(saveFileName)){
            fprintf(stderr, "FAILED TO MAKE SAVE FILE FOLDER");
            return;
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
        else{fprintf(stderr, "FAILED TO OPEN SAVE FILE");}
        return false;
}