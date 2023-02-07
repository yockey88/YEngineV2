#include "engine.hpp"
#include "Graphics/perspectiveCamera.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

namespace Y {
namespace graphics {

    void PerspectiveCamera::RecalculateProjMatrix() {
        int isw = Engine::Instance().GetWindow().GetSize().x;
        int ish = Engine::Instance().GetWindow().GetSize().y;

        float sw = (float)isw;
        float sh = (float)ish;

        glm::mat4 p = glm::mat4(1.f);
        p = glm::perspective(glm::radians(m_Fov) , sw / sh , m_Close , m_Far);
        m_PerspectiveProjMatrix = p;
    }

    void PerspectiveCamera::RecalculateViewMatrix() {
        glm::mat4 v = glm::mat4(1.f);
        v = glm::lookAt(m_Pos , m_Target , m_Up);
        SetViewMat(v);
    }

    PerspectiveCamera::PerspectiveCamera()
        : m_PerspectiveProjMatrix(glm::mat4(1.f)) , m_ViewMatrix(glm::mat4(1.f)) , m_Pos(glm::vec3(0.f , 0.f , 1.f)) , 
        m_Target(glm::vec3(0.f)) , m_Up(glm::vec3(0.f , 1.f , 0.f)) , m_Close(1.f) , m_Far(100.f) , m_Roll(0.f) , m_Pitch(0.f) , m_Yaw(1.f) , 
        m_Fov(100.f) {

        RecalculateProjMatrix();
        RecalculateViewMatrix();

    }   

    PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& other)
        : m_PerspectiveProjMatrix(other.m_PerspectiveProjMatrix) , m_ViewMatrix(other.m_ViewMatrix) , m_Pos(other.m_Pos) , 
        m_Target(other.m_Target) , m_Up(other.m_Up) , m_Close(other.m_Close) , m_Far(other.m_Far) , m_Roll(other.m_Roll) , 
        m_Pitch(other.m_Pitch) , m_Yaw(other.m_Yaw) , m_Fov(other.m_Fov) {
        
        RecalculateProjMatrix();
        RecalculateViewMatrix();

    }

    void PerspectiveCamera::SetNear(float c) {
        
        if (m_Close != c) {
            m_Close = c;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }

        return;
    }

    void PerspectiveCamera::SetFar(float f) {
        
        if (m_Far != f) {
            m_Far = f;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }

        return;
    }

    void PerspectiveCamera::SetRoll(float r) {
        
        if (m_Roll != r) {
            m_Roll = r;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }

        return;
    }

    void PerspectiveCamera::SetPitch(float p) {
        
        if (m_Pitch != p) {
            m_Pitch = p;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }

        return;
    }

    void PerspectiveCamera::SetYaw(float y) {
        
        if (m_Yaw != y) {
            m_Yaw = y;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }

        return;
    }

    void PerspectiveCamera::SetFov(float f) {
        
        if (m_Fov != f) {
            m_Fov = f;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }

        return;
    }

    void PerspectiveCamera::SetPos(const glm::vec3& pos) {

        if (m_Pos != pos) {
            m_Pos = pos;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }

        return;
    }
    
    void PerspectiveCamera::SetTarget(const glm::vec3& target) {

        if (m_Target != target) {
            m_Target = target;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }

        return;
    }

    void PerspectiveCamera::SetUp(const glm::vec3& up) {

        if (m_Up != up) {
            m_Up = up;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }

        return;
    }

    void PerspectiveCamera::SetViewMat(const glm::vec3& target , const glm::vec3& up) {
        if (m_Target != target || m_Up != up) {
            m_Target = target;
            m_Up = up;
            RecalculateProjMatrix();
            RecalculateViewMatrix();
        }
    }

}
}