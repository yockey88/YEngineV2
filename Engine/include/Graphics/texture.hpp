#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stdint.h>
#include <string>

namespace Y {
namespace graphics {

    enum class TextureFilter { nearest , linear };

    class Texture {
        TextureFilter filter;

        uint32_t id;
        uint32_t width , height;
        uint32_t numChannels;
        
        std::string name;
        std::string path;

        unsigned char* pixels;

        void loadTexture();
        public:
            Texture(const std::string& path);
            ~Texture();

            inline uint32_t getID() const { return id; }
            inline uint32_t getWidth() const { return width; }
            inline uint32_t getHeight() const { return height; }
            inline uint32_t getNumChannels() const { return numChannels; }
            inline std::string getPath() const { return path; }
            inline std::string getName() const { return name; }
            inline TextureFilter getTextFilter() const { return filter; }
            inline void setName(const std::string& name) { this->name = name; }

            void bind();
            void unbind();
            void setTextFilter(const TextureFilter& filter);
    };

}
}

#endif