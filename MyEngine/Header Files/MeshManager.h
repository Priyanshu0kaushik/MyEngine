//
//  MeshManager.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 18/11/2025.
//

#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include "MeshData.h"
#include "MessageQueue.h"

class MeshManager {
public:
    MeshManager();
    static void PrintMemory();
    
    uint32_t LoadMesh(const std::string& path);
    Mesh* GetMesh(uint32_t meshID);
    void TriangulateFace(const std::vector<int>& polygonIndices, std::vector<Face>& outFaces);

    std::unordered_map<std::string, uint32_t>& GetAllMeshes(){return m_PathToID;}
    
private:
    uint32_t CreateMesh(const Mesh& meshData);
    void UploadToGPU(Mesh& mesh);
    
    bool SaveMeshBinary(const std::string& path, const Mesh& mesh);
    bool LoadMeshBinary(const std::string& path, Mesh& outMesh);
    
private:

    std::unordered_map<uint32_t, Mesh> m_Meshes;
    uint32_t m_NextMeshID = 1;
    
    std::unordered_map<std::string, uint32_t> m_PathToID;
};
