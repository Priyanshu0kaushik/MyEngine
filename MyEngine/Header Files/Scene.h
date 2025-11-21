//
//  Scene.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 30/10/2025.
//

#pragma once
#include <memory>
#include <vector>
#include "ECS/Coordinator.h"
#include "RenderSystem.h"

class Shader;
class Camera;
class Scene{
public:
    Scene(Coordinator& coordinator, std::shared_ptr<RenderSystem> rs)
            : m_Coordinator(coordinator), renderSystem(rs) {}
    
    Entity AddEntity(char* aName, uint32_t meshID, std::shared_ptr<Texture> texture = nullptr);
    void RemoveEntity(Entity e);

    void Render(Shader& aShader);
    void RenameEntity(Entity e, const char* newName);

private:
    int NameExistCount(Entity e, const char* aName);

    Coordinator& m_Coordinator;

    Camera* m_Camera;
    std::shared_ptr<RenderSystem> renderSystem;
};
