#include "Shaders.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

//constructor
Shader :: Shader(const char* VShaderPath, const char* FShaderPath){
    ifstream VShaderFile, FShaderFile;
    string VCodeStr, FCodeStr;

    //ensure exceptions are thrown
    VShaderFile.exceptions(ifstream :: failbit | ifstream :: badbit);
    FShaderFile.exceptions(ifstream :: failbit | ifstream :: badbit);

    try{
        //open files
        VShaderFile.open(VShaderPath);
        FShaderFile.open(FShaderPath);

        //read files
        stringstream FShaderStream, VShaderStream; //make temp streams
        VShaderStream << VShaderFile.rdbuf();
        FShaderStream << FShaderFile.rdbuf();

        //close files
        VShaderFile.close();
        FShaderFile.close();

        //make strs
        VCodeStr = VShaderStream.str();
        FCodeStr = FShaderStream.str();
    }
    catch(ifstream :: failure e){
        fprintf(stderr, "SHADER RETRIVAL FAILED\n%s\n", e.what());
    }

    //convert into const char*
    const char* VShaderCode = VCodeStr.c_str();
    const char* FShaderCode = FCodeStr.c_str();


    //vars
    GLuint VShader, FShader;
    int success;
    char infoLog[512];

    //create and compile vertex shader
    VShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VShader, 1, &VShaderCode, NULL);
    glCompileShader(VShader);

    //check success
    glGetShaderiv(VShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(VShader, 512, NULL, infoLog);
        printf("VERTEX SHADER COMPILATION FAILED\n", stderr);
    }

    //create and compile fragment shader
    FShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FShader, 1, &FShaderCode, NULL);
    glCompileShader(FShader);

    //check success
    glGetShaderiv(FShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(FShader, 512, NULL, infoLog);
        printf("FRAGMENT SHADER COMPILATION FAILED\n", stderr);
    }

    //create final program
    program = glCreateProgram();
    glAttachShader(program, VShader);
    glAttachShader(program, FShader);
    glLinkProgram(program);

    //check success
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(FShader, 512, NULL, infoLog);
        printf("SHADER PROGRAM LINKING FAILED\n", stderr);
    }

    //delete shaders
    glDeleteShader(VShader);
    glDeleteProgram(FShader);
}


//use function
void Shader :: use(){
    glUseProgram(program);
}

//set float function
void Shader :: setFloat(const string& name, float value) const{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}
//set int function
void Shader :: setInt(const string& name, int value) const{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
//set bool function
void Shader :: setBool(const string& name, bool value) const{
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

//set vec functions
void Shader :: setVec2(const string& name, vec2 value) const{
    glUniform1fv(glGetUniformLocation(program, name.c_str()), 2, value);
}
void Shader :: setVec3(const string& name, vec3 value) const{
    glUniform1fv(glGetUniformLocation(program, name.c_str()), 3, value);
}
void Shader :: setVec4(const string& name, vec4 value) const{
    glUniform1fv(glGetUniformLocation(program, name.c_str()), 4, value);
}
