//
//  TextureManager.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 02/12/2025.
//

#include "TextureManager.h"
#include <iostream>
#include "glad.h"
#include "glfw3.h"
#include "stb_image.h"
#include <assert.h>



TextureManager* TextureManager::instance = nullptr;


TextureManager::TextureManager ()
{
    
}
void TextureManager::Allocate()
{
    assert(instance == nullptr);
    if (instance) return;
    instance = new TextureManager();
}

void TextureManager::DeAllocate(){
    delete instance;
}

TextureManager& TextureManager::Get()
{
    return *instance;
};

uint32_t TextureManager::LoadTexture(const char *path){
    if (m_PathToID.find(path) != m_PathToID.end())
        return m_PathToID[path];
    
    
    TextureData Texture;
    stbi_set_flip_vertically_on_load(true);
    int Channels = 0;
    unsigned char *data = stbi_load(path, &Texture.Width, &Texture.Height, &Channels, 0);

    glGenTextures(1, &Texture.TextureObject);
    glBindTexture(GL_TEXTURE_2D, Texture.TextureObject);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLenum format = GL_RGB;
    if (Channels == 4)
        format = GL_RGBA;
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Texture.Width, Texture.Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    uint32_t id = CreateTexture(Texture);
    m_PathToID[path] = id;
    return id;
}

uint32_t TextureManager::CreateTexture(const TextureData &textureData)
{
    uint32_t id = m_NextTextureID++;
    m_Textures[id] = textureData;
    return id;
}

TextureData* TextureManager::GetTexture(uint32_t textureId){
    if(textureId==UINT32_MAX) return nullptr;
    return &m_Textures[textureId];
}

void TextureManager::ProcessMessage(Message* msg){
    switch (msg->type)
    {
        case MessageType::LoadTexture:
        {
            auto loadMsg = static_cast<LoadTextureMessage*>(msg);
            if(!loadMsg) return;
            uint32_t id = TextureManager::Get().LoadTexture(loadMsg->path.c_str());

            messageQueue->Push(std::make_unique<TextureLoadedMessage>(id, loadMsg->path.c_str()));
            break;
        }

        case MessageType::TextureLoaded:
        {
            auto loadedMsg = static_cast<TextureLoadedMessage*>(msg);
            if(!loadedMsg) return;
            std::cout << "Texture loaded with ID: " << loadedMsg->textureID << std::endl;
            break;
        }
        default:{}
    }
}

