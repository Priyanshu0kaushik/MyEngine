//
//  Camera.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 08/11/2025.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GLFWwindow;
class Camera{
public:
    Camera();
    
    void SetPosition(const glm::vec3& pos);
    void LookAt(const glm::vec3& target, const glm::vec3& up);
    
    glm::mat4 GetView() const;
    glm::mat4 GetProjection() const;
    
    glm::vec3 GetPostion() const{ return m_CameraPos;}
    
    void SetFov(float aFov){ m_Fov = aFov;}
    void SetAspectRatio(float aRatio){ m_AspectRatio = aRatio;}
    void SetAspectRatio(float width, float height){ m_AspectRatio = width/height;}
    void SetNearFar(float aNear, float aFar){ m_Near = aNear; m_Far = aFar;}
    void OnReleaseCamControl();
    void ProcessInput(GLFWwindow* aWindow, float aDeltaTime);
    void ProcessMouseScroll(double yoffset);

private:
    void ProcessKeyboardInput(GLFWwindow* aWindow, float aDeltaTime);
    void ProcessMouseInput(GLFWwindow* aWindow, float aDeltaTime);


private:
    glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    
    float m_Fov = 45.f;
    float m_AspectRatio = 1280.f/720.f;
    float m_Near = 0.1f;
    float m_Far = 100.f;
    
    float m_Yaw = -90.0f;
    float m_Pitch = 0.0f;
    
    bool bFirstMouse = true;

    

};
