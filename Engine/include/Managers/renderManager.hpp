#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

#include "Graphics/renderCmnd.hpp"

#include "glm/glm.hpp"

#include <queue>
#include <stack>

#define Y_SUBMIT_RENDER_CMND(type , ...) std::move(std::make_unique<Y::graphics::rendercommands::type>(__VA_ARGS__))

namespace Y {
namespace managers {

    class RenderManager {
        friend class graphics::rendercommands::PushFramebuffer;
        friend class graphics::rendercommands::PopFramebuffer;
        friend class graphics::rendercommands::PushCamera;
        friend class graphics::rendercommands::PopCamera;
        friend class graphics::rendercommands::PushPerspectiveCamera;
        friend class graphics::rendercommands::PopPerspectiveCamera;

        std::queue<std::unique_ptr<graphics::rendercommands::RenderCommand>> m_RenderCmnds;
        std::stack<std::shared_ptr<graphics::Framebuffer>> m_Framebuffers;
        std::stack<std::shared_ptr<graphics::Camera>> m_Cameras;
        std::stack<std::shared_ptr<graphics::PerspectiveCamera>> m_PerspectiveCameras;

        void PushFrameBuffer(std::shared_ptr<graphics::Framebuffer> newBuffer);
        void PopFrameBuffer(); 
        void PushCamera(std::shared_ptr<graphics::Camera> newCamera);
        void PopCamera();
        void PushPerspectiveCamera(std::shared_ptr<graphics::PerspectiveCamera> newCamera);
        void PopPerspectiveCamera();
        public:
            RenderManager();

            inline graphics::Camera* GetActiveCamera() const { return ((m_Cameras.size() > 0) ? m_Cameras.top().get() : nullptr); }
            inline graphics::PerspectiveCamera* GetActivePerspectiveCamera() const { return ((m_PerspectiveCameras.size() > 0) ? m_PerspectiveCameras.top().get() : nullptr); }

            void Initialize();
            void Shutdown();

            void SetViewport(const glm::ivec4& dimensions);
            void SetClearColor(const glm::vec4& clearColor);
            void SetWireFrameMode(bool enabled);

            void Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc);
            
            // executes commands in order they were received
            void Flush();

            void Clear();
    };

}
}

#endif