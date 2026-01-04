//
//  TextureManager.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 02/12/2025.
//

#pragma once
#include <cstdint>
#include "Texture.h"
#include <vector>
#include <map>
#include "MessageQueue.h"

class TextureManager
{
public:
    TextureManager();    
    uint32_t LoadTexture(const char* path);
    TextureData* GetTexture(uint32_t textureId);
    std::unordered_map<std::string, uint32_t>& GetAllTextures(){return m_PathToID;}



private:
    uint32_t CreateTexture(const TextureData& textureData);
private:

    std::unordered_map<uint32_t, TextureData> m_Textures;
    uint32_t m_NextTextureID = 1;
    std::unordered_map<std::string, uint32_t> m_PathToID;

};
