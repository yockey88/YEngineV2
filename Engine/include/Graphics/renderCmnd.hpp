#ifndef RENDER_CMND_HPP
#define RENDER_CMND_HPP

#include "glm/glm.hpp"

#include <memory>

namespace Y {
namespace graphics {

    class Framebuffer;
    class VertexArray;
    class Shader;

namespace rendering {

    class RenderCommand {
        public:
            RenderCommand() {}
            virtual void Execute() = 0;
    };

    class RenderVertexArray : public RenderCommand {
        std::weak_ptr<VertexArray> vertArray;
        std::weak_ptr<Shader> shader;
        glm::mat4 modelMatrix;
        public:
            RenderVertexArray(std::weak_ptr<VertexArray> vertArray, std::weak_ptr<Shader> shader , const glm::mat4& modelMat = glm::mat4(1.f)) 
                : vertArray(vertArray) , shader(shader) , modelMatrix(modelMat) {}

            virtual void Execute() override;
    };

    class PushFramebuffer: public RenderCommand {
        std::weak_ptr<Framebuffer> fBuffer;
        public:
            PushFramebuffer(std::weak_ptr<Framebuffer> buffer)
                : fBuffer(buffer) {}
            virtual void Execute() override;
    };

    class PopFramebuffer: public RenderCommand {
        public:
            PopFramebuffer() {}
            virtual void Execute() override;
    };

}
}
}

#endif
