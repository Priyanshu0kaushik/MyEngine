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

EditorContext::EditorContext(){
    
}

void EditorContext::Init(GLFWwindow* aWindow, EngineContext* engine){
    if(engine) m_EngineContext = engine;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    // Enable docking
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // Optionally enable multi-viewport (separate OS windows)
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark(); // or StyleColorsClassic()

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
    //Editor Stuff
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

    // Make sure ImGui knows your window size
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

    ImGui::End();
}
void EditorContext::ShowHierarchy(){
    ImGui::Begin("Hierarchy");
    std::vector<std::unique_ptr<Renderable>>& renderables = m_EngineContext->GetScene()->GetRenders();
    for (size_t i = 0; i < renderables.size(); i++)
    {
        Renderable* r = renderables[i].get();

        std::string label = r->GetName();

        // Selectable item
        bool isSelected = (m_SelectedRenderable == r);
        if (ImGui::Selectable(label.c_str(), isSelected))
        {
            m_SelectedRenderable = r; // select this one
            
        }
        if (ImGui::BeginPopupContextItem("object_context_menu")) {
            if (ImGui::MenuItem("Delete")) {
                if(m_EngineContext){
                    m_EngineContext->DeleteRenderable(r);
                    m_SelectedRenderable = nullptr;
                }
            }
            ImGui::EndPopup();
        }

    }
    if (ImGui::Button("Add Cube")) {
        m_EngineContext->CreateCube("Cube ");
    }
    ImGui::End();
}

void EditorContext::DrawInspector()
{
    ImGui::Begin("Inspector");

    if (m_SelectedRenderable)
    {
        glm::vec3 pos = m_SelectedRenderable->GetPosition();
        if (ImGui::DragFloat3("Position", &pos.x, 0.1f))
            m_SelectedRenderable->SetPosition(pos);

        glm::vec3 rot = m_SelectedRenderable->GetRotation();
        if (ImGui::DragFloat3("Rotation", &rot.x, 0.1f))
            m_SelectedRenderable->SetRotation(rot);

        glm::vec3 scale = m_SelectedRenderable->GetScale();
        if (ImGui::DragFloat3("Scale", &scale.x, 0.1f, 0.01f, 10.0f))
            m_SelectedRenderable->SetScale(scale);
    }

    ImGui::End();
}
