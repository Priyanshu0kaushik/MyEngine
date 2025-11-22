//
//  EditorContext.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 10/11/2025.
//

#include "EditorContext.h"
#include "EngineContext.h"
#include "Scene.h"
#include "imgui.h"
#include "glad.h"
#include "glfw3.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>


EditorContext::EditorContext(){
    
}

void EditorContext::Init(GLFWwindow* aWindow, EngineContext* engine){
    if(engine) m_EngineContext = engine;
    m_Coordinator = engine->GetCoordinator();
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    // Enable docking
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // Optionally enable multi-viewport (separate OS windows)
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
//    ImGui::StyleColorsDark(); // or StyleColorsClassic()
    
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_WindowBg]         = ImVec4(0.10f, 0.105f, 0.11f, 1.00f);
    colors[ImGuiCol_Header]           = ImVec4(0.20f, 0.205f, 0.21f, 1.00f);
    colors[ImGuiCol_HeaderHovered]    = ImVec4(0.25f, 0.255f, 0.26f, 1.00f);
    colors[ImGuiCol_HeaderActive]     = ImVec4(0.30f, 0.305f, 0.31f, 1.00f);

    colors[ImGuiCol_Button]           = ImVec4(0.20f, 0.205f, 0.21f, 1.00f);
    colors[ImGuiCol_ButtonHovered]    = ImVec4(0.25f, 0.255f, 0.26f, 1.00f);
    colors[ImGuiCol_ButtonActive]     = ImVec4(0.15f, 0.150f, 0.155f, 1.00f);

    colors[ImGuiCol_FrameBg]          = ImVec4(0.20f, 0.205f, 0.21f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]   = ImVec4(0.25f, 0.255f, 0.26f, 1.00f);
    colors[ImGuiCol_FrameBgActive]    = ImVec4(0.30f, 0.305f, 0.31f, 1.00f);

    colors[ImGuiCol_Tab]              = ImVec4(0.15f, 0.150f, 0.155f, 1.00f);
    colors[ImGuiCol_TabHovered]       = ImVec4(0.38f, 0.380f, 0.385f, 1.00f);
    colors[ImGuiCol_TabActive]        = ImVec4(0.28f, 0.280f, 0.285f, 1.00f);
    colors[ImGuiCol_TabUnfocused]     = ImVec4(0.15f, 0.150f, 0.155f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.205f, 0.21f, 1.00f);
    
    colors[ImGuiCol_TitleBg]            = ImVec4(0.10f, 0.105f, 0.11f, 1.00f);
    colors[ImGuiCol_TitleBgActive]      = ImVec4(0.15f, 0.155f, 0.16f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]   = ImVec4(0.10f, 0.105f, 0.11f, 1.00f);

    // Docking
    colors[ImGuiCol_DockingPreview]     = ImVec4(0.28f, 0.280f, 0.285f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg]     = ImVec4(0.10f, 0.105f, 0.11f, 1.00f);

    // Menu bar
    colors[ImGuiCol_MenuBarBg]          = ImVec4(0.14f, 0.145f, 0.15f, 1.00f);

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(aWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    
}

