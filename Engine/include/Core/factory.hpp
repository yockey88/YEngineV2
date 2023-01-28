#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Graphics/camera.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"

#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <map>

namespace Y {
namespace core { 

    class Factory {
        public:
            static std::shared_ptr<graphics::Camera> GetDefaultCamera();

            static std::shared_ptr<graphics::VertexArray> CreateWindowMesh();
            static std::shared_ptr<graphics::VertexArray> CreateWhiteSquareMesh();

            static const std::shared_ptr<graphics::Shader> LoadShaderFile(const std::string& vpath , const std::string& fpath);
            static const std::shared_ptr<graphics::Shader> LoadBasicCamShader();

            static void GetPiecesOfLine(std::vector<std::string>& pieces , const std::string& line);
            static std::string GetFileAsOneStr(const std::string& path);
    };

    

}
}

#endif