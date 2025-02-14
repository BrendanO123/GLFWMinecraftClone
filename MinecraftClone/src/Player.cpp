#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



using namespace std;

Player :: Player(Shader newShader, float RenderDist) : shader(newShader), renderDist(RenderDist){
    ViewAndPrespectiveMatLoc = glGetUniformLocation(shader.program, "viewAndProjectionMatrix");
    cameraIntVecLoc = glGetUniformLocation(shader.program, "cameraPosI");

    intPos = cam.CameraIPos;
    fPos = cam.CameraFPos;
    lookDirection = cam.CameraFront;
    finalTransformationMatrix = glm :: identity<glm :: mat4>();
}

void Player :: updateMatrixUniforms(float ratio){
    glUniformMatrix4fv(ViewAndPrespectiveMatLoc, 1, GL_FALSE, glm::value_ptr(cam.getViewAndProjection(lookDirection, ratio, renderDist)));
    fPos = cam.CameraFPos;
    glUniform3f(cameraIntVecLoc, fPos.x, fPos.y, fPos.z);
}

glm :: ivec3 Player :: getPosition(){return intPos;}
void Player :: processInput(GLFWwindow* window, float dt){cam.processInput(window, fPos, intPos, dt);}

void Player :: mouseClickCallback(GLFWwindow* window, int button, int action, int mods){
    if(action == GLFW_PRESS){
        if(button == GLFW_MOUSE_BUTTON_LEFT){
            lookDirection = cam.CameraFront;
            fPos = cam.CameraFPos;
            intPos = cam.CameraIPos;
            LClick();
        }
        else if(button == GLFW_MOUSE_BUTTON_MIDDLE){
            lookDirection = cam.CameraFront;
            fPos = cam.CameraFPos;
            intPos = cam.CameraIPos;
            MClick();
        }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT){
            lookDirection = cam.CameraFront;
            fPos = cam.CameraFPos;
            intPos = cam.CameraIPos;
            RClick();
        }
    }
}

void Player :: mouse_callback(GLFWwindow* window, double xpos, double ypos){
    cam.mouse_callback(window, xpos, ypos);
}
void Player :: scroll_callback(GLFWwindow* window, double xOff, double yOff){
    cam.mouse_callback(window, xOff, yOff);
}

bool Player :: RClick(){
    raycastReturnStruct raycast = raycaster.unitVoxelRaycast(intPos, fPos, lookDirection);
    if(raycast.blockType != Blocks :: AIR){
        return World :: world -> breakBlock(raycast.pos);
    }
    return false;
}
bool Player :: LClick(){
    raycastReturnStruct raycast = raycaster.unitVoxelRaycast(intPos, fPos, lookDirection);
    if(raycast.blockType != Blocks :: AIR){
       return  World :: world -> placeBlock(raycast.pos + glm :: ivec3(raycast.normal), raycast.blockType);
    }
    return false;
}
bool Player :: MClick(){
    raycastReturnStruct raycast = raycaster.unitVoxelRaycast(intPos, fPos, lookDirection);
    if(raycast.blockType != Blocks :: AIR){heldBlock = raycast.blockType; return true;}
    return false;
}