void EditorContext::BeginFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static bool dockspaceOpen = true;
    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("DockSpace", &dockspaceOpen, windowFlags);
    ImGui::PopStyleVar(2);

    ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

    ImGui::End();
}
void EditorContext::Render(){
    ShowViewport();
    ShowHierarchy();
    DrawInspector();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if(io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void EditorContext::EndFrame(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EditorContext::ShowViewport(){
    ImGui::Begin("Viewport");

    ImVec2 size = ImGui::GetContentRegionAvail();
    ImGui::Image((void*)(intptr_t)m_EngineContext->GetViewportTexture(), size, ImVec2(0,1), ImVec2(1,0));
    
    bool viewportFocused = ImGui::IsWindowHovered();
    bool rightMouseDown = ImGui::IsMouseDown(ImGuiMouseButton_Right);

    if (!bCameraCapturing && viewportFocused && rightMouseDown) {
        bCameraCapturing = true;
        m_EngineContext->OnStartControlCam();
        glfwSetInputMode(m_EngineContext->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }
    else if (!rightMouseDown && bCameraCapturing) {
        bCameraCapturing = false;
        m_EngineContext->OnReleaseCamControl();
        glfwSetInputMode(m_EngineContext->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    DisplayFPS();
    ImGui::End();
}

void EditorContext::DisplayFPS(){
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    int FPS=0;
    if(m_EngineContext) FPS = m_EngineContext->GetFPS();
    std::string text = "FPS: " + std::to_string(FPS);
    ImVec2 textSize = ImGui::CalcTextSize(text.c_str());

    ImVec2 padding{20.0f,30.f};

    ImVec2 pos = ImVec2(
        windowPos.x + windowSize.x - textSize.x - padding.x,
        windowPos.y + padding.y
    );

    drawList->AddText(pos, IM_COL32(255, 255, 255, 255), text.c_str());
}

void EditorContext::ShowHierarchy(){
    ImGui::Begin("Hierarchy");
    const std::vector<Entity>& aliveEntities = m_Coordinator->GetAliveEntities();
    

    for (size_t i = 0; i < aliveEntities.size(); i++)
    {
        Entity e = aliveEntities[i];
        std::string label = "EntityNameDefault";
        if(NameComponent* nC = m_Coordinator->GetComponent<NameComponent>(e)) label = nC->Name;

        bool isSelected = (m_SelectedEntity == e);
        if (ImGui::Selectable(label.c_str(), isSelected))
        {
            SetSelectedEntity(e);
            strcpy(m_SelectedEntityName, m_Coordinator->GetComponent<NameComponent>(m_SelectedEntity)->Name.c_str());
            
        }
        if (ImGui::BeginPopupContextItem(("object_context_menu##" + std::to_string(e)).c_str())) {
            if (ImGui::MenuItem("Delete"))
            {
                if(m_EngineContext){
                    m_EngineContext->DeleteEntity(e);
                    SetSelectedEntity(UINT32_MAX);
                    
                }
            }
            ImGui::EndPopup();
        }

    }
    if (ImGui::Button("Add Cube")) {
        SetSelectedEntity(m_EngineContext->CreateCube("Cube"));
        
    }
    ImGui::End();
}

void EditorContext::DrawInspector()
{
    ImGui::Begin("Inspector");

    
    if (m_Coordinator->DoesEntityExist(m_SelectedEntity))
    {
        ImGui::Text("Name");
        RenameRender();
        TransformComponent* tc = m_Coordinator->GetComponent<TransformComponent>(m_SelectedEntity);
        if(!tc) return;
        glm::vec3 pos = tc->position;
        ImGui::Text("Position");
        if (ImGui::DragFloat3("###Position", &pos.x, 0.1f))
            tc->position=pos;

        glm::vec3 rot = tc->rotation;
        ImGui::Text("Rotation");
        if (ImGui::DragFloat3("###Rotation", &rot.x, 0.1f))
            tc->rotation = rot;

        glm::vec3 scale = tc->scale;
        ImGui::Text("Scale");
        if (ImGui::DragFloat3("###Scale", &scale.x, 0.1f, 0.01f, 10.0f))
            tc->scale = scale;
    }

    ImGui::End();
}

void EditorContext::RenameRender(){
    bool enterPressed =
        ImGui::InputText(
            "###Name",
            m_SelectedEntityName,
            IM_ARRAYSIZE(m_SelectedEntityName),
            ImGuiInputTextFlags_EnterReturnsTrue
        );
    if (enterPressed || ImGui::IsItemDeactivatedAfterEdit())
    {
        std::string trimmed = m_SelectedEntityName;
        trimmed.erase(0, trimmed.find_first_not_of(" \t\n"));
        trimmed.erase(trimmed.find_last_not_of(" \t\n") + 1);
        
        strcpy(m_SelectedEntityName, trimmed.c_str());
        NameComponent* nameComponent = m_Coordinator->GetComponent<NameComponent>(m_SelectedEntity);
        if(m_Coordinator->DoesEntityExist(m_SelectedEntity) && !trimmed.empty() &&
           trimmed !=nameComponent->Name.c_str()){
            if(m_EngineContext) m_EngineContext->GetScene()->RenameEntity(m_SelectedEntity, trimmed.c_str());
        }
        else strcpy(m_SelectedEntityName, nameComponent->Name.c_str());
    }
}

void EditorContext::SetSelectedEntity(Entity e){
    m_SelectedEntity = e;
    if(!m_Coordinator->DoesEntityExist(e)) return;
    NameComponent* nameComponent = m_Coordinator->GetComponent<NameComponent>(m_SelectedEntity);
    strcpy(m_SelectedEntityName, nameComponent->Name.c_str());
}
