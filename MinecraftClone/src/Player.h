#pragma once



#include "Camera.h"
#include "World.h"
#include "Shaders.h"
#include "UnitVoxelRaycaster.h"

class Player{
    private:
        Camera cam = Camera(); //makes
        GLubyte heldBlock = 0U; //sets
        Shader shader; //needs
        const int reachDist = 24;
        Raycaster raycaster = Raycaster(reachDist, &getVoxel); //makes

        glm :: ivec3 intPos; //needs initital, can be a literal
        glm :: vec3 fPos; //needs initital, can be a literal
        glm :: vec3 lookDirection; //needs initital, can be a literal

        glm :: mat4 finalTransformationMatrix; //sets

        GLuint ViewAndPrespectiveMatLoc, cameraIntVecLoc; //gets from shader
        const float renderDist;

        bool RClick();
        bool LClick();
        bool MClick();
    
        public:
            Player() : renderDist(307.f){}
            Player(Shader newShader, float renderDist);

            void updateMatrixUniforms(float ratio);
            void processInput(GLFWwindow* window, float dt);
            void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
            void mouse_callback(GLFWwindow* window, double xpos, double ypos);
            void scroll_callback(GLFWwindow* window, double xOff, double yOff);
            void setFirstMouse(bool state){cam.setFirstMouse(state);}
            glm :: ivec3 getPosition();

            static GLubyte getVoxel(int x, int y, int z){return World :: world->getBlock(x, y, z);}
};