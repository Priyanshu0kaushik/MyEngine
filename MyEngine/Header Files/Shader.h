//
//  Shader.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 02/11/2025.
//

#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader{
public:
    Shader(const char* aVertexPath, const char* aFragmentPath);
    void Use();
    void SetMatrix4(glm::mat4 aMatrix, const std::string& aName);
    
    unsigned int shaderProgram;
private:
    std::string LoadShader(const char* aPath);
    unsigned int LoadVertexShader(const char* aPath);
    unsigned int LoadFragmentShader(const char* aPath);
};
