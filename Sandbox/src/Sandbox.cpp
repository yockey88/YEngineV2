#include "main.hpp"

#include "Core/factory.hpp"
#include "Graphics/camera.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"
#include "Graphics/material.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Y {
	
class Sandbox : public App {
	core::WindowProperties setWinProps();
	std::shared_ptr<graphics::Camera> camera;
	std::shared_ptr<graphics::VertexArray> VA;
	std::shared_ptr<graphics::Material> material;

	glm::vec3 camPos{ 0.f , 0.f , 5.f };
	float camRot = 0.f;

	glm::vec3 pos{ 0.f , 0.f , 1.f } , size{ 1.f , 1.f , 0.f };
	
	public:
		Sandbox() {}
		Sandbox(const Sandbox&) = delete;

		virtual core::WindowProperties GetWindowProperties() override { return setWinProps(); }

		virtual void Initialize() override {
			VA = core::Factory::CreateWhiteSquareMesh();
			std::shared_ptr<graphics::Shader> shader = core::Factory::LoadBasicCamShader();
			material = std::make_shared<graphics::Material>(shader);

			camera = std::make_shared<graphics::Camera>();
			camera->setPos(camPos);
			camera->setViewMat(camPos , camRot);
		}

		virtual void Shutdown() override { }

		virtual void Update(const float& dt) override {}

		virtual void Render() override {
			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(PushCamera , camera));

			glm::mat4 model = glm::mat4(1.f);
			model = glm::translate(model , pos) * glm::scale(model , size);
			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArrayMaterial , VA , material , model));

			Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(PopCamera));
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