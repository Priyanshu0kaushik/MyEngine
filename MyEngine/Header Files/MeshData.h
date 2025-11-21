//
//  MeshData.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 19/11/2025.
//

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct Face {
    std::vector<int> vertexIndices;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};
