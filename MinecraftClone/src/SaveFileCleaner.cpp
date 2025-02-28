#include "ChunkCleaner.h"

#ifndef CLEAN_ALL
int main(){
    string saveFileName; 

    std :: cout << "Enter a Name for the Save File and Press Enter:" << std :: endl;
    getline(cin, saveFileName);

    char* chars = saveFileName.data();
    for(int i =0; i<saveFileName.length(); i++){if(chars[i] == ' '){chars[i] = '_';}}
    saveFileName = string(chars);
    Cleaner :: cleanChunk(saveFileName);
}

#else

int main(){
    string saveFileName; 
    for(const auto &directory : std::filesystem::directory_iterator("MinecraftClone/saves/")){
        if(directory.is_directory()){
            saveFileName = directory.path().string();
            saveFileName = saveFileName.substr(saveFileName.find("MinecraftClone/saves/") + 21);

            Cleaner :: cleanChunk(saveFileName);
        }
    }
}

#endif