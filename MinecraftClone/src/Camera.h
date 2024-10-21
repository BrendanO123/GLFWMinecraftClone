#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

const bool normalizedMoveSpeed = true;
const float moveSpeed = 0.06f;

class Camera{
    private:
        glm :: vec3 CameraFront;
        glm :: vec2 rotation;
        bool firstMouseCall;

        float lastX;
        float lastY;
        float maxFov;
    public:
        glm :: vec3 CameraPos;
        const glm :: vec3 CameraUp = glm :: vec3(0.f, 1.f, 0.f);

        float fov;
        float mouseSensitivity;

        Camera();
        Camera(float FOV, float maxFOV, glm :: vec3 pos, glm :: vec2 Rotation, float sensitivity=0.1f);
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void scroll_callback(GLFWwindow* window, double xOff, double yOff);
        void processInput(GLFWwindow* window, float deltaTime);
        glm :: mat4 getView();
        glm :: vec3 getPos();
        void setFirstMouse(bool state){firstMouseCall = state;}
};