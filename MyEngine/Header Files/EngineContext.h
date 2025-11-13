//
//  EngineContext.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 03/11/2025.
//
#pragma once

#include "glad.h"
#include "glfw3.h"

class Scene;
class Shader;
class EditorContext;
class Camera;
class Renderable;

class EngineContext{
public:
    EngineContext(int width, int height, const char* title);
    void SetShader(Shader* aShader){ m_Shader = aShader;}
    Scene* GetScene(){return m_Scene;}
    Camera* GetCamera(){return m_Camera;}
    GLFWwindow* GetWindow(){return m_Window;}
    Shader* GetShader(){return m_Shader;}
    void InitViewportFramebuffer(int width, int height);
    void Draw();
    void Shutdown();
    unsigned int GetViewportTexture(){return m_ViewportTexture;}
    
    void OnStartControlCam();
    void OnReleaseCamControl();

public:
    void CreateCube(const char* Name);
    void DeleteRenderable(Renderable* aRenderable);
private:
    void InitWindow(int width, int height, const char* title);
    void Cleanup();
private:
    GLFWwindow* m_Window = nullptr;
    Scene* m_Scene = nullptr;
    Camera* m_Camera = nullptr;
    Shader* m_Shader = nullptr;
    EditorContext* m_EditorContext = nullptr;
    float m_ViewportWidth, m_ViewportHeight;
    unsigned int m_ViewportFBO, m_ViewportTexture, m_ViewportRBO;
    bool bControllingCamera = false;
    float m_DeltaTime = 0.0f;    // Time between current frame and last frame
    float m_LastFrameTime = 0.0f; // Time of last frame
};
