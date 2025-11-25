//
//  FragmentShader.glsl
//  MyEngine
//
//  Created by Priyanshu Kaushik on 03/11/2025.
//

#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord);
} 
