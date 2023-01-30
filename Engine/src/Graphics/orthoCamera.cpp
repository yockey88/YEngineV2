#include "engine.hpp"

#include "Graphics/orthoCamera.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

namespace Y {
namespace graphics {

    void OrthoCamera::RecalculateProjMatrix() {
        float halfW = m_Pos.z * m_AspectRatio * 0.5f;
        float halfH = m_Pos.z * 0.5f;

        m_ProjMatrix = glm::ortho(-1 * halfW , halfW , -1 * halfH , halfH , m_Close , m_Far);

        return;
    }

    OrthoCamera::OrthoCamera() 
      : m_ProjMatrix(1.f) , m_ViewMatrix(1.f) , m_AspectRatio(16.f / 9.f) , 
        m_Close(0.1f) , m_Far(100.f) {

        RecalculateProjMatrix();

    }   

    OrthoCamera::OrthoCamera(const OrthoCamera& other)
      : m_ProjMatrix(other.m_ProjMatrix) , m_ViewMatrix(other.m_ViewMatrix) , m_AspectRatio(other.m_AspectRatio) ,
        m_Pos(other.m_Pos) , m_Close(other.m_Close) , m_Far(other.m_Far) {
        
        RecalculateProjMatrix();

    }

    void OrthoCamera::SetPos(const glm::vec3& pos) {

        if (m_Pos != pos) {
            m_Pos = pos;
            RecalculateProjMatrix();
        }

        return;
    } 

    void OrthoCamera::CalcViewMat(const glm::vec3& pos , float rot) {

        if (m_Pos != pos || m_Rotation != rot) {
            m_Pos = pos;
            m_Rotation = rot;

            glm::mat4 view = glm::mat4(1.f);
            view = glm::translate(view , pos);
            view = glm::rotate(view , glm::radians(rot) , glm::vec3(0 , 0 , 1));
            view = glm::inverse(view);
            SetViewMat(view);
        }

        return;
    }

    void OrthoCamera::SetClose(float c) {
        
        if (m_Close != c) {
            m_Close = c;
            RecalculateProjMatrix();
        }

        return;
    }

    void OrthoCamera::SetFar(float f) {
        
        if (m_Far != f) {
            m_Far = f;
            RecalculateProjMatrix();
        }

        return;
    }

    void OrthoCamera::SetHeight(float h) {
        
        if (m_Pos.z != h) {
            m_Pos.z = h;
            CalcViewMat(m_Pos , m_Rotation);
            RecalculateProjMatrix();
        }

        return;
    }

    void OrthoCamera::SetAspectRatio(float ar) {

        if (m_AspectRatio != ar) {
            m_AspectRatio = ar;
            RecalculateProjMatrix();
        }

        return;
    }

    void OrthoCamera::SetRotation(float r) {

        if (m_Rotation != r) {
            m_Rotation = r;
            CalcViewMat(m_Pos , m_Rotation);
        }

        return;
    }


}
}