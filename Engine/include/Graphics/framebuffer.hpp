#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "glm/glm.hpp"

#include <stdint.h>

namespace Y {
namespace graphics {

    class Framebuffer {
        uint32_t fbo;
        uint32_t textureID;
        uint32_t renderBufferID;

        glm::ivec2 size;
        glm::vec4 clearColor;
        public:
            Framebuffer(int width , int height);
            ~Framebuffer();

            inline uint32_t GetFbo() const { return fbo; }
            inline uint32_t GetTextureID() const { return textureID; }
            inline uint32_t GetRenderBufferID() const { return renderBufferID; }
            inline glm::ivec2& GetSize() { return size; }
            void SetClearColor(const glm::vec4& cc) { clearColor = cc; }
            inline glm::vec4& GetClearColor() { return clearColor; } 
    };

}
}

#endif