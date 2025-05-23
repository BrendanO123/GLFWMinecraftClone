#pragma once

#define GL_SILENCE_DEPRECATION

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <GLFW/linmath.h>

using namespace std;

/**
 * @brief The shader class used to compile, link, and interact with glfw shaders and shader programs from seperate files.
 */
class Shader{
    public:
    
        GLuint program;
        Shader(const char* VShaderPath, const char* FShaderPath);
        Shader();
        ~Shader();

        void setFloat(const string& name, float value) const;
        void setVec2(const string& name, vec2 value) const;
        void setVec3(const string& name, vec3 value) const;
        void setVec4(const string& name, vec4 value) const;
        void setInt(const string& name, int value) const;
        void setBool(const string& name, bool value) const;

        void setFloat(GLuint position, float value) const;
        void setVec2(GLuint position, vec2 value) const;
        void setVec3(GLuint position, vec3 value) const;
        void setVec4(GLuint position, vec4 value) const;
        void setInt(GLuint position, int value) const;
        void setBool(GLuint position, bool value) const;

        void use();
};