#include "main.hpp"

#include "Core/factory.hpp"

#include "Graphics/camera.hpp"
#include "Graphics/perspectiveCamera.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"
#include "Graphics/material.hpp"

#include "Input/keyboard.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Y {
	
class Sandbox : public App {
	core::WindowProperties setWinProps();
	std::shared_ptr<graphics::PerspectiveCamera> camera;
	std::shared_ptr<graphics::VertexArray> VA;
	std::shared_ptr<graphics::Shader> shader;

	glm::vec3 pos{ 0.f , 0.f , 0.f } , size{ 1.f , 1.f , 1.f };
	
	public:
		Sandbox() {}
		Sandbox(const Sandbox&) = delete;

		virtual core::WindowProperties GetWindowProperties() override { return setWinProps(); }

		virtual void Initialize() override {
			camera = core::Factory::GetPerspectiveCamera();

			VA = core::Factory::CreateCubeMesh();
			shader = core::Factory::LoadBasicCamShader();
		}

		virtual void Shutdown() override { }

		virtual void Update(const float& dt) override {
			if (input::keyboard::key(Y_INPUT_KEY_A)) {
				glm::vec3 newPos = camera->GetPos() - glm::vec3(0.2f , 0.f , 0.f); 
				camera->SetPos(newPos);
			}
			if (input::keyboard::key(Y_INPUT_KEY_D)) {
				glm::vec3 newPos = camera->GetPos() + glm::vec3(0.2f , 0.f , 0.f); 
				camera->SetPos(newPos);
			}
		}

		virtual void Render() override {
			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(PushPerspectiveCamera , camera));

			glm::mat4 model = glm::mat4(1.f);
			model = glm::translate(model , pos) * glm::scale(model , size);
			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , VA , shader , model));

			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(PopPerspectiveCamera));
		}

		virtual void ImGuiRender() override {}
};

core::WindowProperties Sandbox::setWinProps() {
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
	
}

/* Machine Y Entry Point Override */
Y::App* CreateApp() {
	return new Y::Sandbox;
}