#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Graphics/orthoCamera.hpp"
#include "Graphics/perspectiveCamera.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"
#include "Graphics/renderCmnd.hpp"

#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <map>

namespace Y {
namespace core { 

    class Factory {
        public:
            static std::shared_ptr<graphics::OrthoCamera> GetOrthoCamera();
            static std::shared_ptr<graphics::PerspectiveCamera> GetPerspectiveCamera();

            static std::shared_ptr<graphics::VertexArray> CreateWindowMesh();

            static std::shared_ptr<graphics::VertexArray> CreatePoint(const glm::vec3& color ,  const glm::vec3& pos , const float& size);

            static std::shared_ptr<graphics::VertexArray> CreateLine(const glm::vec3& color ,  const glm::vec3& pnt1 ,  const glm::vec3& pnt2);
            static std::shared_ptr<graphics::VertexArray> CreateLine(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& pnt1 ,  const glm::vec3& pnt2);

            static std::shared_ptr<graphics::VertexArray> CreateTriangleMesh(const glm::vec3& color);
            static std::shared_ptr<graphics::VertexArray> CreateTriangleMesh(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3);

            static std::shared_ptr<graphics::VertexArray> CreateSquareMesh(const glm::vec3& color);
            static std::shared_ptr<graphics::VertexArray> CreateSquareMesh(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& color4);

            static std::shared_ptr<graphics::VertexArray> CreateCubeMesh(const glm::vec3& color);
            static std::shared_ptr<graphics::VertexArray> CreateCubeMesh(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& color4);

            static const std::shared_ptr<graphics::Shader> LoadShaderFile(const std::string& vpath , const std::string& fpath);
            static const std::shared_ptr<graphics::Shader> LoadBasicCamShader();
            static const std::shared_ptr<graphics::Shader> LoadBasicCircleCamShader();

            static void GetPiecesOfLine(std::vector<std::string>& pieces , const std::string& line);
            static std::string GetFileAsOneStr(const std::string& path);
    };

    

}
}

#endif