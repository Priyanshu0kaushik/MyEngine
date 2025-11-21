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

class MeshManager {
public:
    MeshManager();
    static void Allocate();
    static MeshManager& Get();
    
    static void DeAllocate();
    
    uint32_t LoadMesh(const std::string& path);
    Mesh& GetMesh(uint32_t meshID);
    void TriangulateFace(const std::vector<int>& polygonIndices, std::vector<Face>& outFaces);

private:
    uint32_t CreateMesh(const Mesh& meshData);
    void UploadToGPU(Mesh& mesh);

private:
    static MeshManager* instance;
    
    std::vector<Mesh> s_Meshes;
    std::unordered_map<std::string, uint32_t> s_PathToID;
};
