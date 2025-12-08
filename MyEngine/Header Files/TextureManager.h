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

class TextureManager
{
public:
    TextureManager();
    static void Allocate();
    static TextureManager& Get();
    static void DeAllocate();
    
    uint32_t LoadTexture(const char* path);
    TextureData& GetTexture(uint32_t textureId);
    
    std::unordered_map<std::string, uint32_t>& GetAllTextures(){return m_PathToID;}

private:
    uint32_t CreateTexture(const TextureData& textureData);
private:
    static TextureManager* instance;
    
    std::vector<TextureData> m_Textures;
    std::unordered_map<std::string, uint32_t> m_PathToID;

};
