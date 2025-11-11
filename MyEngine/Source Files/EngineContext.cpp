//
//  EngineContext.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 03/11/2025.
//

#include "EngineContext.h"
#include "Scene.h"
#include "EditorContext.h"
#include "Camera.h"
#include "Cube.h"


EngineContext::EngineContext(int width, int height, const char* title){
    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW");

    //GLFW Window
    InitWindow(width, height, title);
    
    //ImGUI
    m_EditorContext = new EditorContext();
    m_EditorContext->Init(m_Window, this);
    
    m_Scene = new Scene();
    m_Camera = new Camera();
}

void EngineContext::InitWindow(int width, int height, const char* title){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(m_Window);

    /* IMPORTANT: Load GLAD (after context is created) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    glEnable(GL_DEPTH_TEST);

}


void EngineContext::Draw(){
    while (!glfwWindowShouldClose(m_Window))
    {
        m_EditorContext->BeginFrame();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if(m_Shader && m_Camera){
            m_Shader->SetMatrix4(m_Camera->GetView(), "view");
            m_Shader->SetMatrix4(m_Camera->GetProjection(), "projection");
        }

        if(m_Scene && m_Scene){
            m_Shader->Use();
            m_Scene->Render(*m_Shader);
        }
        
        // ImGUI
        m_EditorContext->Render();
        
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void EngineContext::Cleanup(){
    delete m_Camera;
    delete m_Scene;
    delete m_EditorContext;
}

void EngineContext::CreateCube(const char *Name){
    if(!m_Scene) return;
    std::unique_ptr<Cube> cube = std::make_unique<Cube>();
    cube->Rename(Name);
    m_Scene->AddRenderable(std::move(cube));
}

void EngineContext::DeleteRenderable(Renderable* aRenderable){
    if(m_Scene) m_Scene->RemoveRenderable(aRenderable);
}

void EngineContext::Shutdown(){
    m_EditorContext->EndFrame();
    Cleanup();
    glfwTerminate();
}
