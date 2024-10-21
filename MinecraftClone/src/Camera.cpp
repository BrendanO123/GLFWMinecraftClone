#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera :: Camera(){
    CameraFront = glm :: vec3(0.f, 0.f, -1.f);
    rotation = glm :: vec2(0.f, -90.f);
    firstMouseCall = true;
    lastX = 400;
    lastY = 300;
    maxFov = 75.0f;

    CameraPos = glm :: vec3(0.f, 0.f, 4.5f);

    fov = 45.f;
    mouseSensitivity = 0.1f;
}

Camera :: Camera(float FOV, float maxFOV, glm :: vec3 pos, glm :: vec2 Rotation, float sensitivity){
    fov = FOV; maxFov = maxFOV; CameraPos = pos; rotation = Rotation; mouseSensitivity = sensitivity;

    CameraFront.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    CameraFront.y = sin(glm::radians(rotation.x));
    CameraFront.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    CameraFront = glm :: normalize(CameraFront);

    firstMouseCall = true;
    lastX = 400;
    lastY = 300;
}
glm :: vec3 Camera :: getPos(){return CameraPos;}

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
    if(fov<1.0f){fov=1.0f;}
    if(fov>maxFov){fov=maxFov;}
}

void Camera :: processInput(GLFWwindow* window, float deltaTime=1.f){

    //TODO: create pause menu and f3 screen

    glm :: vec3 move = glm :: vec3 (0.f, 0.f, 0.f);
    bool shouldMove = false;
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
    CameraPos += move * moveSpeed * ((glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) ? 4.0f : 1.0f);
}

glm :: mat4 Camera :: getView(){
    glm :: mat4 view = glm :: identity<glm :: mat4>();
    view = glm :: lookAt(CameraPos, CameraFront + CameraPos, CameraUp);

    return view;
}