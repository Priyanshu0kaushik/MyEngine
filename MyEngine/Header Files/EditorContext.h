//
//  EditorContext.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 10/11/2025.
//

#pragma once
#include "imgui.h"
#include "ECS/Coordinator.h"

class GLFWwindow;
class EngineContext;

class EditorContext{
public:
    EditorContext();
    void Init(GLFWwindow* window, EngineContext* engine);
    
    void BeginFrame();
    void EndFrame();
    void Render();
private:
    void ShowViewport();
    void ShowHierarchy();
    void DrawInspector();
    void RenameRender();
    void DisplayFPS();
    void SetSelectedEntity(Entity e);
private:
    ImGuiIO* io;
    EngineContext* m_EngineContext = nullptr;
    Entity m_SelectedEntity;
    Coordinator* m_Coordinator;
    char m_SelectedEntityName[128] = "Name";

    bool bCameraCapturing = false;

};
