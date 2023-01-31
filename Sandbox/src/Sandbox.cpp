#include "main.hpp"

#include "Core/factory.hpp"
#include "Core/renderer.hpp"
#include "Graphics/perspectiveCamera.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"
#include "Graphics/material.hpp"

#include "Input/keyboard.hpp"
#include "Input/mouse.hpp"

#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/quaternion.hpp" 

namespace Y {
	
class Sandbox : public App {
	core::WindowProperties m_WinProps; 
	std::shared_ptr<graphics::PerspectiveCamera> camera;

	std::shared_ptr<graphics::VertexArray> VA;
	std::shared_ptr<graphics::VertexArray> floor;
	std::shared_ptr<graphics::Shader> shader;

	glm::mat4 cubeModel , floorModel;
	
	glm::ivec2 currMousePos , lastMousePos;

	float xOffset , yOffset;

	core::WindowProperties SetWinProps();

	void RenderGrid();
	
	public:
		Sandbox() {}
		Sandbox(const Sandbox&) = delete;

		virtual core::WindowProperties GetWindowProperties() override { return SetWinProps(); }

		virtual void Initialize() override {
			camera = core::Factory::GetPerspectiveCamera();
			camera->SetPos({ 0.f , 0.f , 7.f });
			camera->SetForward({ 0.f , 0.f , -1.f});

			floor = core::Factory::CreateSquareMesh({ (float)20 / 255.f , (float)87 / 255.f , (float)20 / 255.f });
			VA = core::Factory::CreateCubeMesh({ 1.f , 1.f , 1.f } , { 1.f , 0.f , 0.f } , { 0.f , 1.f , 0.f } , { 0.f , 0.f , 1.f });

			shader = core::Factory::LoadBasicCamShader();

			cubeModel = glm::mat4(1.f);
			cubeModel = glm::translate(cubeModel , { 0.f , 0.f , 0.f }) * glm::scale(cubeModel , { 1.f , 1.f , 1.f });

			floorModel = glm::mat4(1.f);
			floorModel = glm::translate(floorModel , { 0.f , -4.f , 0.f }) * glm::scale(floorModel , { 100.f , 100.f , 100.f });
			floorModel = glm::rotate(floorModel , glm::radians(90.f) , { 1.f , 0.f , 0.f });

			xOffset = 0.f; // = (float)input::mouse::DX() * -0.05f;
 			yOffset = 0.f; // = (float)input::mouse::DY() * -0.05f;
		}

		virtual void Shutdown() override { }

		virtual void Update(const float& dt) override {

			xOffset = (float)input::mouse::DX() * 0.05f;
			yOffset = (float)input::mouse::DY() * 0.05f;

			float yaw = xOffset;
			float pitch = yOffset;

			if (input::keyboard::key(Y_INPUT_KEY_W)) { camera->SetPos(camera->GetPos() + (0.2f * glm::normalize(camera->GetCameraForward()))); }
			if (input::keyboard::key(Y_INPUT_KEY_A)) 
				{ camera->SetPos(camera->GetPos() - (0.2f * glm::normalize(glm::cross(camera->GetCameraForward() , camera->GetCameraUp())))); }
			if (input::keyboard::key(Y_INPUT_KEY_S)) { camera->SetPos(camera->GetPos() - (0.2f * glm::normalize(camera->GetCameraForward()))); }
			if (input::keyboard::key(Y_INPUT_KEY_D)) 
				{ camera->SetPos(camera->GetPos() + (0.2f * glm::normalize(glm::cross(camera->GetCameraForward() , camera->GetCameraUp())))); }
		
			cubeModel = glm::rotate(cubeModel , glm::radians(2.f) , { 1.f , 1.f , -1.f });
		}

		virtual void Render() override {
			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(PushPerspectiveCamera , camera));

			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , floor , shader , floorModel));
			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , VA , shader , cubeModel));

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