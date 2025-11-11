//
//  EditorContext.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 10/11/2025.
//

#pragma once
#include "imgui.h"
class GLFWwindow;
class EngineContext;
class Renderable;

class EditorContext{
public:
    EditorContext();
    void Init(GLFWwindow* window, EngineContext* engine);
    
    void BeginFrame();
    void EndFrame();
    void Render();
private:
    void ShowHierarchy();
    void DrawInspector();
    void RenameTargetMenu();
private:
    ImGuiIO* io;
    EngineContext* m_EngineContext = nullptr;
    Renderable* m_SelectedRenderable = nullptr;
    Renderable* m_RenameTarget = nullptr;
};
