#include <string.h>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <GLFW/linmath.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <glm/gtc/type_ptr.hpp>

#include "Player.h"
#include "World.h"
#include "StructureLoader.h"
#include "Structures.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

#define VSYNC 1 //0 = off, 1 = on

int chunkRenderDist = 12;
float renderDist = int(chunkRenderDist*16*1.6 + 0.5f);

Player* player;

bool menu = false;
bool structureCreatorMode = false;

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error %s\n", description);
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(!menu){player->mouse_callback(window, xpos, ypos);}
}

static void scroll_callback(GLFWwindow* window, double xOff, double yOff){
    if(!menu){player->scroll_callback(window, xOff, yOff);}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
    else if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        menu = !menu;
        if(menu){glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}
        else{glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); player->setFirstMouse(true);}
    }
    else if(key == GLFW_KEY_M && action == GLFW_PRESS){player->MClick();}
    else if(key == GLFW_KEY_TAB && action == GLFW_PRESS){player->RClick();}

    else if(key == GLFW_KEY_1 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: OAK_PLANKS);}
    else if(key == GLFW_KEY_2 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: GLASS);}
    else if(key == GLFW_KEY_3 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: COBBLE_STONE);}
    else if(key == GLFW_KEY_4 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: SMOOTH_ANDESITE);}
    else if(key == GLFW_KEY_5 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: BRICK);}
    else if(key == GLFW_KEY_6 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: DARK_PLANKS);}
    else if(key == GLFW_KEY_7 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: DARK_LOG);}
    else if(key == GLFW_KEY_8 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: COARSE_DIRT);}
    else if(key == GLFW_KEY_9 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: PODZOL);}
    else if(key == GLFW_KEY_0 && action == GLFW_PRESS){player->setHeldBlock(Blocks :: ROOTED_DIRT);}
    else if(key == GLFW_KEY_UP && action == GLFW_PRESS){
        int block = player->getHeldBlock()-1; if(block==0){block=35;}
        player->setHeldBlock(block);
    }
    else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        int block = player->getHeldBlock()+1; if(block==36){block=1;}
        player->setHeldBlock(block);
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS){
        structureCreatorMode = !structureCreatorMode;
        //player->setStructureCreatorMode(structureCreatorMode);
    }
    else if(key == GLFW_KEY_ENTER && action == GLFW_PRESS){
        //if(structureCreatorMode){player->createStructure();}
        structureCreatorMode=false;
    }

    else if(key == GLFW_KEY_L && action == GLFW_PRESS){World :: getInstance() -> setShouldSave(true);}
}
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(!menu){player->mouseClickCallback(window, button, action, mods);}
}

void processInput(GLFWwindow* window, float deltaTime=1.f){if(!menu){player->processInput(window, deltaTime);}}


const string title = "Minecraft Clone";

