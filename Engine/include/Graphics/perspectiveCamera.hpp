#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "glm/glm.hpp"

namespace Y {
namespace graphics {

    class PerspectiveCamera {

        float m_Close , m_Far;
        float m_Roll , m_Pitch , m_Yaw;
        float m_Fov;

        glm::vec3 m_Pos , m_Target , m_Up;
        glm::mat4 m_PerspectiveProjMatrix;
        glm::mat4 m_ViewMatrix;

        void RecalculateProjMatrix();
        void RecalculateViewMatrix();
        public:
            PerspectiveCamera();
            PerspectiveCamera(const PerspectiveCamera& other);

            void SetPos(const glm::vec3& pos);
            void SetTarget(const glm::vec3& target);
            void SetUp(const glm::vec3& up);
            void SetViewMat(const glm::vec3& target , const glm::vec3& up);
            inline void SetViewMat(const glm::mat4& matrix) { m_ViewMatrix = matrix; }

            void SetNear(float close);
            void SetFar(float far);
            void SetRoll(float roll);
            void SetPitch(float pitch);
            void SetYaw(float yaw);
            void SetFov(float fov);

            inline glm::vec3 GetPos() const { return m_Pos; }
            inline glm::vec3 GetTarget() const { return m_Target; }
            inline glm::vec3 GetUp() const { return m_Up; }
            const glm::mat4& GetPerspectiveProjMatrix() const { return m_PerspectiveProjMatrix; }
            const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

            inline float GetNear() const { return m_Close; }
            inline float GetFar() const { return m_Far; }
            inline float GetRoll() const { return m_Roll; }
            inline float GetPitch() const { return m_Pitch; }
            inline float GetYaw() const { return m_Yaw; }
            inline float GetFov() const { return m_Fov; }
    };

}
}

#endif