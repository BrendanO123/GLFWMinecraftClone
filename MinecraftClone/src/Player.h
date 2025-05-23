#pragma once

#include <queue>

#include "Camera.h"
#include "Shaders.h"
#include "UnitVoxelRaycaster.h"
#include "BlockHighlighter.h"

struct clickAction{
    raycastReturnStruct raycast;
    bool LClicked = false;

    clickAction(raycastReturnStruct rayCastResult, bool clickType = false) : raycast(rayCastResult), LClicked(clickType){}
    clickAction(){}
};
enum CLICK_TYPES : bool {L_CLICKED = false, R_CLICKED = true};
class Player{
    private:
        Camera cam = Camera(); //makes
        GLubyte heldBlock = Blocks :: OAK_PLANKS; //sets
        Shader shader; //needs
        BlockHighlighter* highlighter;
        const int reachDist = 24;
        Raycaster raycaster = Raycaster(reachDist, &getVoxel); //makes

        glm :: ivec3 intPos; //needs initital, can be a literal
        glm :: vec3 fPos; //needs initital, can be a literal
        glm :: vec3 lookDirection; //needs initital, can be a literal

        glm :: mat4 finalTransformationMatrix; //sets

        GLuint ViewAndPrespectiveMatLoc, cameraIntVecLoc; //gets from shader
        const float renderDist;
        queue<clickAction> clicks = queue<clickAction>();
    
    public:
        Player() : renderDist(307.f){}
        ~Player(){delete(highlighter);}
        Player(Shader newShader, float renderDist);

        bool MClick();
        bool RClick();
        bool LClick();
        vector<bool> resolveClicks();

        void updateMatrixUniforms(float ratio);
        void processInput(GLFWwindow* window, float dt);
        void highlightSelected();

        void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void scroll_callback(GLFWwindow* window, double xOff, double yOff);

        glm :: ivec3 getPosition();
        glm :: vec3 getFPosition();
        glm :: vec2 getRotation();
        void setPosition(glm :: ivec3 i, glm :: vec3 f);
        void setRotation(glm :: vec2 r);

        void setFirstMouse(bool state){cam.setFirstMouse(state);}
        bool setHeldBlock(GLubyte blockType){if(blockType){heldBlock = blockType; return true;} return false;}
        GLubyte getHeldBlock(){return heldBlock;}

        static GLubyte getVoxel(int x, int y, int z);
};