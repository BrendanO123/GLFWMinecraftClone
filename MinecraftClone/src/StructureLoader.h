#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <fstream>

#include "FileManager.h"
#include "Blocks.h"
#include "Structure.h"
#include "World.h"

class StructManager{

    public:
        ~StructManager();

        //init to make universal instance of world, access instance, close instance
        static StructManager* getInstance(){
            if(structManager==nullptr){
                structManager= new StructManager();
            }
            return structManager;
        }
        static bool closeInstance(){
            if(structManager == nullptr){return false;}
            delete structManager; return true;
        }
        Structure* getStruct(string name){
            if(StructLocations.find(name) == StructLocations.end()){return nullptr;}
            if(Structs.find(StructLocations.at(name)) == Structs.end()){return nullptr;}
            return Structs.at(StructLocations.at(name));
        }
        int getStructID(string name){
            if(StructLocations.find(name) == StructLocations.end()){return -1;}
            return StructLocations.at(name);
        }
        Structure* getStruct(int id){
            if(Structs.find(id) == Structs.end()){return nullptr;}
            return Structs.at(id);
        }

        //delete copy constructors
        StructManager(const StructManager&) = delete;
        StructManager& operator=(const StructManager&) = delete;

        bool saveNewStruct(string name, glm :: ivec3 first, glm :: ivec3 last, bool* forcedBlockArr = nullptr);
        bool saveStruct(string name, Structure Struct);

    private:
        int StructureCount=0;
        static string filePath;

        //private universal instance and therefore private constructor
        static StructManager* structManager;
        StructManager();

        unordered_map<int, Structure*> Structs = unordered_map<int, Structure*>();
        unordered_map<string, int> StructLocations = unordered_map<string, int>();
        static Structure* loadStruct(string path);
};
namespace Structures{
    /**
     * @brief The name of all variable fill structures and their index in the constant list.
     */
    enum STRUCT_ASSETS : unsigned char{
        OAK_TREE = 0,
        POND = 1,

        TALL_GRASS = 2,
        SHORT_GRASS_STRUCT = 3,

        BLUE_LILAC_STRUCT = 4,
        CORNFLOWER_STRUCT = 5,
        ALLIUM_STRUCT = 6,
        TULIP_PINK_STRUCT = 7,
        ROSE_STRUCT = 8,
        TULIP_ORANGE_STRUCT = 9,
        DANDILION_STRUCT = 10,
        TULIP_WHITE_STRUCT = 11,

        LILAC = 12,
        PEONY = 13,
        ROSEBUSH = 14
    };
}