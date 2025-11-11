//
//  Texture.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 09/11/2025.
//
#pragma once

class Texture{
public:

    Texture(const char* aPath);
    
    int Width;
    int Height;
    
    unsigned int TextureObject;
};
