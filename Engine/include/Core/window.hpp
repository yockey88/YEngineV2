#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SDL.h"
#undef main
#include "glm/glm.hpp"

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
		glm::vec4 cc;
		glm::ivec2 pos , size , minSize;
		int flags;
		float aspectRatio;
		std::string title;

		WindowProperties();
	};

	class Window {
		WindowProperties m_WinProps;
		std::shared_ptr<graphics::Framebuffer> m_FrameBuffer;
		std::shared_ptr<graphics::VertexArray> m_VA;
		std::shared_ptr<graphics::Shader> m_Shader;
		SDL_Window* m_Window;
		SDL_GLContext m_GlContext;
		glm::vec2 m_FBufferSize;

		std::string m_VShader , m_FShader;

		glm::ivec2 m_Size;

		bool m_Open , m_RenderToScrn;

		void InitializeScrnRender();
		void clear() {}
		void HandleEvents(SDL_Event &e);
		void RenderToScreen();
		void HandleResize(int width , int height);
		
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

	public:
		Window() : m_Window(nullptr) , m_Open(false) , m_RenderToScrn(true) {}
		~Window() { Shutdown(); }

		[[nodiscard]] bool Create(const WindowProperties& props);

		inline void SetRenderToScrn(bool render) { m_RenderToScrn = render; }
		void BeginRender();
		void FlushEvents();
		void EndRender();

		void Shutdown();
		
		inline SDL_Window* GetSDLWindow() { return m_Window; }
		inline SDL_GLContext GetSDL_GLContext() { return m_GlContext; }
		inline std::shared_ptr<graphics::Framebuffer> GetFrameBuffer() { return m_FrameBuffer; }
		glm::ivec2 GetSize();
		glm::ivec2 GetCorrectAspectRatioSize(int w , int h);
		inline bool IsOpen() const { return m_Open; }
		inline bool ShouldRenderToScrn() const { return m_RenderToScrn; } 
	};

}
}

#endif /* window.hpp */