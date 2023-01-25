#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

#include "Graphics/renderCmnd.hpp"

#include "glm/glm.hpp"

#include <queue>
#include <stack>

#define Y_SUBMIT_RENDER_CMND(type , ...) std::move(std::make_unique<Y::graphics::rendering::type>(__VA_ARGS__))

namespace Y {
namespace managers {

    class RenderManager {
        friend class graphics::rendering::PushFramebuffer;
        friend class graphics::rendering::PopFramebuffer;

        std::queue<std::unique_ptr<graphics::rendering::RenderCommand>> renderCmnds;
        std::stack<std::shared_ptr<graphics::Framebuffer>> frameBuffers;

        void PushFrameBuffer(std::shared_ptr<graphics::Framebuffer> newBuffer);
        void PopFrameBuffer(); 

        public:
            RenderManager() {}

            void Initialize();
            void Shutdown();

            void SetViewport(const glm::ivec4& dimensions);
            void SetClearColor(const glm::vec4& clearColor);
            void SetWireFrameMode(bool enabled);

            void Submit(std::unique_ptr<graphics::rendering::RenderCommand> rc);
            
            // executes commands in order they were received
            void Flush();

            void Clear();
    };

}
}

#endif
