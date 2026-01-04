//
//  Message.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 08/12/2025.
//
#pragma once
#include <iostream>
#include "AssetTypes.h"

enum class MessageType {
   
    LoadAsset,
    AssetLoaded
};
struct Message{
    MessageType type;
    virtual ~Message() = default;
};

struct LoadAssetMessage : public Message {
    std::string path;
    LoadAssetMessage(const std::string& p) : path(p) { type = MessageType::LoadAsset; }
};

struct AssetLoadedMessage : public Message {
    uint32_t id;
    std::string path;
    AssetType assetType;
    
    AssetLoadedMessage(uint32_t _id, std::string _path, AssetType _type)
        : id(_id), path(_path), assetType(_type) { type = MessageType::AssetLoaded; }
};

