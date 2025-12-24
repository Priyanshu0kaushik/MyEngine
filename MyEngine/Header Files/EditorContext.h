//
//  EditorContext.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 10/11/2025.
//

#pragma once
#include "imgui.h"
#include "ECS/Coordinator.h"
#include "UI/UIPanel.h"

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
    void DisplayFPS();
private:
    ImGuiIO* io;
    EngineContext* m_EngineContext = nullptr;
    Entity m_SelectedEntity;
    Coordinator* m_Coordinator;
    
    std::vector<UIPanel*> UIPanels;
    
    bool bCameraCapturing = false;

    EditorDrawContext context;
};
