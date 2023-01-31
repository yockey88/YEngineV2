#include "main.hpp"

#include "Core/factory.hpp"
#include "Core/renderer.hpp"
#include "Graphics/perspectiveCamera.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"
#include "Graphics/material.hpp"

#include "Input/keyboard.hpp"
#include "Input/mouse.hpp"

#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/quaternion.hpp" 

namespace Y {
	
class Sandbox : public App {
	core::WindowProperties m_WinProps; 
	std::shared_ptr<graphics::PerspectiveCamera> camera;

	// std::shared_ptr<graphics::VertexArray> VA;

	std::shared_ptr<graphics::VertexArray> xyPlane;
	std::shared_ptr<graphics::VertexArray> yzPlane;
	std::shared_ptr<graphics::VertexArray> zxPlane;
	std::shared_ptr<graphics::Shader> shader;

	// glm::mat4 cubeModel;

	glm::mat4 xyModel;
	glm::mat4 yzModel;
	glm::mat4 zxModel;
	
	glm::vec2 mousePos;

	core::WindowProperties SetWinProps();

	void RenderGrid();
	
	public:
		Sandbox() {}
		Sandbox(const Sandbox&) = delete;

		virtual core::WindowProperties GetWindowProperties() override { return SetWinProps(); }

		virtual void Initialize() override {
			camera = core::Factory::GetPerspectiveCamera();
			camera->SetPos({ 10.f , 10.f , 10.f });
			camera->SetForward({ -10.f , -10.f , -10.f });

			glm::mat4 rot = glm::mat4(1.f);
			rot = glm::rotate(rot , glm::radians(90.f) , { 1.f , 0.f , -1.f });
			glm::vec3 cameraUp = glm::vec3(rot * glm::vec4(cameraUp , 1.f));

			camera->SetUp(cameraUp);

			// VA = core::Factory::CreateCubeMesh({ 1.f , 1.f , 1.f } , { 1.f , 0.f , 0.f } , { 0.f , 1.f , 0.f } , { 0.f , 0.f , 1.f });

			// cubeModel = glm::mat4(1.f);
			// cubeModel = glm::translate(cubeModel , { 0.f , 0.f , 0.f }) * glm::scale(cubeModel , { 1.f , 1.f , 1.f });

			xyPlane = core::Factory::CreateSquareMesh({ 1.f , 0.f , 0.f });
			yzPlane = core::Factory::CreateSquareMesh({ 0.f , 1.f , 0.f });
			zxPlane = core::Factory::CreateSquareMesh({ 0.f , 0.f , 1.f });

			shader = core::Factory::LoadBasicCamShader();

			xyModel = glm::mat4(1.f);
			yzModel = glm::mat4(1.f);
			zxModel = glm::mat4(1.f);

			xyModel = glm::translate(xyModel , { 5.f , 5.f , 0.f }) * glm::scale(xyModel , { 10.f , 10.f , 10.f });
			yzModel = glm::translate(yzModel , { 0.f , 5.f , 5.f }) * glm::scale(yzModel , { 10.f , 10.f , 10.f }) * 
						glm::rotate(yzModel , glm::radians(90.f) , { 0.f , 1.f , 0.f });
			zxModel = glm::translate(zxModel , { 5.f , 0.f , 5.f }) * glm::scale(zxModel , { 10.f , 10.f , 10.f }) * 
						glm::rotate(zxModel , glm::radians(90.f) , { 1.f , 0.f , 0.f });

			mousePos = glm::vec2{ (float)input::mouse::X() , (float)input::mouse::Y() };
		}

		virtual void Shutdown() override { }

		virtual void Update(const float& dt) override {
			mousePos = glm::vec3(0.f);

			if (input::keyboard::key(Y_INPUT_KEY_W)) { camera->SetPos(camera->GetPos() + (0.2f *glm::normalize(camera->GetCameraForward()))); }
			if (input::keyboard::key(Y_INPUT_KEY_A)) 
				{ camera->SetPos(camera->GetPos() - (0.2f * glm::normalize(glm::cross(camera->GetCameraForward() , camera->GetCameraUp())))); }
			if (input::keyboard::key(Y_INPUT_KEY_S)) { camera->SetPos(camera->GetPos() - (0.2f *glm::normalize(camera->GetCameraForward()))); }
			if (input::keyboard::key(Y_INPUT_KEY_D)) 
				{ camera->SetPos(camera->GetPos() + (0.2f * glm::normalize(glm::cross(camera->GetCameraForward() , camera->GetCameraUp())))); }
		
			// cubeModel = glm::rotate(cubeModel , glm::radians(2.f) , { 1.f , 1.f , 0.f });
		}

		virtual void Render() override {
			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(PushPerspectiveCamera , camera));

			// glm::mat4 model = cubeModel;
			// Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , VA , shader , model));

			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , xyPlane , shader , xyModel));
			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , yzPlane , shader , yzModel));
			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , zxPlane , shader , zxModel));

			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(PopPerspectiveCamera));
		}

		virtual void ImGuiRender() override {}
};

core::WindowProperties Sandbox::SetWinProps() {
	core::WindowProperties props;

	props.size.x = 1920;
	props.size.y = 1079;

	props.cc.r = static_cast<float>(0x2f) / static_cast<float>(0xFF);
	props.cc.g = static_cast<float>(0x61) / static_cast<float>(0xFF);
	props.cc.b = static_cast<float>(0xc4) / static_cast<float>(0xFF);
	props.cc.a = static_cast<float>(0xFF) / static_cast<float>(0xFF);

	props.flags |= SDL_WINDOW_RESIZABLE;
	props.title = "[Machine Y Development v{1.0.2}]";

	return props;
}

void Sandbox::RenderGrid() {

	for (int i = -5; i < 6; i++) {
		for (int j = 5; j > -6; j--) {
			if (j == 0) {
				core::YRenderer2D::RenderLine(Y_GREEN3 , { (float)j , (float)(-1 * i) , 0.f } , { (float)j , (float)i , 0.f } , 3.f);
			} else {
				core::YRenderer2D::RenderLine(Y_WHITE3 , { (float)j , (float)(-1 * i) , 0.f } , { (float)j , (float)i , 0.f } , 1.f);
			}
		}
	}
	for (int i = -5; i < 6; i++) {
		for (int j = 5; j > -6; j--) {
			if (i == 0) {
				core::YRenderer2D::RenderLine(Y_RED3 , { (float)(-1 * j) , (float)i , 0.f } , { (float)j , (float)i , 0.f } , 3.f);
			} else {
				core::YRenderer2D::RenderLine(Y_WHITE3 , { (float)(-1 * j) , (float)i , 0.f } , { (float)j , (float)i , 0.f } , 1.f);
			}
		}
	}
	core::YRenderer2D::RenderPoint({ 1.f , 0.f , 1.f } , { 0.f , 0.f , 0.f } , 11.f);

	return;
}
	
}

/* Machine Y Entry Point Override */
Y::App* CreateApp() {
	return new Y::Sandbox;
}