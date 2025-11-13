//
//  Camera.cpp
//  MyEngine
//
//  Created by Priyanshu Kaushik on 08/11/2025.
//

#include "Camera.h"
#include "glad.h"
#include "glfw3.h"

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
    return glm::lookAt(m_CameraPos, m_CameraPos + m_Front, m_Up);
}
glm::mat4 Camera::GetProjection() const{
    return glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_Near, m_Far);
}

void Camera::ProcessInput(GLFWwindow* aWindow, float aDeltaTime){
    ProcessMouseInput(aWindow, aDeltaTime);
    ProcessKeyboardInput(aWindow, aDeltaTime);
}


void Camera::ProcessKeyboardInput(GLFWwindow* aWindow ,float aDeltaTime){
    const float cameraSpeed = m_CameraSpeedVar * aDeltaTime; 
    if (glfwGetKey(aWindow, GLFW_KEY_W) == GLFW_PRESS)
        m_CameraPos += cameraSpeed * m_Front;
    if (glfwGetKey(aWindow, GLFW_KEY_S) == GLFW_PRESS)
        m_CameraPos -= cameraSpeed * m_Front;
    if (glfwGetKey(aWindow, GLFW_KEY_A) == GLFW_PRESS)
        m_CameraPos -= glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;
    if (glfwGetKey(aWindow, GLFW_KEY_D) == GLFW_PRESS)
        m_CameraPos += glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;
    if (glfwGetKey(aWindow, GLFW_KEY_E) == GLFW_PRESS)
        m_CameraPos += m_Up * cameraSpeed;
    if (glfwGetKey(aWindow, GLFW_KEY_Q) == GLFW_PRESS)
        m_CameraPos -= m_Up * cameraSpeed;
}

void Camera::ProcessMouseInput(GLFWwindow* aWindow, float aDeltaTime){
    
    static double lastX = 0.0, lastY = 0.0;

    double xpos, ypos;
    glfwGetCursorPos(aWindow, &xpos, &ypos);

    if (bFirstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        bFirstMouse = false;
    }

    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos);
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_Yaw   += xoffset;
    m_Pitch += yoffset;

    // Clamp pitch
    if (m_Pitch > 89.0f) m_Pitch = 89.0f;
    if (m_Pitch < -89.0f) m_Pitch = -89.0f;

    // Update Front vector
    m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front.y = sin(glm::radians(m_Pitch));
    m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(m_Front);
}

void Camera::OnReleaseCamControl(){
    bFirstMouse = true;

}

void Camera::ProcessMouseScroll(double yoffset){
    m_Fov -= yoffset;
    if (m_Fov < 1.0f) m_Fov = 1.0f;
    if (m_Fov > 90.0f) m_Fov = 90.0f;
}
