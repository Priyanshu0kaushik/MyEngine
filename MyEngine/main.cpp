//
//  main.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 27/10/2025.
//


#include <iostream>
#include "Header Files/Shader.h"
#include "Header Files/EngineContext.h"

int main(void)
{


    EngineContext* engineContext = new EngineContext(600,400,"MyEngine");
    
    Shader* shader = new Shader("/Users/priyanshukaushik/Projects/MyEngine/MyEngine/Shaders/VertexShader.glsl",
                                        "/Users/priyanshukaushik/Projects/MyEngine/MyEngine/Shaders/FragmentShader.glsl");
    

    engineContext->SetShader(shader);
    
    engineContext->Draw();
    engineContext->Shutdown();
    
    
    return 0;
}
