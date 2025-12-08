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
#include <sys/sysctl.h>
#include <mach/mach.h>



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
    if (m_PathToID.find(path) != m_PathToID.end())
        return m_PathToID[path];

    std::string binPath = path + ".asset";
    Mesh meshData;

    if (std::filesystem::exists(binPath))
    {
        std::cout<<"BinaryLoading"<< std::endl;
        LoadMeshBinary(binPath, meshData);
        uint32_t id = CreateMesh(meshData);
        m_PathToID[path] = id;
        return id;
    }
    else{
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
                    TriangulateFace(polygonIndices, meshData.faces);
                    
                }
            }
        }

        file.close();
        std::string binPath = path + ".asset";
        SaveMeshBinary(binPath, meshData);
    }

    
    uint32_t id = CreateMesh(meshData);
    m_PathToID[path] = id;
    return id;
}

uint32_t MeshManager::CreateMesh(const Mesh& meshData)
{
    m_Meshes.push_back(meshData);
    return (uint32_t)m_Meshes.size() - 1;
}

Mesh& MeshManager::GetMesh(uint32_t meshID)
{
    return m_Meshes[meshID];
}

void MeshManager::TriangulateFace(const std::vector<int> &polygonIndices, std::vector<Face> &outFaces){
    if (polygonIndices.size() < 3)
        return;

    for (size_t i = 1; i + 1 < polygonIndices.size(); ++i)
    {
        Face face;
        face.vertexIndices.push_back(polygonIndices[0]);
        face.vertexIndices.push_back(polygonIndices[i]);
        face.vertexIndices.push_back(polygonIndices[i + 1]);
        outFaces.push_back(face);
    }
}

void MeshManager::PrintMemory()
{
    int mib [] = { CTL_HW, HW_MEMSIZE };
    uint64_t totalMem = 0;
    size_t len = sizeof(totalMem);
    
    if(-1 == sysctl(mib, 2, &totalMem, &len, NULL, 0))
    {
        std::cerr << "Failed to get total memory.\n";
        return;
    }
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
    vm_statistics64_data_t vmstat;

    if (host_statistics64(mach_host_self(),
                          HOST_VM_INFO64,
                          (host_info64_t)&vmstat,
                          &count) != KERN_SUCCESS)
    {
        std::cerr << "Failed to get VM statistics.\n";
        return;
    }
    
    uint64_t pageSize = 0;
    len = sizeof(pageSize);
    sysctlbyname("hw.pagesize", &pageSize, &len, NULL, 0);

    uint64_t freeMem  = (vmstat.free_count + vmstat.inactive_count) * pageSize;
    uint64_t usedMem  = totalMem - freeMem;

//    uint64_t virtualMemUsed = vmstat.internal_page_count * pageSize;
    uint64_t virtualMemFree = vmstat.free_count * pageSize;

    std::cout << "There is "
              << freeMem / (1024 * 1024)
              << " MB of physical memory available.\n";

    std::cout << "There is "
              << virtualMemFree / (1024 * 1024)
              << " MB of virtual memory free.\n";

    std::cout << "Total physical memory: "
              << totalMem / (1024 * 1024)
              << " MB\n";

    std::cout << "Used physical memory: "
              << usedMem / (1024 * 1024)
              << " MB\n";
}

bool MeshManager::SaveMeshBinary(const std::string &path, const Mesh &mesh)
{
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open())
    {
        std::cout << "Failed to save mesh: " << path << std::endl;
        return false;
    }

    uint32_t vertexCount = (uint32_t)mesh.vertices.size();
    out.write((char*)&vertexCount, sizeof(uint32_t));
    
    out.write((char*)mesh.vertices.data(), vertexCount * sizeof(Vertex));

    
    uint32_t faceCount = (uint32_t)mesh.faces.size();
    out.write((char*)&faceCount, sizeof(uint32_t));

    
    for (const Face& face : mesh.faces)
    {
        uint32_t indexCount = (uint32_t)face.vertexIndices.size();
        out.write((char*)&indexCount, sizeof(uint32_t));
        out.write((char*)face.vertexIndices.data(),
                  indexCount * sizeof(int));
    }

    out.close();
    
    return true;
}

bool MeshManager::LoadMeshBinary(const std::string &path, Mesh &outMesh)
{
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open())
    {
        std::cout << "Failed to load mesh binary: " << path << std::endl;
        return false;
    }
    
    outMesh.vertices.clear();
    outMesh.faces.clear();

    uint32_t vertexCount = 0;
    in.read((char*)&vertexCount, sizeof(uint32_t));

    outMesh.vertices.resize(vertexCount);
    in.read((char*)outMesh.vertices.data(),
            vertexCount * sizeof(Vertex));

    uint32_t faceCount = 0;
    in.read((char*)&faceCount, sizeof(uint32_t));

    for (uint32_t i = 0; i < faceCount; i++)
    {
        Face face;

        uint32_t indexCount = 0;
        in.read((char*)&indexCount, sizeof(uint32_t));

        face.vertexIndices.resize(indexCount);
        in.read((char*)face.vertexIndices.data(),
                indexCount * sizeof(int));

        outMesh.faces.push_back(face);
    }

    in.close();
    return true;
}
