//
//  FragmentShader.glsl
//  MyEngine
//
//  Created by Priyanshu Kaushik on 03/11/2025.
//

#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;

uniform vec4 materialAmbient = vec4(1, 1, 1, 1);
uniform vec4 materialDiffuse = vec4(1, 1, 1, 1);
uniform vec4 materialSpecular = vec4(1, 1, 1, 1);
uniform float materialShininess = 32.0;

uniform vec3 light_position = vec3(10, 25, 15);
uniform vec4 light_ambient = vec4(0.2, 0.2, 0.2, 1);
uniform vec4 light_diffuse = vec4(1, 0.9, 0.8, 1);
uniform vec4 light_specular = vec4(0.9, 0.8, 0.7, 1);
uniform vec3 light_attenuation = vec3(1, 0.1, 0.001);


uniform vec3 eyePosition;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light_position - FragPos);
    vec3 viewDir = normalize(eyePosition - FragPos);
    
    vec4 texColor = texture(texture1, TexCoord);

    vec3 ambient = materialAmbient.rgb * light_ambient.rgb * texColor.rgb;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * materialDiffuse.rgb * light_diffuse.rgb * texColor.rgb;


    vec3 specular = vec3(0.0);
    if (diff > 0.0)
    {
        
        vec3 halfVector = normalize(lightDir + viewDir);
        float specAngle = max(dot(norm, halfVector), 0.0);
        float spec = pow(specAngle, materialShininess);
        
        specular = spec * materialSpecular.rgb * light_specular.rgb;
    }

    
    float distance = length(light_position - FragPos);
    float attenuation = 1.0 / (light_attenuation.x + light_attenuation.y * distance + light_attenuation.z * (distance * distance));

    vec3 result = ambient + (diffuse + specular) * attenuation;
    
    FragColor = vec4(result, 1.0);
}
