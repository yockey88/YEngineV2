#include "factory.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"

namespace Y {
namespace factory {

    std::shared_ptr<graphics::VertexArray> GetMainWindowVA() {
        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
		Y_CREATE_VERTEX_BUFFER(vb, short);
		vb->PushVertex({  1 ,  1 , 1 , 1 });
		vb->PushVertex({  1 , -1 , 1 , 0 });
		vb->PushVertex({ -1 , -1 , 0 , 0 });
		vb->PushVertex({ -1 ,  1 , 0 , 1 });
		vb->SetLayout({ 2 , 2 });
		VA->PushBuffer(std::move(vb));
		VA->SetElements({ 0 , 3 , 1 , 1 , 3 , 2 });
		VA->Upload();
        return VA;
    }

    std::shared_ptr<graphics::Shader> GetMainWindowShader() {
        std::string v_path = GetFileAsOneStr("resources/shaders/main_window_shader.vert");
        std::string f_path = GetFileAsOneStr("resources/shaders/main_window_shader.frag");
        std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader>(v_path , f_path);
        return shader;
    }

    std::string GetFileAsOneStr(const std::string& path) {
        std::string line , hold = "";
        std::ifstream shader(path);
        Y_ASSERT(shader.is_open() , "Using Nonexistent Shader Paths");

        while (!shader.eof()) {
            getline(shader , line);
            hold += line + '\n';
        }

        return hold;
    }

}
}