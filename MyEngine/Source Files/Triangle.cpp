//
//  Triangle.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 29/10/2025.
//

#include "Triangle.h"


Triangle::Triangle(){
    float vertices[] = {
        0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    };
    

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));
    
    glBindBuffer(GL_ARRAY_BUFFER ,0);
    glBindVertexArray(0);
}
Triangle::~Triangle(){
    if(VBO) glDeleteBuffers(1, &VBO);
    if(VAO) glDeleteVertexArrays(1, &VAO);
}

void Triangle::Render(Shader& shader){
    Renderable::Render(shader);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    
    
}
