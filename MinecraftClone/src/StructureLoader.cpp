#include "StructureLoader.h"

namespace fs = std::filesystem;
using namespace std; 

StructManager* StructManager :: structManager = nullptr;
string StructManager :: filePath = "MinecraftClone/assets/Structures/";

StructManager :: ~StructManager(){
    for(auto iterate = Structs.begin(); iterate != Structs.end();){
        delete iterate->second;
        iterate = Structs.erase(iterate);
    }
    StructLocations.clear();
}
StructManager :: StructManager(){
    StructureCount = 0;
    Structs = unordered_map<int, Structure*>();
    StructLocations = unordered_map<string, int>();
    for (const auto& entry : fs::directory_iterator(StructManager :: filePath)) {
        if(fs::is_regular_file(entry.path())){
            if(entry.path().extension()==".Struct"){
                Structure* Struct = loadStruct(entry.path().string());
                if(Struct!=nullptr){
                    Structs.emplace(Struct->id, Struct);
                    StructLocations.emplace(entry.path().stem(), Struct->id);
                    StructureCount++;
                }
            }
        }
    }
}

Structure* StructManager :: loadStruct(string path){
    ifstream file1(path.c_str());
    if(file1.good()){
        file1.close();
        ifstream file = ifstream(path.c_str(), ios::in|ios::binary);
        if(file.is_open() && file.good()){

            char* basics = new char[4*sizeof(uint32_t)];
            file.read(basics, 4*sizeof(uint32_t));

            int sizeX, sizeY, sizeZ, id;
            sizeX = FileManager :: getInt(basics, 0);
            sizeY = FileManager :: getInt(basics, sizeof(uint32_t));
            sizeZ = FileManager :: getInt(basics, sizeof(uint32_t) * 2);
            id = FileManager :: getInt(basics, sizeof(uint32_t) * 3);

            delete [] basics;
            int arraySize = sizeX * sizeY * sizeZ;
            int mainSize = arraySize + ((arraySize+7)>>3) + 1;

            char* contents = new char[mainSize];
            file.read(contents, mainSize);
            file.close();

            GLubyte blocks[arraySize];
            copy(contents, contents + arraySize, blocks);

            bool forcedArr[((arraySize+7)>>3)<<3];
            copy(contents + arraySize, contents+mainSize-1, (char*)forcedArr);
            
            vector<bool> forcedBlocks = vector<bool>();
            forcedBlocks.reserve(((arraySize+7)>>3)<<3);
            for(int i=0; i<((arraySize+7)>>3)<<3; i++){forcedBlocks.emplace_back(forcedArr[i]);}

            Structure* Struct = new Structure(sizeX, sizeY, sizeZ, id, blocks, forcedBlocks);
            if(contents[mainSize-1] != EOF){fprintf(stderr,"INCORRECT STRUCTURE FILE ENCODNG FOUND"); /*return nullptr*/}
            delete [] contents;

            return Struct;
        }
    }
    file1.close();
    fprintf(stderr, "FAILED TO OPEN STRUCTURE FILE");
    return nullptr;
}

bool StructManager :: saveNewStruct(string name, glm :: ivec3 first, glm :: ivec3 last, bool* forcedBlockArr){
    return false;
}
bool StructManager :: saveStruct(string name, Structure Struct){

    ofstream file; file.open((filePath + name + ".Struct").c_str(), ios::out|ios::binary|ios::trunc); 

    int arraySize = Struct.sizeX * Struct.sizeY * Struct.sizeZ;
    int mainSize = arraySize + ((arraySize+7)>>3) + 4 * sizeof(uint32_t)+1;
    int offset = 0;

    if(file.is_open()){

        //file contents
        char* contents = new char [mainSize];
        contents[mainSize-1] = EOF;

        //structure size
        FileManager :: setInt(contents, 0, Struct.sizeX);
        FileManager :: setInt(contents, sizeof(uint32_t)*1, Struct.sizeY);
        FileManager :: setInt(contents, sizeof(uint32_t)*2, Struct.sizeZ);

        FileManager :: setInt(contents, sizeof(uint32_t)*3, Struct.id);


        //block type data
        offset = sizeof(uint32_t)*4;
        copy((char*)Struct.contents, (char*)Struct.contents + arraySize, contents+offset);
        offset+=arraySize;
        

        //forced block array specifying where to carve out blocks for air
        int forcedBlockArrSize = (((arraySize+7)>>3)<<3);
        bool arr[forcedBlockArrSize];

        std::memset(arr, 0, forcedBlockArrSize);
        for(int i=0; i<arraySize; i++){arr[i] = Struct.forcedBlocks.at(i);}
        copy((char*)(arr), (char*)(arr) + ((arraySize+7)>>3), contents+offset);


        file.write(contents, mainSize);
        file.close();

        delete[] contents;
        return true;
    }
    else{file.close(); fprintf(stderr, "FAILED TO OPEN SAVE FILE");}
    return false;
}