int main(){
    std :: cout << "Initializing Dependencies" << std :: endl;
    glfwSetErrorCallback(error_callback);

    if(!glfwInit()){ //GLFW initialization fails
        glfwTerminate();
        printf("GLFW INIT FAILED\n", stderr);
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(640, 480, title.data(), NULL, NULL);
    if(!window){ // Window creation fails
        glfwTerminate();
        printf("GLFW WINDOW INIT FAILED\n", stderr);
        exit(EXIT_FAILURE); 
    } 
    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGL(glfwGetProcAddress)){ // Glad initialization fails
        glfwDestroyWindow(window);
        glfwTerminate();
        printf("GLAD INIT FAILED\n", stderr);
        exit(EXIT_FAILURE); 
    }
    glfwSwapInterval(VSYNC);

    Shader shader = Shader("MinecraftClone/assets/shaders/VShader.glsl", "MinecraftClone/assets/shaders/FShader.glsl");
    shader.use();
    player = new Player(shader, renderDist);

    float alphaErrorRange=0.2f; //MUST BE >0!!
    shader.setFloat("invBlockMapW_blocks", 1.f / Blocks :: blockMapW_blocks);
    shader.setFloat("invBlockMapH_blocks", 1.f / Blocks :: blockMapH_blocks);
    shader.setFloat("alphaH", alphaErrorRange);


    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    /** TODO:
     * c++:
     * png writing for temp and rainfall maps
     *      could always also do biome maps if needed
     * 
     * math:
     * rainfall math
     *      distance to ocean and rainshadow dot product math
     * temperature math
     *      perlin noise, z cord, rainfall * constant
     * 
     * 
     * old but useful todo list:
     * add way more block types and sprites
     * add f3 screen and png writing for underlying maps
     * 
     * get vukan and metalvk
     * add compute shader dispatching for chunk gen
     * make FBm noise for temperature noise, and rainfall noise maps
     * 
     * create latitude temperature map and add to temperature noise
     * 
     * create variable layer count FBm for terrain height w/ errosion and continental maps
     * create rainshadow math and add to rainfall noise
     * 
     * create biome maps
     * create cave noise
     * 
     * create river placment math
     */

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    constexpr const int maxMipmapLevel = 4;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, maxMipmapLevel);

    stbi_set_flip_vertically_on_load(true);
    stbi_set_unpremultiply_on_load(false);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for(int i = 0; i <= maxMipmapLevel; i++){
        int w, h, channels;
        stringstream str; str << "MinecraftClone/assets/sprites/Levels/mapLevel" << i << ".png";
        GLubyte *data = stbi_load(str.str().c_str(), &w, &h, &channels, 0);
        if(data){
            glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            if(i==0){glGenerateMipmap(GL_TEXTURE_2D);}
        }
        else{
            glfwDestroyWindow(window);
            glfwTerminate();
            printf("TEXTURE LOAD FAILED\n", stderr);
            exit(EXIT_FAILURE); 
        }
        stbi_image_free(data);
    }

    string saveFileName, seedInput; int seed = -1;

    std :: cout << "Starting Program" << std :: endl;
    std :: cout << "Enter a Name for the Save File and Press Enter:" << std :: endl;
    getline(cin, saveFileName);
    char* chars = saveFileName.data();
    for(int i =0; i<saveFileName.length(); i++){if(chars[i] == ' '){chars[i] = '_';}}
    saveFileName = string(chars);

    ifstream file1(("MinecraftClone/saves/" + saveFileName + "/main").c_str());
    if(!file1.is_open()){file1.close();
        std :: cout << "Enter a Starting Seed (Or Leave Blank) and Press Enter:" << std :: endl;
        stringstream stream;
        getline(cin, seedInput);
        stream << seedInput;
        stream >> seed;
        if(stream.fail()){
            seed = (int)time(0);
        }
    }
    else{file1.close();}
    World :: init(&shader, chunkRenderDist, seed, saveFileName, player);

    StructManager* structManager = StructManager :: getInstance();
    /*structManager->saveStruct("OAK_TREE", Structures :: Structs[Structures :: OAK_TREE]);
    structManager->saveStruct("POND", Structures :: Structs[Structures :: POND]);
    structManager->saveStruct("TALL_GRASS", Structures :: Structs[Structures :: TALL_GRASS]);
    structManager->saveStruct("SHORT_GRASS", Structures :: Structs[Structures :: SHORT_GRASS_STRUCT]);
    structManager->saveStruct("BLUE_LILAC", Structures :: Structs[Structures :: BLUE_LILAC_STRUCT]);
    structManager->saveStruct("CORNFLOWER", Structures :: Structs[Structures :: CORNFLOWER_STRUCT]);
    structManager->saveStruct("ALLIUM", Structures :: Structs[Structures :: ALLIUM_STRUCT]);
    structManager->saveStruct("TULIP_PINK", Structures :: Structs[Structures :: TULIP_PINK_STRUCT]);
    structManager->saveStruct("ROSE", Structures :: Structs[Structures :: ROSE_STRUCT]);
    structManager->saveStruct("TULIP_ORANGE", Structures :: Structs[Structures :: TULIP_ORANGE_STRUCT]);
    structManager->saveStruct("DANDILION", Structures :: Structs[Structures :: DANDILION_STRUCT]);
    structManager->saveStruct("TULIP_WHITE", Structures :: Structs[Structures :: TULIP_WHITE_STRUCT]);
    structManager->saveStruct("LILAC", Structures :: Structs[Structures :: LILAC]);
    structManager->saveStruct("PEONY", Structures :: Structs[Structures :: PEONY]);
    structManager->saveStruct("ROSEBUSH", Structures :: Structs[Structures :: ROSEBUSH]);*/

    glClearColor(135/255.0f, 206/255.0f, 235/255.0f, 1.0f);
    float deltaTime, currentFrame; 
    float lastFrame = glfwGetTime();
    while(!glfwWindowShouldClose(window)){ //while window wants to stay open

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        float ratio = width / (float) height;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window, deltaTime);

        player->updateMatrixUniforms(ratio);
        World :: getInstance()->update(player->getPosition(), menu, player);
        if(!menu){player->highlightSelected();}

        glfwSwapBuffers(window);
        if(!menu){glfwPollEvents();}
        else{glfwWaitEvents();}
    }

    World :: closeInstance();
    StructManager :: closeInstance();
    delete (player);
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}