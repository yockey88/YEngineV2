#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "glm/glm.hpp"
#include "SDL.h"
#undef main

#include <string>
#include <memory>

using SDL_GLContext = void*;

namespace Y {
namespace graphics {

	class Framebuffer;
	class VertexArray;
	class Shader;

}
namespace core {

	struct WindowProperties {
		glm::ivec2 pos , size , sizeMin;
		glm::vec4 cc;
		int flags;
		float aspectRatio;
		std::string title;

		WindowProperties();
	};

	class Window {
		WindowProperties winProps;
		std::shared_ptr<graphics::Framebuffer> frameBuffer;
		std::shared_ptr<graphics::VertexArray> vertArray;
		std::shared_ptr<graphics::Shader> shader;
		SDL_Window* window;
		SDL_GLContext glContext;
		glm::vec2 fBufferSize;

		int scrnH , scrnW;

		bool open , renderingToScrn;

		void InitializeScrnRender();
		void Clear() {}
		void HandleEvents(SDL_Event &e);
		void RenderToScreen();
		void HandleResize(int width , int height);
		
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

	public:
		Window() : window(nullptr) , open(false) , renderingToScrn(true) {}
		~Window() { Shutdown(); }

		[[nodiscard]] bool Create(const WindowProperties& props);

		void BeginRender();
		void FlushEvents();
		void EndRender();

		void Shutdown();

		inline std::shared_ptr<graphics::Framebuffer> getFrameBuffer() { return frameBuffer; }
		inline SDL_Window* GetSDLWindow() { return window; }
		inline SDL_GLContext GetSDL_GLContext() { return glContext; }
		glm::ivec2 GetSize();
		glm::ivec2 GetCorrectAspectRatioSize(int w , int h);
		inline void SetRenderingToScrn(const bool& flag) { renderingToScrn = flag; }
		inline bool IsOpen() const { return open; }
		inline bool RenderingToScrn() const { return renderingToScrn; }
	};

}
}

#endif /* window.hpp */