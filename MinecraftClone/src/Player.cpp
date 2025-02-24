#include "Player.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "World.h"

using namespace std;

Player :: Player(Shader newShader, float RenderDist) : shader(newShader), renderDist(RenderDist){
    ViewAndPrespectiveMatLoc = glGetUniformLocation(shader.program, "viewAndProjectionMatrix");
    cameraIntVecLoc = glGetUniformLocation(shader.program, "cameraPosI");

    intPos = cam.CameraIPos;
    fPos = cam.CameraFPos;
    lookDirection = cam.CameraFront;
    finalTransformationMatrix = glm :: identity<glm :: mat4>();
    highlighter = new BlockHighlighter(shader);
}

void Player :: updateMatrixUniforms(float ratio){
    glUniformMatrix4fv(ViewAndPrespectiveMatLoc, 1, GL_FALSE, glm::value_ptr(cam.getViewAndProjection(lookDirection, ratio, renderDist)));
    intPos = cam.CameraIPos;
    glUniform3iv(cameraIntVecLoc, 1, glm::value_ptr(intPos));
}

glm :: ivec3 Player :: getPosition(){return intPos;}
void Player :: processInput(GLFWwindow* window, float dt){cam.processInput(window, fPos, intPos, dt);}

void Player :: mouseClickCallback(GLFWwindow* window, int button, int action, int mods){
    if(action == GLFW_PRESS){
        if(button == GLFW_MOUSE_BUTTON_LEFT){
            LClick();
        }
        else if(button == GLFW_MOUSE_BUTTON_MIDDLE){
            MClick();
        }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT){
            RClick();
        }
    }
}
void Player :: highlightSelected(){
    lookDirection = cam.CameraFront;
    fPos = cam.CameraFPos;
    intPos = cam.CameraIPos;
    raycastReturnStruct raycast = raycaster.unitVoxelRaycast(intPos, fPos, lookDirection);

    highlighter->highlight(raycast.pos, raycast.blockType);
}

void Player :: mouse_callback(GLFWwindow* window, double xpos, double ypos){
    cam.mouse_callback(window, xpos, ypos);
}
void Player :: scroll_callback(GLFWwindow* window, double xOff, double yOff){
    cam.mouse_callback(window, xOff, yOff);
}

bool Player :: RClick(){
    lookDirection = cam.CameraFront;
    fPos = cam.CameraFPos;
    intPos = cam.CameraIPos;
    raycastReturnStruct raycast = raycaster.unitVoxelRaycast(intPos, fPos, lookDirection);
    if(raycast.blockType != Blocks :: AIR){
        clicks.push(clickAction(raycast, R_CLICKED));
        return true;
    }
    return false;
}
bool Player :: LClick(){
    lookDirection = cam.CameraFront;
    fPos = cam.CameraFPos;
    intPos = cam.CameraIPos;
    raycastReturnStruct raycast = raycaster.unitVoxelRaycast(intPos, fPos, lookDirection);
    if(raycast.blockType != Blocks :: AIR){
        clicks.push(clickAction(raycast, L_CLICKED));
        return true;
    }
    return false;
}
vector<bool> Player :: resolveClicks(){
    vector<bool> returnBools = vector<bool>();
    clickAction i;
    while(!clicks.empty()){
        i = clicks.front();
        clicks.pop();
        if(i.LClicked){
            returnBools.push_back(World :: world -> placeBlock(i.raycast.pos + glm :: ivec3(i.raycast.normal), heldBlock));
        }
        else{
            returnBools.push_back(World :: world -> breakBlock(i.raycast.pos));
        }
    }
    return returnBools;
}
bool Player :: MClick(){
    lookDirection = cam.CameraFront;
    fPos = cam.CameraFPos;
    intPos = cam.CameraIPos;
    raycastReturnStruct raycast = raycaster.unitVoxelRaycast(intPos, fPos, lookDirection);
    if(raycast.blockType != Blocks :: AIR){heldBlock = raycast.blockType; return true;}
    return false;
}
GLubyte Player :: getVoxel(int x, int y, int z){return World :: world->getBlock(x, y, z);}

void Player :: setRotation(glm :: vec2 r){
    cam.setRotation(r);
    lookDirection = cam.CameraFront;
}
void Player :: setPosition(glm :: ivec3 i, glm :: vec3 f){
    intPos = i; fPos = f;
    intPos += floor(fPos);
    fPos -= floor(fPos);
    cam.CameraFPos = fPos;
    cam.CameraIPos = intPos;
}
glm :: vec3 Player :: getFPosition(){return fPos;}
glm :: vec2 Player :: getRotation(){return cam.getRotation();}