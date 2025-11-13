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

void Scene::RenameRenderable(Renderable* r, const char* newName){
    if(!r) return;
    std::string name(newName);
    
    int count = NameExistCount(name.c_str());
    if(count== 0) r->Rename(name.c_str());
    else{
        while(true){
            std::string suffix = "_"+std::to_string(count);
            std::string tempname = name + suffix;
            int n = NameExistCount(tempname.c_str());
            if(n == 0){
                r->Rename(tempname.c_str());
                return;
            }
            else count++;
        }
    }
}


int Scene::NameExistCount(const char* aName){
    int count = 0;
    for(auto& render : renders){
        if (render->GetName() == aName) count++;
    }
    return count;
}
