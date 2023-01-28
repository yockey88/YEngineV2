#include "engine.hpp"

#include "Graphics/camera.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

namespace Y {
namespace graphics {

    void Camera::recalculateProjMatrix() {
        float halfW = height * aspectRatio * 0.5f;
        float halfH = height * 0.5f;

        orthoProjMatrix = glm::ortho(-1 * halfW , halfW , -1 * halfH , halfH , close , mFar);

        return;
    }

    Camera::Camera() 
      : orthoProjMatrix(1.f) , viewMatrix(1.f) , aspectRatio(16.f / 9.f) , 
      height(1080.f) , close(0.1f) , mFar(100.f) {

        recalculateProjMatrix();

    }   

    Camera::Camera(const Camera& other)
      : orthoProjMatrix(other.orthoProjMatrix) , viewMatrix(other.viewMatrix) , aspectRatio(other.aspectRatio) ,
        height(other.height) , close(other.close) , mFar(other.mFar) {
        
        recalculateProjMatrix();

    }

    void Camera::setAspectRatio(float ar) {

        if (aspectRatio != ar) {
            aspectRatio = ar;
            recalculateProjMatrix();
        }

        return;
    }

    void Camera::setHeight(float h) {
        
        if (height != h) {
            this->height = h;
            this->pos.z = h;
            recalculateProjMatrix();
        }

        return;
    }

    void Camera::setNear(float c) {
        
        if (close != c) {
            close = c;
            recalculateProjMatrix();
        }

        return;
    }

    void Camera::setFar(float f) {
        
        if (mFar != f) {
            mFar = f;
            recalculateProjMatrix();
        }

        return;
    }

    void Camera::setPos(const glm::vec3& pos) {

        if (this->pos != pos) {
            this->pos = pos;
            this->height = pos.z;
            recalculateProjMatrix();
        }

        return;
    } 

    void Camera::setViewMat(const glm::vec3& pos , float rot) {

        glm::mat4 view = glm::mat4(1.f);
        view = glm::translate(view , pos);
        view = glm::rotate(view , glm::radians(rot) , glm::vec3(0 , 0 , 1));
        view = glm::inverse(view);
        setViewMat(view);

        return;
    }


}
}