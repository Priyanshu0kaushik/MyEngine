//
//  Scene.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 30/10/2025.
//

#pragma once
#include <memory>
#include <vector>
#include "Renderable.h"

class Shader;
class Camera;

class Scene{
public:
    Scene();
    void AddRenderable(std::unique_ptr<Renderable> aRender);
    void RemoveRenderable(Renderable* aRender);
    std::vector<std::unique_ptr<Renderable>>& GetRenders(){
        return renders;
    }
    void Render(Shader& aShader);
private:
    Camera* m_Camera;
    std::vector<std::unique_ptr<Renderable>> renders;
};
