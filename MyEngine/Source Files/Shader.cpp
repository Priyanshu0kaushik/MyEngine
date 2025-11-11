//
//  Shader.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 02/11/2025.
//

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "glfw3.h"
#include <glm/gtc/type_ptr.hpp>

std::string Shader::LoadShader(const char *aPath){
    std::string shaderCode;
    std::ifstream shaderFile;
    
    shaderFile.open(aPath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open file: " << aPath << std::endl;
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    
    shaderFile.close();
    shaderCode = shaderStream.str();
    
    return shaderCode;
}

unsigned int Shader::LoadVertexShader(const char *aPath){
    int result;
    char Log[512];
    
    std::string shaderCodeString = LoadShader(aPath);
    const char* shaderCode = shaderCodeString.c_str();
    
    unsigned int shaderObject;

    shaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderObject, 1, &shaderCode , NULL);
    glCompileShader(shaderObject);
    
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);
    
    if(!result){
        glGetShaderInfoLog(shaderObject, 512, NULL, Log);
        std::cout<<"Failed to compile vertex shader: "<< Log << std::endl;
    }
    return shaderObject;
}

unsigned int Shader::LoadFragmentShader(const char *aPath){
    int result;
    char Log[512];
    
    std::string shaderCodeString = LoadShader(aPath);
    const char* shaderCode = shaderCodeString.c_str();
    
    unsigned int shaderObject;

    shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderObject, 1, &shaderCode , NULL);
    glCompileShader(shaderObject);
    
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);
    
    if(!result){
        glGetShaderInfoLog(shaderObject, 512, NULL, Log);
        std::cout<<"Failed to compile vertex shader: "<< Log << std::endl;
    }
    return shaderObject;
}


Shader::Shader(const char* aVertexPath, const char* aFragmentPath){
    int result;
    char Log[512];
    
    unsigned int VertexShader = LoadVertexShader(aVertexPath);
    unsigned int FragmentShader = LoadFragmentShader(aFragmentPath);
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, VertexShader);
    glAttachShader(shaderProgram, FragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    
    if(!result){
        glGetProgramInfoLog(shaderProgram, 512, NULL, Log);
        std::cout<<"Failed to compile vertex shader: "<< Log << std::endl;
    }
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}

void Shader::Use(){
    glUseProgram(shaderProgram);
}

void Shader::SetMatrix4(glm::mat4 aMatrix, const std::string& aName){
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, aName.c_str()), 1, GL_FALSE, glm::value_ptr(aMatrix));
    
}
