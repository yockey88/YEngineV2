#include "engine.hpp"

#include "Graphics/perspectiveCamera.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

namespace Y {
namespace graphics {

    void PerspectiveCamera::RecalculateProjMatrix() {

        int width = Y_WINDOW.GetSize().x;
        int height = Y_WINDOW.GetSize().y;

        m_ProjMatrix = glm::perspective(glm::radians(m_Fov) , (float)width / (float)height , m_Close , m_Far);

    }

    void PerspectiveCamera::RecalculateViewMatrix() {

        glm::mat4 view = glm::mat4(1.f);
        view = glm::lookAt(m_Pos , (m_Pos + m_Forward) , m_Up);
        SetViewMat(view);

    }

    PerspectiveCamera::PerspectiveCamera()
        : m_ProjMatrix(1.f) , m_ViewMatrix(1.f) , m_Forward({ 0.f , 0.f , -1.f }) , m_Up({ 0.f , 1.f , 0.f }) , m_Pos({ 0.f , 0.f , 20.f }) ,
        m_Close(0.1f) , m_Far(100.f) , m_Pitch(0.f) , m_Yaw(0.f) , m_Roll(0.f) , m_Fov(90.f) {

        RecalculateProjMatrix();
        RecalculateViewMatrix();

    }

    PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& other) : m_ProjMatrix(other.m_ProjMatrix) , m_ViewMatrix(other.m_ViewMatrix) ,
        m_Forward(other.m_Forward) , m_Up(other.m_Up) , m_Pos(other.m_Pos) , m_Close(other.m_Close) ,
        m_Far(other.m_Far) , m_Pitch(other.m_Pitch) , m_Yaw(other.m_Yaw) , m_Roll(0.f) , m_Fov(other.m_Fov) {
        
        RecalculateProjMatrix();
        RecalculateViewMatrix();

    }

    void PerspectiveCamera::SetPos(const glm::vec3& pos) {

        if (m_Pos != pos) {
            m_Pos = pos;
            RecalculateViewMatrix();
        }

        return;
    }
    
    void PerspectiveCamera::SetForward(const glm::vec3& forward) {
        
        if (m_Forward != forward) {
            m_Forward = forward;  
            RecalculateViewMatrix();
        }

    }

    void PerspectiveCamera::SetUp(const glm::vec3& up) {

        if (m_Up != up) {
            m_Up = up;  
            RecalculateViewMatrix();
        }

    }

    void PerspectiveCamera::CalcViewMat(const glm::vec3& pos , const glm::vec3& forward , const glm::vec3& up) {

        if (m_Pos != pos || m_Forward != forward || m_Up != up) {
            m_Pos = pos;
            m_Forward = forward;
            m_Up = up;
            RecalculateViewMatrix();
        }
        

        return;
    }

    void PerspectiveCamera::SetClose(float close) {

        if (m_Close != close) {
            m_Close = close;
            RecalculateProjMatrix();
        }

        return;
    
    }

    void PerspectiveCamera::SetFar(float Far) {
    
        if (m_Far != Far) {
            m_Far = Far;
            RecalculateProjMatrix();
        }

        return;
        
    }

    void PerspectiveCamera::SetPitch(float pitch) {

        if (m_Pitch != pitch) {
            m_Pitch = pitch;
            RecalculateViewMatrix();
        }

        return;
    
    }

    void PerspectiveCamera::SetYaw(float yaw) {

        if (m_Yaw != yaw) {
            m_Yaw = yaw;
            RecalculateViewMatrix();
        }

        return;
    
    }

    void PerspectiveCamera::SetRoll(float roll) {

        if (m_Roll != roll) {
            m_Roll = roll;
            RecalculateViewMatrix();
        }

        return;
    
    }

    void PerspectiveCamera::SetFov(float fov) {

        if (m_Fov != fov) {
            m_Fov = fov;
            RecalculateProjMatrix();
        }

        return;
    
    }

}
}