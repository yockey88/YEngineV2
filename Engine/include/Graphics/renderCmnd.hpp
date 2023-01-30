#ifndef RENDER_COMMANDS_HPP
#define RENDER_COMMANDS_HPP

#include "glm/glm.hpp"

#include <memory>

namespace Y {
namespace graphics {

    class OrthoCamera;
    class PerspectiveCamera;
    class VertexArray;
    class Shader;
    class Texture;
    class Framebuffer;
    class Material;

namespace rendercommands {

    class RenderCommand {
        public:
            RenderCommand() {}
            virtual void Execute() = 0;
    };

    class RenderPoint : public RenderCommand {
        std::shared_ptr<VertexArray> vertArray;
        std::shared_ptr<Shader> shader;
        float size;
        public:
            RenderPoint(std::shared_ptr<VertexArray> vertArray , std::shared_ptr<Shader> shader , const float& size) 
                : vertArray(vertArray) , shader(shader) , size(size) {}
            virtual void Execute() override;
    };

    class RenderLine : public RenderCommand {
        std::shared_ptr<VertexArray> vertArray;
        std::shared_ptr<Shader> shader;
        float width;
        public:
            RenderLine(std::shared_ptr<VertexArray> vertArray , std::shared_ptr<Shader> shader ,  const float& width) 
                : vertArray(vertArray) , shader(shader) , width(width) {}
            virtual void Execute() override;
    };

    class RenderVertexArray : public RenderCommand {
        std::shared_ptr<VertexArray> vertArray;
        std::shared_ptr<Shader> shader;
        glm::mat4 modelMatrix;
        public:
            RenderVertexArray(std::shared_ptr<VertexArray> vertArray , std::shared_ptr<Shader> shader , const glm::mat4& modelMat = glm::mat4(1.f)) 
                : vertArray(vertArray) , shader(shader) , modelMatrix(modelMat) {}

            virtual void Execute() override;
    };

    class RenderTexturedVertexArray : public RenderCommand {
        std::shared_ptr<VertexArray> vertArray;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<Texture> texture;
        glm::mat4 modelMatrix;
        public:
            RenderTexturedVertexArray(std::shared_ptr<VertexArray> vertArray , std::shared_ptr<Shader> shader , std::shared_ptr<Texture> texture , const glm::mat4& modelMat = glm::mat4(1.f))
                : vertArray(vertArray) , shader(shader) , texture(texture) , modelMatrix(modelMat) {}

            virtual void Execute() override;
    };

    class RenderVertexArrayMaterial : public RenderCommand {
        std::shared_ptr<VertexArray> vertArray;
        std::shared_ptr<Material> material;
        glm::mat4 modelMatrix;
        public:
            RenderVertexArrayMaterial(std::shared_ptr<VertexArray> vertArray , std::shared_ptr<Material> material , const glm::mat4& modelMat = glm::mat4(1.f))
                : vertArray(vertArray) , material(material) , modelMatrix(modelMat) {}

            virtual void Execute() override;
    };

    class PushFramebuffer : public RenderCommand {
        std::shared_ptr<Framebuffer> fBuffer;
        public:
            PushFramebuffer(std::shared_ptr<Framebuffer> buffer)
                : fBuffer(buffer) {}
            virtual void Execute() override;
    };

    class PopFramebuffer : public RenderCommand {
        public:
            PopFramebuffer() {}
            virtual void Execute() override;
    };

    class PushOrthoCamera : public RenderCommand {
        std::shared_ptr<OrthoCamera> camera;
        public:
            PushOrthoCamera(std::shared_ptr<OrthoCamera> camera) : camera(camera) {}
            virtual void Execute() override;
    };

    class PopOrthoCamera : public RenderCommand {
        public:
            PopOrthoCamera() {}
            virtual void Execute() override;
    };

    class PushPerspectiveCamera : public RenderCommand {
        std::shared_ptr<PerspectiveCamera> camera;
        public:
            PushPerspectiveCamera(std::shared_ptr<PerspectiveCamera> camera) : camera(camera) {}
            virtual void Execute() override;
    };

    class PopPerspectiveCamera : public RenderCommand {
        public:
            PopPerspectiveCamera() {}
            virtual void Execute() override;
    };

}
}
}

#endif