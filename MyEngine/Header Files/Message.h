//
//  Message.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 08/12/2025.
//
#pragma once
#include <iostream>

enum class MessageType{
    LoadMesh,
    MeshLoaded
};

struct Message{
    MessageType type;
    virtual ~Message() = default;
};

struct LoadMeshMessage : public Message
{
    std::string path;

    LoadMeshMessage(const char* p)
    {
        type = MessageType::LoadMesh;
        path = p;
    }
};

struct MeshLoadedMessage : public Message
{
    uint32_t meshID;
    std::string path;

    MeshLoadedMessage(uint32_t id, const char* p)
    {
        type = MessageType::MeshLoaded;
        meshID = id;
        path = p;
    }
};
