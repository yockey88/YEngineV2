#include "core/factory.hpp"
#include "engine.hpp"

// using js = nlohmann::json;

namespace Y {
namespace core {
    
    std::shared_ptr<graphics::Camera> Factory::GetDefaultCamera() {

        std::shared_ptr<graphics::Camera> camera = std::make_shared<graphics::Camera>();
        camera->setPos({ 0.f , 0.f , 5.f });
        camera->setViewMat({ 0.f , 0.f , 5.f } , 0.f);
        return camera;

    }

    std::shared_ptr<graphics::PerspectiveCamera> Factory::GetPerspectiveCamera() {
        std::shared_ptr<graphics::PerspectiveCamera> camera = std::make_shared<graphics::PerspectiveCamera>();
        camera->SetPos({ 0.f , 0.f , 5.f });
        camera->SetTarget({ 0.f , 0.f , 0.f });
        camera->SetUp({ 0.f , 1.f , 0.f });
        return camera;
    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateWindowMesh() {
        
        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
		VA->setName("Window Mesh");
        
        Y_CREATE_VERTEX_BUFFER(vb, short);
		vb->pushVertex({  1 ,  1 , 1 , 1 });
		vb->pushVertex({  1 , -1 , 1 , 0 });
		vb->pushVertex({ -1 , -1 , 0 , 0 });
		vb->pushVertex({ -1 ,  1 , 0 , 1 });
		vb->setLayout({ 2 , 2 });
		VA->pushBuffer(std::move(vb));
		VA->setElements({ 0 , 3 , 1 , 1 , 3 , 2 });
		VA->upload();

        return VA;
    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateSquareMesh() {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->setName("Square Mesh");
        Y_CREATE_VERTEX_BUFFER(vb, float);

        vb->pushVertex({  0.5 ,  0.5 , 0.0 , 1.0 , 1.0 , 1.0 });
        vb->pushVertex({  0.5 , -0.5 , 0.0 , 1.0 , 1.0 , 1.0 });
        vb->pushVertex({ -0.5 , -0.5 , 0.0 , 1.0 , 1.0 , 1.0 });
        vb->pushVertex({ -0.5 ,  0.5 , 0.0 , 1.0 , 1.0 , 1.0 });
        vb->setLayout({ 3 , 3 });

        VA->pushBuffer(std::move(vb));
        VA->setElements({ 0 , 3 , 1 , 1 , 3 , 2 });
        VA->upload();

        return VA;

    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateCubeMesh() {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->setName("Square Mesh");
        Y_CREATE_VERTEX_BUFFER(vb, float);

        vb->pushVertex({  0.5 ,  0.5 , 0.5 , 1.0 , 1.0 , 1.0 });
        vb->pushVertex({  0.5 , -0.5 , 0.5 , 1.0 , 1.0 , 1.0 });
        vb->pushVertex({ -0.5 , -0.5 , 0.5 , 1.0 , 1.0 , 1.0 });
        vb->pushVertex({ -0.5 ,  0.5 , 0.5 , 1.0 , 1.0 , 1.0 });

        vb->pushVertex({  0.5 ,  0.5 , -0.5 , 1.0 , 1.0 , 1.0 });
        vb->pushVertex({  0.5 , -0.5 , -0.5 , 1.0 , 1.0 , 1.0 });
        vb->pushVertex({ -0.5 , -0.5 , -0.5 , 1.0 , 1.0 , 1.0 });
        vb->pushVertex({ -0.5 ,  0.5 , -0.5 , 1.0 , 1.0 , 1.0 });
        vb->setLayout({ 3 , 3 });

        VA->pushBuffer(std::move(vb));
        VA->setElements({ 0 , 3 , 1 , 1 , 3 , 2 ,
                          2 , 3 , 7 , 7 , 6 , 2 , 
                          2 , 6 , 1 , 1 , 6 , 5 , 
                          5 , 6 , 4 , 4 , 6 , 7 , 
                          7 , 3 , 4 , 4 , 3 , 0 , 
                          0 , 1 , 5 , 5 , 4 , 0 });
        VA->upload();

        return VA;
    }

    const std::shared_ptr<graphics::Shader> Factory::LoadShaderFile(const std::string& vpath , const std::string& fpath) {

        std::string vShaderStr = GetFileAsOneStr(vpath);
        std::string fShaderStr = GetFileAsOneStr(fpath);

        std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader>(vShaderStr , fShaderStr);

        return shader;
    }

    const std::shared_ptr<graphics::Shader> Factory::LoadBasicCamShader() {

        std::string vShader = GetFileAsOneStr("resources/shaders/basic_camera_shader.vert");
        std::string fShader = GetFileAsOneStr("resources/shaders/basic_camera_shader.frag");

        std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader>(vShader , fShader);
        return shader; 
    }

    void Factory::GetPiecesOfLine(std::vector<std::string>& pieces , const std::string& line) {
        std::string hold = "";
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ',') {
                pieces.push_back(hold);
                hold = "";
            } else {
                hold += line[i];
            }
        }
        pieces.push_back(hold);

        return;
    }

    std::string Factory::GetFileAsOneStr(const std::string& path) {
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