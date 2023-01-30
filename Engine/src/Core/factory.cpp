#include "core/factory.hpp"
#include "engine.hpp"

#include "glm/gtc/matrix_transform.hpp"

// using js = nlohmann::json;

namespace Y {
namespace core {
    
    std::shared_ptr<graphics::OrthoCamera> Factory::GetOrthoCamera() {

        std::shared_ptr<graphics::OrthoCamera> camera = std::make_shared<graphics::OrthoCamera>();
        camera->SetPos({ 0.f , 0.f , 11.f });
        camera->CalcViewMat({ 0.f , 0.f , 11.f } , 0.f);
        return camera;

    }

    std::shared_ptr<graphics::PerspectiveCamera> Factory::GetPerspectiveCamera() {

        std::shared_ptr<graphics::PerspectiveCamera> camera = std::make_shared<graphics::PerspectiveCamera>();
        camera->SetPos({ 0.f , 0.f , 5.f });
        camera->CalcViewMat({ 0.f , 0.f , 5.f } , { 0.f , 0.f , -1.f } , { 0.f , 1.f , 0.f });
        return camera;

    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateWindowMesh() {
        
        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
		VA->SetName("Window Mesh");
        
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

    std::shared_ptr<graphics::VertexArray> Factory::CreatePoint(const glm::vec3& color ,  const glm::vec3& pos , const float& size) {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->SetName("Point");
        Y_CREATE_VERTEX_BUFFER(vb , float);
        vb->PushVertex({ pos.x , pos.y , pos.z , color.r , color.g , color.b , size });
        vb->SetLayout({ 3 , 3 });

        VA->PushBuffer(std::move(vb));
        VA->Upload();

        return VA;

    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateLine(const glm::vec3& color ,  const glm::vec3& pnt1 ,  const glm::vec3& pnt2) {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->SetName("Line");
        Y_CREATE_VERTEX_BUFFER(vb , float);
        vb->PushVertex({ pnt1.x , pnt1.y , pnt1.z , color.r , color.g , color.b });
        vb->PushVertex({ pnt2.x , pnt2.y , pnt2.z , color.r , color.g , color.b });
        vb->SetLayout({ 3 , 3 });

        VA->PushBuffer(std::move(vb));
        VA->Upload();

        return VA;

    }
    
    std::shared_ptr<graphics::VertexArray> Factory::CreateLine(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& pnt1 ,  const glm::vec3& pnt2) {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->SetName("Line");
        Y_CREATE_VERTEX_BUFFER(vb , float);
        vb->PushVertex({ pnt1.x , pnt1.y , pnt1.z , color1.r , color1.g , color1.b });
        vb->PushVertex({ pnt2.x , pnt2.y , pnt2.z , color2.r , color2.g , color2.b });
        vb->SetLayout({ 3 , 3 });

        VA->PushBuffer(std::move(vb));
        VA->Upload();

        return VA;

    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateTriangleMesh(const glm::vec3& color) {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->SetName("Triangle Mesh");
        Y_CREATE_VERTEX_BUFFER(vb, float);

        vb->PushVertex({  0.0 ,  0.5 , 0.0 , color.r , color.g , color.b });
        vb->PushVertex({  0.5 , -0.5 , 0.0 , color.r , color.g , color.b });
        vb->PushVertex({ -0.5 , -0.5 , 0.0 , color.r , color.g , color.b });
        vb->SetLayout({ 3 , 3 });

        VA->PushBuffer(std::move(vb));
        VA->Upload();

        return VA;
    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateTriangleMesh(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3) {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->SetName("Triangle Mesh");
        Y_CREATE_VERTEX_BUFFER(vb, float);

        vb->PushVertex({  0.0 ,  0.5 , 0.0 , color1.r , color1.g , color1.b });
        vb->PushVertex({  0.5 , -0.5 , 0.0 , color2.r , color2.g , color2.b });
        vb->PushVertex({ -0.5 , -0.5 , 0.0 , color3.r , color3.g , color3.b });
        vb->SetLayout({ 3 , 3 });

        VA->PushBuffer(std::move(vb));
        VA->Upload();

        return VA;
    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateSquareMesh(const glm::vec3& color) {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->SetName("Square Mesh");
        Y_CREATE_VERTEX_BUFFER(vb, float);

        vb->PushVertex({  0.5 ,  0.5 , 0.0 , color.r , color.g , color.b });
        vb->PushVertex({  0.5 , -0.5 , 0.0 , color.r , color.g , color.b });
        vb->PushVertex({ -0.5 , -0.5 , 0.0 , color.r , color.g , color.b });
        vb->PushVertex({ -0.5 ,  0.5 , 0.0 , color.r , color.g , color.b });
        vb->SetLayout({ 3 , 3 });

        VA->PushBuffer(std::move(vb));
        VA->SetElements({ 0 , 3 , 1 , 1 , 3 , 2 });
        VA->Upload();

        return VA;

    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateSquareMesh(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& color4) {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->SetName("Square Mesh");
        Y_CREATE_VERTEX_BUFFER(vb, float);

        vb->PushVertex({  0.5 ,  0.5 , 0.0 , color1.r , color1.g , color1.b });
        vb->PushVertex({  0.5 , -0.5 , 0.0 , color2.r , color2.g , color2.b });
        vb->PushVertex({ -0.5 , -0.5 , 0.0 , color3.r , color3.g , color3.b });
        vb->PushVertex({ -0.5 ,  0.5 , 0.0 , color4.r , color4.g , color4.b });
        vb->SetLayout({ 3 , 3 });

        VA->PushBuffer(std::move(vb));
        VA->SetElements({ 0 , 3 , 1 , 1 , 3 , 2 });
        VA->Upload();

        return VA;

    }

    std::shared_ptr<graphics::VertexArray> Factory::CreateCubeMesh(const glm::vec3& color) {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->SetName("Cube Mesh");
        Y_CREATE_VERTEX_BUFFER(vb, float);

        vb->PushVertex({  0.5 ,  0.5 , 0.5 , color.r , color.g , color.b });
        vb->PushVertex({  0.5 , -0.5 , 0.5 , color.r , color.g , color.b });
        vb->PushVertex({ -0.5 , -0.5 , 0.5 , color.r , color.g , color.b });
        vb->PushVertex({ -0.5 ,  0.5 , 0.5 , color.r , color.g , color.b });
        vb->PushVertex({  0.5 ,  0.5 , -0.5 , color.r , color.g , color.b });
        vb->PushVertex({  0.5 , -0.5 , -0.5 , color.r , color.g , color.b });
        vb->PushVertex({ -0.5 , -0.5 , -0.5 , color.r , color.g , color.b });
        vb->PushVertex({ -0.5 ,  0.5 , -0.5 , color.r , color.g , color.b });

        vb->SetLayout({ 3 , 3 });

        VA->PushBuffer(std::move(vb));
        VA->SetElements({ 0 , 3 , 1 , 1 , 3 , 2 ,
                            2 , 3 , 7 , 7 , 6 , 2 ,
                            2 , 6 , 1 , 1 , 6 , 5 ,
                            5 , 6 , 4 , 4 , 6 , 7 , 
                            7 , 3 , 4 , 4 , 3 , 0 , 
                            0 , 1 , 5 , 5 , 4 , 0 });
        VA->Upload();

        return VA;

    }
    
    std::shared_ptr<graphics::VertexArray> Factory::CreateCubeMesh(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& color4) {

        std::shared_ptr<graphics::VertexArray> VA = std::make_shared<graphics::VertexArray>();
        VA->SetName("Cube Mesh");
        Y_CREATE_VERTEX_BUFFER(vb, float);

        vb->PushVertex({  0.5 ,  0.5 , 0.5 , color1.r , color1.g , color1.b });
        vb->PushVertex({  0.5 , -0.5 , 0.5 , color2.r , color2.g , color2.b });
        vb->PushVertex({ -0.5 , -0.5 , 0.5 , color3.r , color3.g , color3.b });
        vb->PushVertex({ -0.5 ,  0.5 , 0.5 , color4.r , color4.g , color4.b });
        vb->PushVertex({  0.5 ,  0.5 , -0.5 , color1.r , color1.g , color1.b });
        vb->PushVertex({  0.5 , -0.5 , -0.5 , color2.r , color2.g , color2.b });
        vb->PushVertex({ -0.5 , -0.5 , -0.5 , color3.r , color3.g , color3.b });
        vb->PushVertex({ -0.5 ,  0.5 , -0.5 , color4.r , color4.g , color4.b });

        vb->SetLayout({ 3 , 3 });

        VA->PushBuffer(std::move(vb));
        VA->SetElements({ 0 , 3 , 1 , 1 , 3 , 2 ,
                            2 , 3 , 7 , 7 , 6 , 2 ,
                            2 , 6 , 1 , 1 , 6 , 5 ,
                            5 , 6 , 4 , 4 , 6 , 7 , 
                            7 , 3 , 4 , 4 , 3 , 0 , 
                            0 , 1 , 5 , 5 , 4 , 0 });
        VA->Upload();

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

    const std::shared_ptr<graphics::Shader> Factory::LoadBasicCircleCamShader() {
        std::string vShader = GetFileAsOneStr("resources/shaders/basic_circle.vert");
        std::string fShader = GetFileAsOneStr("resources/shaders/basic_circle.frag");

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