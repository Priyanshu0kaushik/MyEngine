//
//  Components.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 19/11/2025.
//

#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Texture.h"


struct TransformComponent
{
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 scale = glm::vec3(1.0f);
    
    static constexpr const char* TypeName = "Transform Component";
    static constexpr const bool UniquePerEntity = true;

};

struct NameComponent
{
    std::string Name = "GameObject";
    
    static constexpr const char* TypeName = "Name Component";
    static constexpr const bool UniquePerEntity = true;
};

struct MeshComponent
{
    uint32_t meshID;
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    int indexCount = 0;
    bool uploaded = false;
    std::shared_ptr<Texture> MyTexture = nullptr;
    
    static constexpr const char* TypeName = "Mesh Component";
    static constexpr const bool UniquePerEntity = true;
};

