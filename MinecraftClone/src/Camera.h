#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

const bool normalizedMoveSpeed = true;
const float moveSpeed = 0.05f * 200;

class Camera{
    private:
        glm :: vec2 rotation;
        bool firstMouseCall;

        float lastX;
        float lastY;
    
    public:
        glm :: vec3 CameraFPos;
        glm :: ivec3 CameraIPos;
        glm :: vec3 CameraFront;
        const glm :: vec3 CameraUp = glm :: vec3(0.f, 1.f, 0.f);

        float fov;
        const float maxFov; 
        const float minFov;
        const float defaultFov;
        float mouseSensitivity;

        Camera();
        Camera(float FOV, float maxFOV, float minFOV, float defualtFOV, glm :: vec3 pos, glm :: vec2 Rotation, float sensitivity=0.1f);
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void scroll_callback(GLFWwindow* window, double xOff, double yOff);
        void processInput(GLFWwindow* window, glm :: vec3 &FPos, glm :: ivec3 &IPos, float deltaTime=1.f);
        glm :: mat4 getViewAndProjection(glm :: vec3 &LookDirection, float ratio, float renderDist);
        glm :: ivec3 getIntPos();
        glm :: vec3 getFloatPos();
        void setRotation(glm ::vec2 r);
        glm :: vec2 getRotation(){return rotation;}
        void setFirstMouse(bool state){firstMouseCall = state;}
};