//
//  Renderable.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 29/10/2025.
//
#pragma once

#include "glad.h"
#include "glfw3.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Renderable{
public:
    virtual ~Renderable() = default;
    
    virtual void Render(Shader& shader) =0;
    std::unique_ptr<Texture> MyTexture;
    glm::mat4 GetModelMatrix() const;
    void SetPosition(const glm::vec3& aPos){ m_Position = aPos;}
    void SetRotation(const glm::vec3& eulerAngles) { m_Rotation = eulerAngles; } // in radians
    void SetScale(const glm::vec3& scale) { m_Scale = scale; }
    
    glm::vec3 GetPosition(){ return m_Position;}
    glm::vec3 GetRotation(){ return m_Rotation;}
    glm::vec3 GetScale(){ return m_Scale;}
    
    void AddPositionOffset(float aOffset, const glm::vec3& axis);
    void Rotate(float angleDegrees, const glm::vec3& axis);
    void Rename(const char* newName){ m_Name = newName;}
    std::string GetName(){ return m_Name;}
    
private:
    std::string m_Name = "Object";
    glm::vec3 m_Position = glm::vec3(0.0f);
    glm::vec3 m_Rotation = glm::vec3(0.0f);
    glm::vec3 m_Scale    = glm::vec3(1.0f);
};
