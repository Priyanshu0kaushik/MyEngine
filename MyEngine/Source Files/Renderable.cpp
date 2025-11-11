//
//  Renderable.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 29/10/2025.
//

#include "Renderable.h"

void Renderable::Render(Shader &shader){
    shader.SetMatrix4(GetModelMatrix(), "transform");

}

glm::mat4 Renderable::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_Position);
    model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0,0,1));
    model = glm::scale(model, m_Scale);
    return model;
}

void Renderable::Rotate(float angleDegrees, const glm::vec3& axis){
    m_Rotation = m_Rotation + angleDegrees * axis;
}

void Renderable::AddPositionOffset(float aOffset, const glm::vec3 &axis){
    m_Position = m_Position + aOffset * axis;
}

