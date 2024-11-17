#pragma once

#include <GLFW/glfw3.h>
#include <vector>

using namespace std;


/**
 * @brief The struct that stores a layer of a chunk at a given y value. Stores its y value and a layer of block types. 
 */
struct Layer{
    GLubyte y;
    vector<GLubyte> data;

    Layer(GLubyte newY){y = newY; data = vector<unsigned char>(256, (unsigned char)0);};
};