#include "engine.hpp"
#include "log.hpp"
#include "Managers/renderManager.hpp"
#include "Graphics/framebuffer.hpp"
#include "Graphics/helper.hpp"

#include "glad/glad.h"

#include <iostream>

namespace Y {
namespace managers {

    void RenderManager::PushFrameBuffer(std::shared_ptr<graphics::Framebuffer> newBuffer) {

        Y_ASSERT(newBuffer != nullptr , "FrameBuffer is Null");
        m_Framebuffers.push(newBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER , newBuffer->getFbo()); Y_CHECK_GL_ERROR;
        glm::ivec2 bufferSize = newBuffer->getSize();
        SetViewport({0 , 0 , newBuffer->getSize().x , newBuffer->getSize().y});

        glm::vec4 cc = newBuffer->getClearColor();
        glClearColor(cc.r , cc.g , cc.b , cc.a); Y_CHECK_GL_ERROR;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); Y_CHECK_GL_ERROR;

        return;
    }

    void RenderManager::PopFrameBuffer() {

        Y_ASSERT(m_Framebuffers.size() > 0 , "Render Manager::popFrameBuffer() - empty stack");
        if (m_Framebuffers.size() > 0) {
            m_Framebuffers.pop();
            if (m_Framebuffers.size() > 0) {
                auto nextfb = m_Framebuffers.top();
                glBindFramebuffer(GL_FRAMEBUFFER , nextfb->getFbo()); Y_CHECK_GL_ERROR;
                SetViewport({0 , 0 , nextfb->getSize().x , nextfb->getSize().y});
            } else {
                glBindFramebuffer(GL_FRAMEBUFFER , 0); Y_CHECK_GL_ERROR;
                auto& window = Y_WINDOW;
                SetViewport({ 0 , 0 , window.GetSize().x , window.GetSize().y });
            }
        }
        return;
    }

    void RenderManager::PushCamera(std::shared_ptr<graphics::Camera> newCamera) {

        Y_ASSERT(newCamera != nullptr , "Camera is Null");
        m_Cameras.push(newCamera);

        return;
    }

    void RenderManager::PopCamera() {

        Y_ASSERT(m_Cameras.size() > 0 , "Render Manager::popCamera() - empty stack");
        if (m_Cameras.size() > 0) {
            m_Cameras.pop();
        }

        return;
    }

    void RenderManager::PushPerspectiveCamera(std::shared_ptr<graphics::PerspectiveCamera> newCamera) {
        Y_ASSERT(newCamera != nullptr , "Camera is Null");
        m_PerspectiveCameras.push(newCamera);
    }

    void RenderManager::PopPerspectiveCamera() {
        Y_ASSERT(m_PerspectiveCameras.size() > 0 , "Render Manager::popCamera() - empty stack");
        if (m_PerspectiveCameras.size() > 0) {
            m_PerspectiveCameras.pop();
        }
    }


    RenderManager::RenderManager() {}

    void RenderManager::Initialize() {
        Y_INFO("[Rendering Device]\n\t\tVendor-> {}\n\t\tRenderer-> {}\n\t\tVersion-> {}" ,
                    (const char*)glGetString(GL_VENDOR) , 
                    (const char*)glGetString(GL_RENDERER) , 
                    (const char*)glGetString(GL_VERSION));
        glEnable(GL_DEPTH_TEST); Y_CHECK_GL_ERROR;
		glDepthFunc(GL_LEQUAL); Y_CHECK_GL_ERROR;

		glEnable(GL_BLEND); Y_CHECK_GL_ERROR;
		glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA); Y_CHECK_GL_ERROR;

        Clear();

        return;
    }

    void RenderManager::Shutdown() {
        while (m_RenderCmnds.size() > 0) {
            m_RenderCmnds.pop();
        }

        return;
    }
    
    void RenderManager::SetViewport(const glm::ivec4& dimensions) {
        glViewport(dimensions.x , dimensions.y , dimensions.z , dimensions.w); Y_CHECK_GL_ERROR;
        return;
    }

    void RenderManager::SetClearColor(const glm::vec4& clearColor) {
        glClearColor(clearColor.r , clearColor.g , clearColor.b , clearColor.a); Y_CHECK_GL_ERROR;

        return;
    }

    void RenderManager::SetWireFrameMode(bool enabled) {
        if (enabled)
            glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
        
        if (!enabled)
            glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);

        return;
    }

    void RenderManager::Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc) {
        m_RenderCmnds.push(std::move(rc));

        return;
    }

    void RenderManager::Flush() {
        while (m_RenderCmnds.size() > 0) {
            auto rc = std::move(m_RenderCmnds.front());

            m_RenderCmnds.pop();
            rc->Execute();
        }

        return;
    }

    void RenderManager::Clear() {
        
        Y_ASSERT(m_RenderCmnds.size() == 0 , "Render Commands Unexecuted | Commands still in Queue");
        while (m_RenderCmnds.size() > 0) {
            m_RenderCmnds.pop();
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        return;
    }

}
}