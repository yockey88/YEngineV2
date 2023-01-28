#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"

namespace Y {
namespace graphics {

    class Camera {

        float aspectRatio;
        float close , mFar;
        float height;
        
        glm:: vec3 pos;
        glm::mat4 orthoProjMatrix;
        glm::mat4 viewMatrix;

        void recalculateProjMatrix();
        public:
            Camera();
            Camera(const Camera& other);

            void setPos(const glm::vec3& pos);
            void setViewMat(const glm::vec3& pos , float rot);
            inline void setViewMat(const glm::mat4& matrix) { viewMatrix = matrix; }

            void setAspectRatio(float aspectRatio);
            void setNear(float close);
            void setFar(float far);
            void setHeight(float height);

            inline glm::vec3 getPos() const { return pos; }
            const glm::mat4& getOrthoProjMatrix() const { return orthoProjMatrix; }
            const glm::mat4& getViewMatrix() const { return viewMatrix; }

            inline float getAspectRatio() const { return aspectRatio; }
            inline float getNear() const { return close; }
            inline float getFar() const { return mFar; }
            inline float getHeight() const { return height; }
    };

}
}

#endif