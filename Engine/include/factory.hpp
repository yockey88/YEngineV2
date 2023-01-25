#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <string>
#include <fstream>
#include <memory>

namespace Y {
namespace graphics {

    class VertexArray;
    class Shader;

}
namespace factory {

    std::shared_ptr<graphics::VertexArray> GetMainWindowVA();
    std::shared_ptr<graphics::Shader> GetMainWindowShader();
    

    std::string GetFileAsOneStr(const std::string& path);

}
}

#endif
