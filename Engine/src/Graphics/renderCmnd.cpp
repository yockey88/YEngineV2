#include "Graphics/renderCmnd.hpp"
#include "engine.hpp"
#include "log.hpp"
#include "Graphics/framebuffer.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"

#include "glad/glad.h"

#include <iostream>

namespace Y {
namespace graphics {
namespace rendering {

    void RenderVertexArray::Execute() {
        std::shared_ptr<VertexArray> exVertArray = vertArray.lock();
        std::shared_ptr<Shader> exShader = shader.lock();

        Y_ASSERT(exVertArray->IsValid() , "Attemtping to Execute Invalid Vertex Array");
        if (exVertArray && exShader) {
            exVertArray->Bind();
            exShader->Bind();

            exShader->SetUniformMat4("model" , modelMatrix);

            if (exVertArray->GetEltCount() > 0) {
                glDrawElements(GL_TRIANGLES , exVertArray->GetEltCount() , GL_UNSIGNED_INT , 0);
            } else {
                glDrawArrays(GL_TRIANGLE_STRIP , 0 , exVertArray->GetVertCount());
            }

            exShader->Unbind();
            exVertArray->Unbind();
        } else {
            Y_WARN("Attempting to Render an Invalid Vertex Array");
        }

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

}
}
}