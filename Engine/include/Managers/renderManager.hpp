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
        friend class graphics::rendercommands::PushOrthoCamera;
        friend class graphics::rendercommands::PopOrthoCamera;
        friend class graphics::rendercommands::PushPerspectiveCamera;
        friend class graphics::rendercommands::PopPerspectiveCamera;

        std::queue<std::unique_ptr<graphics::rendercommands::RenderCommand>> m_RenderCmnds;
        std::stack<std::shared_ptr<graphics::Framebuffer>> m_Framebuffers;
        std::stack<std::shared_ptr<graphics::OrthoCamera>> m_OrthoCameras;
        std::stack<std::shared_ptr<graphics::PerspectiveCamera>> m_PerspectiveCameras;

        void PushFrameBuffer(std::shared_ptr<graphics::Framebuffer> newBuffer);
        void PopFrameBuffer(); 
        void PushOrthoCamera(std::shared_ptr<graphics::OrthoCamera> newCamera);
        void PopOrthoCamera();
        void PushPerspectiveCamera(std::shared_ptr<graphics::PerspectiveCamera> newCamera);
        void PopPerspectiveCamera();
        public:
            RenderManager();

            inline graphics::OrthoCamera* GetActiveOrthoCamera() const { return ((m_OrthoCameras.size() > 0) ? m_OrthoCameras.top().get() : nullptr); }
            inline graphics::PerspectiveCamera* GetActivePerspectiveCamera() const { return ((m_PerspectiveCameras.size() > 0) ? m_PerspectiveCameras.top().get() : nullptr); }

            void Initialize();
            void Shutdown();

            void SetViewport(const glm::ivec4& dimensions);
            void SetClearColor(const glm::vec4& clearColor);
            void SetWireFrameMode(bool enabled);

            void Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc);
            void Flush();
            void Clear();
    };

}
}

#endif