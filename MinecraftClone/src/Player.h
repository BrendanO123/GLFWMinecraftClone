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
        GLubyte heldBlock = 0U; //sets
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

        bool RClick();
        bool LClick();
    
        public:
            Player() : renderDist(307.f){}
            ~Player(){delete(highlighter);}
            Player(Shader newShader, float renderDist);

            bool MClick();
            vector<bool> resolveClicks();
            void updateMatrixUniforms(float ratio);
            void highlightSelected();
            void processInput(GLFWwindow* window, float dt);
            void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
            void mouse_callback(GLFWwindow* window, double xpos, double ypos);
            void scroll_callback(GLFWwindow* window, double xOff, double yOff);
            void setFirstMouse(bool state){cam.setFirstMouse(state);}
            glm :: ivec3 getPosition();

            static GLubyte getVoxel(int x, int y, int z);
};