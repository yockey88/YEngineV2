#include "engine.hpp"
#include "app.hpp"
#include "main.hpp"

namespace Y {
	
class Sandbox : public App {
	core::WindowProperties setWinProps();

	public:
		Sandbox() {}
		Sandbox(const Sandbox&) = delete;

		virtual core::WindowProperties GetWindowProperties() override { return setWinProps(); }

		virtual void Initialize() override {}

		virtual void Shutdown() override { }

		virtual void Update(const float& dt) override {}

		virtual void Render() override {}

		virtual void ImGuiRender() override {}
};

core::WindowProperties Sandbox::setWinProps() {
	core::WindowProperties props;

	props.size.x = 1920;
	props.size.y = 1079;

	props.flags |= SDL_WINDOW_RESIZABLE;
	props.title = "[Machine Y Development v{1.0.2}]";

	return props;
}
	
}

/* Machine Y Entry Point Override */
Y::App* CreateApp() {
	return new Y::Sandbox;
}