//
//  EngineContext.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 03/11/2025.
//

#include "EngineContext.h"
#include "Scene.h"
#include "Camera.h"
#include "EditorContext.h"
#include "Cube.h"


EngineContext::EngineContext(int width, int height, const char* title){
    m_Scene = new Scene();
    m_Camera = new Camera();
    
    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW");

    //GLFW Window
    InitWindow(width, height, title);
    InitViewportFramebuffer(500,500);
    //ImGUI
    m_EditorContext = new EditorContext();
    m_EditorContext->Init(m_Window, this);
    

}

void EngineContext::InitViewportFramebuffer(int width, int height){
    m_ViewportWidth = width;
    m_ViewportHeight = height;
    
    glGenFramebuffers(1, &m_ViewportFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_ViewportFBO);

    // Color texture
    glGenTextures(1, &m_ViewportTexture);
    glBindTexture(GL_TEXTURE_2D, m_ViewportTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ViewportTexture, 0);

    // Depth buffer
    glGenRenderbuffers(1, &m_ViewportRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_ViewportRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_ViewportRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Incomplete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
    
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetScrollCallback(m_Window, EngineContext::ScrollCallback);
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    glEnable(GL_DEPTH_TEST);

}

void EngineContext::OnStartControlCam(){
    bControllingCamera = true;
}

void EngineContext::OnReleaseCamControl(){
    bControllingCamera = false;
    m_Camera->OnReleaseCamControl();
}


void EngineContext::Draw(){
    while (!glfwWindowShouldClose(m_Window))
    {
        float currentFrame = glfwGetTime();
        m_DeltaTime = currentFrame - m_LastFrameTime;
        m_LastFrameTime = currentFrame;
        
        m_EditorContext->BeginFrame();

        /* Render here */
        glBindFramebuffer(GL_FRAMEBUFFER, m_ViewportFBO);
        glViewport(0, 0, m_ViewportWidth, m_ViewportHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if(bControllingCamera) m_Camera->ProcessInput(m_Window, m_DeltaTime);
        
        if(m_Shader && m_Camera){
            m_Shader->Use();
            m_Shader->SetMatrix4(m_Camera->GetView(), "view");
            m_Shader->SetMatrix4(m_Camera->GetProjection(), "projection");
        }

        if(m_Scene){
            m_Scene->Render(*m_Shader);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
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
    m_Scene->RenameRenderable(cube.get(), "Cube");
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
