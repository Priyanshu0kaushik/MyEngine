//
//  Camera.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 08/11/2025.
//

#include "Camera.h"

Camera::Camera(){
    m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    m_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::SetPosition(const glm::vec3& pos){
    m_CameraPos = pos;
}

void Camera::LookAt(const glm::vec3& target, const glm::vec3& up){
    m_CameraTarget = target;
    m_Up = up;
}

glm::mat4 Camera::GetView() const{
    return glm::lookAt(m_CameraPos, m_CameraTarget, m_Up);
}
glm::mat4 Camera::GetProjection() const{
    return glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_Near, m_Far);
}
