#ifndef ORTHO_CAMERA_HPP
#define ORTHO_CAMERA_HPP

#include "glm/glm.hpp"

namespace Y {
namespace graphics {

    class OrthoCamera {
        
        glm::vec3 m_Pos;
        glm::mat4 m_ProjMatrix;
        glm::mat4 m_ViewMatrix;

        float m_Close , m_Far;
        float m_AspectRatio , m_Rotation;

        void RecalculateProjMatrix();
        
        public:
            OrthoCamera();
            OrthoCamera(const OrthoCamera& other);

            void SetPos(const glm::vec3& pos);
            void CalcViewMat(const glm::vec3& pos , float rot);
            inline void SetViewMat(const glm::mat4& matrix) { m_ViewMatrix = matrix; }

            void SetClose(float close);
            void SetFar(float Far); 
            void SetHeight(float height);
            void SetAspectRatio(float aspectRatio);
            void SetRotation(float rotation);

            inline glm::vec3 GetPos() const { return m_Pos; }
            const glm::mat4& GetProjMatrix() const { return m_ProjMatrix; }
            const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

            inline float GetAspectRatio() const { return m_AspectRatio; }
            inline float GetRotation() const { return m_Rotation; }
            inline float GetNear() const { return m_Close; }
            inline float GetFar() const { return m_Far; }
    };

}
}

#endif
