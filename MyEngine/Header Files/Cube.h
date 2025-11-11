//
//  Cube.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 03/11/2025.
//

#pragma once
#include "Renderable.h"

class Cube : public Renderable{
public:
    Cube();
    ~Cube();
    void Render(Shader& shader) override;
private:
    unsigned int VAO, VBO, EBO, indicesCount;
};

