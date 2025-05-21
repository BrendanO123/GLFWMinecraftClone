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
            if(Structs.find(name) == Structs.end()){return nullptr;}
            return Structs.at(name);
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

        unordered_map<string, Structure*> Structs = unordered_map<string, Structure*>();
        static Structure* loadStruct(string path);
};