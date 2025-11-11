//
//  Cube.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 03/11/2025.
//

#include "Cube.h"

Cube::Cube()
{
    MyTexture = std::make_unique<Texture>("/Users/priyanshukaushik/Projects/MyEngine/MyEngine/Assets/brick.jpg");
    float vertices[] = {
        // Positions         // Colors        // Texture Coords
        // Front face
        -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, 0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, 0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

        // Right face
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

        // Top face
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f
    };



    unsigned int indices[] =
    {
        // Front face
        0, 2, 1, 2, 0, 3,
        // Back face
        4, 6, 5, 6, 4, 7,
        // Bottom face
        8, 10, 9, 10, 8, 11,
        // Top face
        12, 14, 13, 14, 12, 15,
        // Left face
        16, 18, 17, 18, 16, 19,
        // Right face
        20, 22, 21, 22, 20, 23
    };

    indicesCount = 36;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glEnableVertexAttribArray(2); // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Cube::~Cube()
{
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (EBO) glDeleteBuffers(1, &EBO);
}

void Cube::Render(Shader& aShader)
{
    Renderable::Render(aShader);
    aShader.Use();
    if(MyTexture){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, MyTexture->TextureObject);
        glUniform1i(glGetUniformLocation(aShader.shaderProgram, "texture1"), 0);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



