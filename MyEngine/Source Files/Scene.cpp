//
//  Scene.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 30/10/2025.
//
#include "Scene.h"
#include "Shader.h"

Scene::Scene(){
    
}
void Scene::AddRenderable(std::unique_ptr<Renderable> aRender){
    renders.push_back(std::move(aRender));
}

void Scene::Render(Shader& aShader){
    for (const auto& render : renders) {
        render->Render(aShader);  // use -> to access the object
    }
}

void Scene::RemoveRenderable(Renderable* aRender){
    renders.erase(std::remove_if(renders.begin(), renders.end(), [aRender](const std::unique_ptr<Renderable>& r) { return r.get() == aRender;}), renders.end());
}

