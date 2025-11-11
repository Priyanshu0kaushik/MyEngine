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
    
    ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

}
void EditorContext::Render(){
    //Editor Stuff
    ShowHierarchy();
    DrawInspector();
    RenameTargetMenu();

    
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
        if (ImGui::BeginPopupContextItem("object_context_menu")) { // <-- unique popup ID
            if (ImGui::MenuItem("Rename")) {
                ImGui::OpenPopup("Rename Object");
                m_RenameTarget = r;
            }
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
void EditorContext::RenameTargetMenu(){
    if (ImGui::BeginPopup("Rename Object")) {
        static char nameBuffer[128];
        std::cout<<"Renaming";
        ImGui::InputText("New Name", nameBuffer, IM_ARRAYSIZE(nameBuffer));
        
        if (ImGui::Button("OK")) {
            if (m_RenameTarget) {
                m_RenameTarget->Rename(nameBuffer);
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
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
