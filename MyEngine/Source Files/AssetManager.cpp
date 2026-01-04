//
//  AssetManager.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 03/01/2026.
//

#include "AssetManager.h"
#include <filesystem>
#include <algorithm>
#include <iostream>

AssetManager* AssetManager::m_Instance = nullptr;


void AssetManager::Allocate()
{
    assert(m_Instance == nullptr);
    if (m_Instance) return;
    m_Instance = new AssetManager();
}

void AssetManager::DeAllocate(){
    delete m_Instance;
}

AssetManager& AssetManager::Get()
{
    return *m_Instance;
};


std::string ToLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

AssetType AssetManager::GetAssetTypeFromExtension(const std::string &path)
{
    std::filesystem::path filePath(path);
    if (!filePath.has_extension()) return AssetType::None;
    
    std::string ext = ToLowerCase(filePath.extension().string());
    
    if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".tga" || ext == ".bmp")
    {
        return AssetType::Texture;
    }
        
    if (ext == ".obj")
    {
        return AssetType::Mesh;
    }
    
    return AssetType::None;
}

uint32_t AssetManager::LoadAsset(const std::string& path)
{
    AssetType type = GetAssetTypeFromExtension(path);

    switch (type) {
        case AssetType::Texture:
            std::cout << "[AssetManager] Detected Texture: " << path << std::endl;
            return m_TextureManager.LoadTexture(path.c_str());

        case AssetType::Mesh:
            std::cout << "[AssetManager] Detected Mesh: " << path << std::endl;
            return m_MeshManager.LoadMesh(path.c_str());

        case AssetType::Material:
            std::cout << "[AssetManager] Detected Material: " << path << std::endl;
            
            return 0;

        default:
            std::cerr << "[AssetManager] Unknown file type: " << path << std::endl;
            return UINT32_MAX;
    }
}

void AssetManager::ProcessMessage(Message *msg)
{
    if (msg->type == MessageType::LoadAsset)
    {
        auto loadMsg = static_cast<LoadAssetMessage*>(msg);
        uint32_t assetID = LoadAsset(loadMsg->path);
        
        AssetType type = GetAssetTypeFromExtension(loadMsg->path);

        if (assetID != UINT32_MAX)
        {
            std::unique_ptr<AssetLoadedMessage> replyMsg = std::make_unique<AssetLoadedMessage>(assetID, loadMsg->path, type);
            messageQueue->Push(std::move(replyMsg));
        }
    }
}
