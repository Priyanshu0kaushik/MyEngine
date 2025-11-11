//
//  Triangle.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 29/10/2025.
//
#pragma once
#include "Renderable.h"

class Triangle : public Renderable{
public:
    Triangle();
    ~Triangle();
    void Render(Shader& shader) override;
private:
    unsigned int VAO, VBO;
};
