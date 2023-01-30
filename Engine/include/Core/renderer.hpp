#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "glm/glm.hpp"

#define Y_WHITE3 glm::vec3{ 1.f , 1.f , 1.f }
#define Y_BLACK3 glm::vec3{ 0.f , 0.f , 0.f }
#define Y_RED3   glm::vec3{ 1.f , 0.f , 0.f }
#define Y_GREEN3 glm::vec3{ 0.f , 1.f , 0.f }
#define Y_BLUE3  glm::vec3{ 0.f , 0.f , 1.f }

namespace Y {
namespace core {

    class YRenderer2D {
        public:
            static void RenderPoint(const glm::vec3& color , const glm::vec3& pos , const float& size);

            static void RenderLine(const glm::vec3& color , const glm::vec3& pnt1 , const glm::vec3& pnt2 , const float& width);
            static void RenderLine(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& pnt1 , const glm::vec3& pnt2 , const float& width);

            static void RenderTriangle(const glm::vec3& color , const glm::vec3& pos , const glm::vec3& size);
            static void RenderTriangle(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& pos , const glm::vec3& size);

            static void RenderRect(const glm::vec3& color , const glm::vec3& pos , const glm::vec3& size);
            static void RenderRect(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& color4 , 
                                    const glm::vec3& pos , const glm::vec3& size);

            static void RenderCube(const glm::vec3& color , const glm::vec3& pos , const glm::vec3& size);
            static void RenderCube(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& color4 , 
                                    const glm::vec3& pos , const glm::vec3& size);
    };

}
}

#endif