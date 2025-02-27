#include <filesystem>
#include <string>

#include "FileManager.h"
#include "ChunkData.h"

using namespace std;

int main(){
    string saveFileName; 

    std :: cout << "Enter a Name for the Save File and Press Enter:" << std :: endl;
    getline(cin, saveFileName);

    char* chars = saveFileName.data();
    for(int i =0; i<saveFileName.length(); i++){if(chars[i] == ' '){chars[i] = '_';}}
    saveFileName = string(chars);


    ifstream file1(("MinecraftClone/saves/" + saveFileName + "/main").c_str());
    if(file1.is_open()){file1.close(); //exists


        int seed = 0; glm :: ivec3 ipos = glm :: ivec3(0); glm :: vec3 fpos = glm :: vec3(0); glm :: vec2 rot = glm :: vec2(0);
        FileManager* fileManager = new FileManager(saveFileName, seed, ipos, fpos, rot);


        for(const auto & directory : std::filesystem::directory_iterator(("MinecraftClone/saves/" + saveFileName + "/"))){ //regions

            if(directory.is_directory()){

                for(const auto & entry : std::filesystem::directory_iterator(directory)){ //chunks
                    ChunkData* data = fileManager->load(entry.path());
                    if(data == nullptr){continue;}
                    vector<Layer> list = data->data;

                    bool needsResave = false, airOnly = true;
                    for(int i = 0; i < data->data.size(); i++){ //layers

                        airOnly = true;
                        for(int j = 0; j < 256; j++){if(data->data.at(i).data.at(j)){airOnly = false; break;}} //blocks
                        if(airOnly){
                            data->data.erase(data->data.begin() + i);
                            i--;
                            needsResave = true;
                        }

                    }
                    if(needsResave){data->data.shrink_to_fit(); fileManager->save(data);}
                    delete data;
                }
            }
        }
        delete fileManager;
    }
    else{file1.close(); cout << "Save File Not Found" << endl;}
}