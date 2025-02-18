#include "Camera.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Camera :: Camera() : maxFov(110.f), minFov(15.0f), defaultFov(70.f){
    rotation = glm :: vec2(0.f, -89.9f);
    CameraFront.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    CameraFront.y = sin(glm::radians(rotation.x));
    CameraFront.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    CameraFront = glm :: normalize(CameraFront);

    firstMouseCall = true;
    lastX = 400;
    lastY = 300;

    CameraFPos = glm :: vec3(0.f, 0.f, 0.f);
    CameraIPos = glm :: vec3(8, 135, 8);

    fov = defaultFov;
    mouseSensitivity = 0.1f;
}

Camera :: Camera(float FOV, float maxFOV, float minFOV, float defaultFOV, glm :: vec3 pos, glm :: vec2 Rotation, float sensitivity) : maxFov(maxFOV), minFov(minFOV), defaultFov(defaultFOV) {
    fov = FOV; rotation = Rotation; mouseSensitivity = sensitivity;
    CameraIPos = glm :: ivec3((int)pos.x, (int)pos.y, (int)pos.z);
    CameraFPos = glm :: ivec3(pos.x - CameraIPos.x, pos.y - CameraIPos.y, pos.z - CameraIPos.z);

    CameraFront.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    CameraFront.y = sin(glm::radians(rotation.x));
    CameraFront.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    CameraFront = glm :: normalize(CameraFront);

    firstMouseCall = true;
    lastX = 400;
    lastY = 300;
}
glm :: ivec3 Camera :: getIntPos(){return CameraIPos;}
glm :: vec3 Camera :: getFloatPos(){return CameraFPos;}

void Camera :: mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(firstMouseCall){lastX=xpos; lastY=ypos; firstMouseCall=false; return;}
    float xOff = xpos-lastX; float yOff = lastY-ypos;
    xOff *= mouseSensitivity; yOff *=mouseSensitivity;

    rotation += glm :: vec2(yOff, xOff);
    float lookRange = 89.5f;
    if(rotation.x > lookRange){rotation.x = lookRange;}
    else if(rotation.x < -lookRange){rotation.x = -lookRange;}
    if(rotation.y<0){rotation.y+=360.f;}
    while(rotation.y>360){rotation.y-=360.f;}

    lastX = xpos; lastY=ypos;
    CameraFront.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    CameraFront.y = sin(glm::radians(rotation.x));
    CameraFront.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    CameraFront = glm :: normalize(CameraFront);
}

void Camera :: scroll_callback(GLFWwindow* window, double xOff, double yOff){
    fov -= (float)yOff;
    if(fov<minFov){fov=minFov;}
    if(fov>maxFov){fov=maxFov;}
}

void Camera :: processInput(GLFWwindow* window, glm :: vec3 &FPos, glm :: ivec3 &IPos, float deltaTime){

    //TODO: create pause menu and f3 screen

    glm :: vec3 move = glm :: vec3 (0.f, 0.f, 0.f);
    bool shouldMove = false;
    if(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS){fov=defaultFov;}
    if((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ^ (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)){
        shouldMove = true;
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){move += CameraFront;}
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){move -= CameraFront;}
    }
    if((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) ^ (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)){
        shouldMove = true;
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){move += glm::normalize(glm::cross(CameraFront, CameraUp));}
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){move -= glm::normalize(glm::cross(CameraFront, CameraUp));}
    }
    if((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) ^ (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)){
        shouldMove = true;
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){move += CameraUp;}
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){move -= CameraUp;}
    }

    if(shouldMove && normalizedMoveSpeed){move = glm :: normalize(move);}
    CameraFPos += move * moveSpeed * ((glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) ? 4.5f : 1.0f);
    CameraIPos += glm :: ivec3(CameraFPos);
    CameraFPos -= glm :: ivec3(CameraFPos);
    IPos = CameraIPos; FPos = CameraFPos;
}

glm :: mat4 Camera :: getViewAndProjection(glm :: vec3 &LookDirection, float ratio, float renderDist){
    return glm::perspective(glm::radians(fov), ratio, 0.1f, renderDist) * glm :: lookAt(CameraFPos, CameraFront + CameraFPos, CameraUp);
}