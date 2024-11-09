#pragma once

#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

struct Layer{
    GLubyte y;
    vector<GLubyte> data;

    Layer(GLubyte newY){y = newY; data = vector<unsigned char>(256, (unsigned char)0);};
};