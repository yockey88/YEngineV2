#include "engine.hpp"
#include "log.hpp"
#include "Graphics/renderCmnd.hpp"
#include "Graphics/camera.hpp"
#include "Graphics/perspectiveCamera.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"
#include "Graphics/texture.hpp"
#include "Graphics/material.hpp"

#include "glad/glad.h"

#include <iostream>

namespace Y {
namespace graphics {
namespace rendercommands {

    void RenderVertexArray::Execute() {
        std::shared_ptr<VertexArray> exVertArray = vertArray.lock();
        std::shared_ptr<Shader> exShader = shader.lock();

        Y_ASSERT(exVertArray->isValid() , "Attemtping to Execute Invalid Vertex Array");
        if (exVertArray && exShader) {
            exVertArray->bind();
            exShader->bind();

            // ToDo -> convert camera to leverage UBOs
            const auto& cam = Y_RENDERER.GetActivePerspectiveCamera();
            if (cam) {
                exShader->setUniformMat4("proj" , cam->GetPerspectiveProjMatrix());
                exShader->setUniformMat4("view" , cam->GetViewMatrix());
            }

            exShader->setUniformMat4("model" , modelMatrix);

            if (exVertArray->getEltCount() > 0) {
                glDrawElements(GL_TRIANGLES , exVertArray->getEltCount() , GL_UNSIGNED_INT , 0);
            } else {
                glDrawArrays(GL_TRIANGLE_STRIP , 0 , exVertArray->getVertCount());
            }

            exShader->unbind();
            exVertArray->unbind();
        } else {
            Y_WARN("Attempting to Render an Invalid Vertex Array");
        }

        return;
    }

    void RenderTexturedVertexArray::Execute() {
        std::shared_ptr<VertexArray> exVertArray = vertArray.lock();
        std::shared_ptr<Shader> exShader = shader.lock();
        std::shared_ptr<Texture> exText = texture.lock();

        Y_ASSERT(exVertArray->isValid() , "Attempting Render Invalid Texture Vertex Array | Did you call VertexArray::Upload()?");
        if (exVertArray && exText && exShader) {
            exVertArray->bind();
            exText->bind();
            exShader->bind();

            // ToDo -> convert camera to leverage UBOs
            const auto& cam = Y_RENDERER.GetActivePerspectiveCamera();
            if (cam) {
                exShader->setUniformMat4("proj" , cam->GetPerspectiveProjMatrix());
                exShader->setUniformMat4("view" , cam->GetViewMatrix());
            }

            exShader->setUniformMat4("model" , modelMatrix);

            if (exVertArray->getEltCount() > 0) {
                glDrawElements(GL_TRIANGLES , exVertArray->getEltCount() , GL_UNSIGNED_INT , 0);
            } else {
                glDrawArrays(GL_TRIANGLE_STRIP , 0 , exVertArray->getVertCount());
            }

            exShader->unbind();
            exText->unbind();
            exVertArray->unbind();
        } else {
            Y_WARN("Attempting to Render a Texture Vertex Array that has Invalid Data");
        }


        return;
    }

    void RenderVertexArrayMaterial::Execute() {

        std::shared_ptr<VertexArray> exVertArray = vertArray.lock();
        std::shared_ptr<Material> exMaterial = material.lock();

        Y_ASSERT(exVertArray->isValid() , "Attempting Render Invalid Texture Vertex Array | Did you call VertexArray::Upload()?");
        if (exVertArray && exMaterial) {
            exVertArray->bind();

            std::shared_ptr<Shader> exShader= exMaterial->getShader();
            std::shared_ptr<Texture> exTexture = exMaterial->getTexture();
            Y_ASSERT(exShader != nullptr , "Attempting to Execute invalid RenderVertexArrayMaterial - shader is null");

            if (exShader != nullptr) {
                exMaterial->updateShaderUniforms();
                exShader->bind();
                if (exTexture) 
                    exTexture->bind();

                // ToDo -> convert camera to leverage UBOs
                const auto& cam = Y_RENDERER.GetActivePerspectiveCamera();
                if (cam) {
                    exShader->setUniformMat4("proj" , cam->GetPerspectiveProjMatrix());
                    exShader->setUniformMat4("view" , cam->GetViewMatrix());
                }
                exShader->setUniformMat4("model" , modelMatrix);

                if (exVertArray->getEltCount() > 0) {
                    glDrawElements(GL_TRIANGLES , exVertArray->getEltCount() , GL_UNSIGNED_INT , 0);
                } else {
                    glDrawArrays(GL_TRIANGLE_STRIP , 0 , exVertArray->getVertCount());
                }
                
                if (exTexture != nullptr) 
                    exTexture->unbind();
                exShader->unbind();
            }

            exVertArray->unbind();

        } else {
            Y_WARN("Attempting to Render a Texture Vertex Array that has Invalid Data");
        }

        return;

        return;
    }

    void PushFramebuffer::Execute() {
        std::shared_ptr<Framebuffer> fb = fBuffer.lock();
        if (fb) {
            Y_RENDERER.PushFrameBuffer(fb);
        } else {
            Y_WARN("Attempting to execute PushFrameBuffer with invalid data");
        }
        return;
    }

    void PopFramebuffer::Execute() {
        Y_RENDERER.PopFrameBuffer();
        return;
    }

    void PushCamera::Execute() {
        std::shared_ptr<Camera> c = camera.lock();
        if (c) {
            Y_RENDERER.PushCamera(c);
        } else {
            Y_WARN("Attempting to execute PushFrameBuffer with invalid data");
        }
        return;
    }

    void PopCamera::Execute() {
        Y_RENDERER.PopCamera();
        return;
    }

    void PushPerspectiveCamera::Execute() {
        std::shared_ptr<PerspectiveCamera> c = camera.lock();
        if (c) {
            Y_RENDERER.PushPerspectiveCamera(c);
        } else {
            Y_WARN("Attempting to execute PushFrameBuffer with invalid data");
        }
        return;
    }

    void PopPerspectiveCamera::Execute() {
        Y_RENDERER.PopPerspectiveCamera();
        return;
    }

}
}
}