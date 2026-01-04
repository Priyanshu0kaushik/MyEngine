//
//  ContentBrowserPanel.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 04/01/2026.
//

#pragma once
#include "UIPanel.h"
#include <filesystem>
#include "AssetManager.h"

class ContentBrowserPanel: public UIPanel
{
public:
    virtual void Init(EditorDrawContext& context) override;
    virtual void Draw(EditorDrawContext& context) override;
private:
    void OnItemRightClick();
    void ShowItems();
    void OnContentBrowserRightClick();
    void OnItemDeletePressed();
    
    std::filesystem::path s_PathToDelete;

    TextureData FolderIcon, FileIcon;
    std::filesystem::path m_CurrentDirectory;
};
