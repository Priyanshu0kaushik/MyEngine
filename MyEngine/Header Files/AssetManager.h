//
//  AssetManager.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 02/01/2026.
//

#pragma once
#include "TextureManager.h"
#include "MeshManager.h"
#include "MessageQueue.h"
#include "AssetTypes.h"

class AssetManager{
public:
    static void Allocate();
    static AssetManager& Get();
    static void DeAllocate();

    TextureManager& GetTextureManager() { return m_TextureManager; }
    MeshManager& GetMeshManager() { return m_MeshManager; }
    
    uint32_t LoadAsset(const std::string& path);
    void ProcessMessage(Message* msg);
    void SetMessageQueue(std::shared_ptr<MessageQueue> q) { messageQueue = q; }
    
private:
    AssetType GetAssetTypeFromExtension(const std::string& path);
private:
    static AssetManager* m_Instance;
    std::shared_ptr<MessageQueue> messageQueue;

    TextureManager m_TextureManager;
    MeshManager m_MeshManager;
};
