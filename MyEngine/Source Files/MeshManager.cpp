//
//  MeshManager.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 18/11/2025.
//

#include "MeshManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

MeshManager* MeshManager::instance = nullptr;


MeshManager::MeshManager ()
{
    
}
void MeshManager::Allocate()
{
    assert(instance == nullptr);
    if (instance) return;
    instance = new MeshManager();
}

void MeshManager::DeAllocate(){
    delete instance;
}

MeshManager& MeshManager::Get()
{
    return *instance;
};



uint32_t MeshManager::LoadMesh(const std::string& path)
{
    if (s_PathToID.find(path) != s_PathToID.end())
        return s_PathToID[path];

    Mesh meshData;

    std::vector<glm::vec3> tempPositions;
    std::vector<glm::vec2> tempUVs;
    std::vector<glm::vec3> tempNormals;

    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cout << "Failed to load mesh: " << path << std::endl;
        return UINT32_MAX;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")
        {
            glm::vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            tempPositions.push_back(pos);
        }
        else if (prefix == "vt")
        {
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            tempUVs.push_back(uv);
        }
        else if (prefix == "vn")
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        }

        else if (prefix == "f")
        {
            std::vector<int> polygonIndices;
            std::string vertexData;

            while (ss >> vertexData)
            {
                std::stringstream vs(vertexData);
                std::string vStr, tStr, nStr;

                std::getline(vs, vStr, '/');
                std::getline(vs, tStr, '/');
                std::getline(vs, nStr, '/');

                int vIndex = std::stoi(vStr) - 1;
                int tIndex = tStr.empty() ? -1 : std::stoi(tStr) - 1;
                int nIndex = nStr.empty() ? -1 : std::stoi(nStr) - 1;

                // construct vertex
                Vertex vert;
                vert.position = tempPositions[vIndex];
                vert.uv = (tIndex >= 0 ? tempUVs[tIndex] : glm::vec2(0.0f));
                vert.normal = (nIndex >= 0 ? tempNormals[nIndex] : glm::vec3(0, 1, 0));

                meshData.vertices.push_back(vert);

                polygonIndices.push_back((int)meshData.vertices.size() - 1);
            }

            if (polygonIndices.size() == 3)
            {
                Face face;
                face.vertexIndices = polygonIndices;
                meshData.faces.push_back(face);
            }
            else if (polygonIndices.size() > 3)
            {
                //Triangulate
            }
        }
    }

    file.close();

    uint32_t id = CreateMesh(meshData);
    s_PathToID[path] = id;
    return id;
}

uint32_t MeshManager::CreateMesh(const Mesh& meshData)
{
    s_Meshes.push_back(meshData);
    return (uint32_t)s_Meshes.size() - 1;
}

Mesh& MeshManager::GetMesh(uint32_t meshID)
{
    return s_Meshes[meshID];
}

void MeshManager::UploadToGPU(Mesh& mesh)
{
    
}
