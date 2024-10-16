#pragma once

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <GLFW/linmath.h>

using namespace std;

class Shader{
    public:
        GLuint program;
        Shader(const char* VShaderPath, const char* FShaderPath);

        void setFloat(const string& name, float value) const;
        void setVec2(const string& name, vec2 value) const;
        void setVec3(const string& name, vec3 value) const;
        void setVec4(const string& name, vec4 value) const;
        void setInt(const string& name, int value) const;
        void setBool(const string& name, bool value) const;

        void use();
};