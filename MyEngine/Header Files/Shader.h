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
    std::string m_VertexPath;
    std::string m_FragmentPath;
    Shader(const char* aVertexPath, const char* aFragmentPath);
    void Use();
    void SetMatrix4(glm::mat4 aMatrix, const std::string& aName);
    void Reload();
    unsigned int shaderProgram;
private:
    std::string LoadShader(const char *aPath);
    unsigned int LoadVertexShader();
    unsigned int LoadFragmentShader();
};
