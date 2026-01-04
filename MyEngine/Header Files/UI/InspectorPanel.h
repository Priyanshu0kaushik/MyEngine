//
//  InspectorPanel.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 18/12/2025.
//

#pragma once
#include "UIPanel.h"

class InspectorPanel : public UIPanel{
public:
    virtual void Draw(EditorDrawContext& context) override;
    void ShowAddComponentsList();
    void ShowNameComponent();
    void ShowTransformComponent();
    void ShowMeshComponent();
    void ShowCameraComponent();
    void ShowLoadAssetButton();
    void RenameRender();

private:
    EditorDrawContext m_Context;
};
