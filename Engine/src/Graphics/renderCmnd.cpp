#include "engine.hpp"
#include "log.hpp"
#include "Graphics/renderCmnd.hpp"
#include "Graphics/orthoCamera.hpp"
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

    void RenderPoint::Execute() {

        Y_ASSERT(vertArray->IsValid() , "Attemtping to Execute Invalid Vertex Array");
        if (vertArray && shader) {
            vertArray->Bind();
            shader->Bind();

            // ToDo -> convert camera to leverage UBOs
            const auto& cam = Y_RENDERER.GetActivePerspectiveCamera();
            if (cam) {
                shader->SetUniformMat4("proj" , cam->GetProjMatrix());
                shader->SetUniformMat4("view" , cam->GetViewMatrix());
            }

            if (vertArray->GetEltCount() > 0) {
                glDrawElements(GL_POINTS , vertArray->GetEltCount() , GL_UNSIGNED_INT , 0);
            } else {
                glPointSize((GLfloat)size);
                glDrawArrays(GL_POINTS , 0 , vertArray->GetVertCount());
            }

            shader->Unbind();
            vertArray->Unbind();
        } else {
            Y_WARN("Attempting to Render an Invalid Vertex Array");
        }

        return;
    }

    void RenderLine::Execute() {

        Y_ASSERT(vertArray->IsValid() , "Attemtping to Execute Invalid Vertex Array");
        if (vertArray && shader) {
            vertArray->Bind();
            shader->Bind();

            // ToDo -> convert camera to leverage UBOs
            const auto& cam = Y_RENDERER.GetActivePerspectiveCamera();
            if (cam) {
                shader->SetUniformMat4("proj" , cam->GetProjMatrix());
                shader->SetUniformMat4("view" , cam->GetViewMatrix());
            }

            if (vertArray->GetEltCount() > 0) {
                glDrawElements(GL_LINES , vertArray->GetEltCount() , GL_UNSIGNED_INT , 0);
            } else {
                glLineWidth((GLfloat)width);
                glDrawArrays(GL_LINES , 0 , vertArray->GetVertCount());
            }

            shader->Unbind();
            vertArray->Unbind();
        } else {
            Y_WARN("Attempting to Render an Invalid Vertex Array");
        }

        return;
    }

    void RenderVertexArray::Execute() {

        Y_ASSERT(vertArray->IsValid() , "Attemtping to Execute Invalid Vertex Array");
        if (vertArray && shader) {
            vertArray->Bind();
            shader->Bind();

            // ToDo -> convert camera to leverage UBOs
            const auto& cam = Y_RENDERER.GetActivePerspectiveCamera();
            if (cam) {
                shader->SetUniformMat4("proj" , cam->GetProjMatrix());
                shader->SetUniformMat4("view" , cam->GetViewMatrix());
            }

            shader->SetUniformMat4("model" , modelMatrix);

            if (vertArray->GetEltCount() > 0) {
                glDrawElements(GL_TRIANGLES , vertArray->GetEltCount() , GL_UNSIGNED_INT , 0);
            } else {
                glDrawArrays(GL_TRIANGLE_STRIP , 0 , vertArray->GetVertCount());
            }

            shader->Unbind();
            vertArray->Unbind();
        } else {
            Y_WARN("Attempting to Render an Invalid Vertex Array");
        }

        return;
    }

    void RenderTexturedVertexArray::Execute() {

        Y_ASSERT(vertArray->IsValid() , "Attempting Render Invalid Texture Vertex Array | Did you call VertexArray::Upload()?");
        if (vertArray && texture && shader) {
            vertArray->Bind();
            texture->bind();
            shader->Bind();

            // ToDo -> convert camera to leverage UBOs
            const auto& cam = Y_RENDERER.GetActivePerspectiveCamera();
            if (cam) {
                shader->SetUniformMat4("proj" , cam->GetProjMatrix());
                shader->SetUniformMat4("view" , cam->GetViewMatrix());
            }

            shader->SetUniformMat4("model" , modelMatrix);

            if (vertArray->GetEltCount() > 0) {
                glDrawElements(GL_TRIANGLES , vertArray->GetEltCount() , GL_UNSIGNED_INT , 0);
            } else {
                glDrawArrays(GL_TRIANGLE_STRIP , 0 , vertArray->GetVertCount());
            }

            shader->Unbind();
            texture->unbind();
            vertArray->Unbind();
        } else {
            Y_WARN("Attempting to Render a Texture Vertex Array that has Invalid Data");
        }


        return;
    }

    void RenderVertexArrayMaterial::Execute() {

        Y_ASSERT(vertArray->IsValid() , "Attempting Render Invalid Texture Vertex Array | Did you call VertexArray::Upload()?");
        if (vertArray && material) {
            vertArray->Bind();

            std::shared_ptr<Shader> exShader= material->getShader();
            std::shared_ptr<Texture> exTexture = material->getTexture();
            Y_ASSERT(exShader != nullptr , "Attempting to Execute invalid RenderVertexArrayMaterial - shader is null");

            if (exShader != nullptr) {
                material->updateShaderUniforms();
                exShader->Bind();
                if (exTexture) 
                    exTexture->bind();

                // ToDo -> convert camera to leverage UBOs
                const auto& cam = Y_RENDERER.GetActivePerspectiveCamera();
                if (cam) {
                    exShader->SetUniformMat4("proj" , cam->GetProjMatrix()); 
                    exShader->SetUniformMat4("view" , cam->GetViewMatrix());
                }
                exShader->SetUniformMat4("model" , modelMatrix);

                if (vertArray->GetEltCount() > 0) {
                    glDrawElements(GL_TRIANGLES , vertArray->GetEltCount() , GL_UNSIGNED_INT , 0);
                } else {
                    glDrawArrays(GL_TRIANGLE_STRIP , 0 , vertArray->GetVertCount());
                }
                
                if (exTexture != nullptr) 
                    exTexture->unbind();
                exShader->Unbind();
            }

            vertArray->Unbind();

        } else {
            Y_WARN("Attempting to Render a Texture Vertex Array that has Invalid Data");
        }

        return;

        return;
    }

    void PushFramebuffer::Execute() {
        
        if (fBuffer) {
            Y_RENDERER.PushFrameBuffer(fBuffer);
        } else {
            Y_WARN("Attempting to execute Push FrameBuffer with invalid data");
        }
        return;
    }

    void PopFramebuffer::Execute() {
        Y_RENDERER.PopFrameBuffer();
        return;
    }

    void PushOrthoCamera::Execute() {
        
        if (camera) {
            Y_RENDERER.PushOrthoCamera(camera);
        } else {
            Y_WARN("Attempting to execute Push Orthographic Camera with invalid data");
        }
        return;
    }

    void PopOrthoCamera::Execute() {
        Y_RENDERER.PopOrthoCamera();
        return;
    }

    void PushPerspectiveCamera::Execute() {
        
        if (camera) {
            Y_RENDERER.PushPerspectiveCamera(camera);
        } else {
            Y_WARN("Attempting to execute Push Perspective Camera with invalid data");
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