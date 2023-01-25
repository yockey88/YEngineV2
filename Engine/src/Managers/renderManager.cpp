#include "Managers/renderManager.hpp"
#include "engine.hpp"
#include "log.hpp"
#include "Graphics/GLErrorHelper.hpp"
#include "Graphics/framebuffer.hpp"

#include "glad/glad.h"

#include <iostream>

namespace Y {
namespace managers {

    void RenderManager::PushFrameBuffer(std::shared_ptr<graphics::Framebuffer> newBuffer) {

        Y_ASSERT(newBuffer != nullptr , "FrameBuffer is Null");
        frameBuffers.push(newBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER , newBuffer->GetFbo()); Y_CHECK_GL_ERROR;
        glm::ivec2 bufferSize = newBuffer->GetSize();
        SetViewport({0 , 0 , newBuffer->GetSize().x , newBuffer->GetSize().y});

        glm::vec4 cc = newBuffer->GetClearColor();
        glClearColor(cc.r , cc.g , cc.b , cc.a); Y_CHECK_GL_ERROR;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); Y_CHECK_GL_ERROR;

        return;
    }

    void RenderManager::PopFrameBuffer() {

        Y_ASSERT(frameBuffers.size() > 0 , "Render Manager::popFrameBuffer() - empty stack");
        if (frameBuffers.size() > 0) {
            frameBuffers.pop();
            if (frameBuffers.size() > 0) {
                auto nextfb = frameBuffers.top();
                glBindFramebuffer(GL_FRAMEBUFFER , nextfb->GetFbo()); Y_CHECK_GL_ERROR;
                SetViewport({0 , 0 , nextfb->GetSize().x , nextfb->GetSize().y});
            } else {
                glBindFramebuffer(GL_FRAMEBUFFER , 0); Y_CHECK_GL_ERROR;
                auto& window = Y_WINDOW;
                SetViewport({0 , 0 , window.GetSize().x , window.GetSize().y});
            }
        }
        return;
    }
    
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
        while (renderCmnds.size() > 0) {
            renderCmnds.pop();
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

    void RenderManager::Submit(std::unique_ptr<graphics::rendering::RenderCommand> rc) {
        renderCmnds.push(std::move(rc));

        return;
    }

    void RenderManager::Flush() {
        while (renderCmnds.size() > 0) {
            auto rc = std::move(renderCmnds.front());

            renderCmnds.pop();
            rc->Execute();
        }

        return;
    }

    void RenderManager::Clear() {
        
        Y_ASSERT(renderCmnds.size() == 0 , "Render Commands Unexecuted | Commands still in Queue");
        while (renderCmnds.size() > 0) {
            renderCmnds.pop();
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        return;
    }
    
}
}