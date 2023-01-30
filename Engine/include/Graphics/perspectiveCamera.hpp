#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "glm/glm.hpp" 

namespace Y {
namespace graphics {

    class PerspectiveCamera {
        
        glm::vec3 m_Pos , m_Forward , m_Up;
        glm::mat4 m_ProjMatrix , m_ViewMatrix;

        float m_Close , m_Far;
        float m_Pitch , m_Yaw , m_Roll , m_Fov;

        void RecalculateProjMatrix();
        void RecalculateViewMatrix();

        public:
            PerspectiveCamera();
            PerspectiveCamera(const PerspectiveCamera& other);

            // void LookAt(const glm::vec3& target , const glm::vec3& up);
            void SetPos(const glm::vec3& pos);
            void SetForward(const glm::vec3& forward);
            void SetUp(const glm::vec3& up);

            void CalcViewMat(const glm::vec3& pos , const glm::vec3& forward , const glm::vec3& up);
            inline void SetViewMat(const glm::mat4& matrix) { m_ViewMatrix = matrix; }

            void SetClose(float close);
            void SetFar(float Far);
            void SetPitch(float pitch);
            void SetYaw(float yaw);
            void SetRoll(float roll);
            void SetFov(float fov);

            inline glm::vec3 GetPos() const { return m_Pos; }
            inline glm::vec3 GetCameraForward() const { return m_Forward; }
            inline glm::vec3 GetCameraUp() const { return m_Up; }
            const glm::mat4& GetProjMatrix() const { return m_ProjMatrix; }
            const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

            inline float GetNear() const { return m_Close; }
            inline float GetFar() const { return m_Far; }
            inline float GetPitch() const { return m_Pitch; }
            inline float GetYaw() const { return m_Yaw; }
            inline float GetRoll() const { return m_Roll; }
            inline float GetFov() const { return m_Fov; }
    };

}
}

#endif