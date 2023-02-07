#include "engine.hpp"
#include "Core/window.hpp"
#include "Core/factory.hpp"
#include "Graphics/framebuffer.hpp"
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"
#include "Graphics/helper.hpp"
#include "Input/mouse.hpp"
#include "Input/keyboard.hpp"
#include "Input/joystick.hpp"

#include "glad/glad.h"

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

static const std::string v_shader = "resources/shaders/window_shader.vert";
static const std::string f_shader = "resources/shaders/window_shader.frag";

namespace Y {
namespace core {

	WindowProperties::WindowProperties() {
		cc.x = static_cast<float>(0x2f) / static_cast<float>(0xFF);
		cc.y = static_cast<float>(0x61) / static_cast<float>(0xFF);
		cc.z = static_cast<float>(0xc4) / static_cast<float>(0xFF);
		cc.w = static_cast<float>(0xFF) / static_cast<float>(0xFF);

		pos.x = SDL_WINDOWPOS_CENTERED;
		pos.y = pos.x;

		size.x = 1920;
		size.y = 1080;

		minSize.x = 1024;
		minSize.y = 576;

		flags = SDL_WINDOW_OPENGL;

		aspectRatio = 16.f / 9.f;

		title = "[Engine Y [NO APPLICATION RUNNING]]";
	}

	void Window::InitializeScrnRender() {

		m_VA = core::Factory::CreateWindowMesh();
		m_Shader = core::Factory::LoadShaderFile(v_shader , f_shader);

		return;
	}

	/* handleEvents() 
		@params--> nothing
		@return--> void
		
		-> filters all SDL and ImGui events into Engine
	*/
	void Window::HandleEvents(SDL_Event &e) {
		switch (e.type) {
			case SDL_KEYDOWN: 
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE: EngineY.Quit(); break;
					default: break;
				}
			break;
			case SDL_WINDOWEVENT: 
				switch (e.window.event) {
					case SDL_WINDOWEVENT_CLOSE: EngineY.Quit(); break;
					case SDL_WINDOWEVENT_RESIZED: HandleResize(e.window.data1 , e.window.data2); break;
					default: break;
				}
			break;
			case SDL_CONTROLLERDEVICEADDED: input::joystick::onJoystickConnected(e.cdevice); break;
			case SDL_CONTROLLERDEVICEREMOVED: input::joystick::onJoystickConnected(e.cdevice); break;
			default: break;
		}

		return;
	}

	void Window::RenderToScreen() {
		Y_ASSERT(m_VA->isValid() , "Attempting to render with invalid VertexArray -> Did you forget to call upload()?");
		if (m_VA->isValid()) {
			glClearColor(0 , 0 , 0 , 1);
			m_VA->bind();
			glBindTexture(GL_TEXTURE_2D , m_FrameBuffer->getTextureID()); Y_CHECK_GL_ERROR;
			m_Shader->bind();

			glm::vec2 scale = m_FBufferSize / (glm::vec2)GetSize();
			glm::mat4 model(1.0);
			model = glm::scale(model , {scale.x , scale.y , 1.f });
			m_Shader->setUniformMat4("model" , model);
			glDrawElements(GL_TRIANGLES , m_VA->getEltCount() , GL_UNSIGNED_INT , 0); Y_CHECK_GL_ERROR;

			m_Shader->unbind();
			glBindTexture(GL_TEXTURE_2D , 0); Y_CHECK_GL_ERROR;
			m_VA->unbind();
		}

		return;
	}

	void Window::HandleResize(int w , int h) {

		int fBufferWidth = (int)(h * m_WinProps.aspectRatio);
		int fBufferHeight = (int)(w * (1.f / m_WinProps.aspectRatio));

		if (h >= fBufferHeight) {
			fBufferHeight = w;
		} else {
			fBufferHeight = h;
		}

		m_FBufferSize = { fBufferWidth , fBufferHeight };

		return;
	}

	bool Window::Create(const WindowProperties& props) {
		m_WinProps = props;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			Y_FATAL("SDL Initialization Failure -> {}" , SDL_GetError());
			return false;
		}

		m_Window = SDL_CreateWindow(props.title.c_str() , props.pos.x , props.pos.y , props.size.x, props.size.y , props.flags);

		if (m_Window == nullptr) {
			Y_FATAL("RENDERER CREATION FAILURE <SDL ERROR>-> {}" , SDL_GetError());
			return false;
		}

#ifdef Y_PLATFORM_MAC
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS , SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK , SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION , 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION , 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER , 1);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE , 8); 

		SDL_SetWindowMinimumSize(m_Window , 200 , 200);

		m_GlContext = SDL_GL_CreateContext(m_Window);
		if (m_GlContext == nullptr) {
			Y_ERROR("OpenGl context is null | See SDL Error -> {}" , SDL_GetError());
			return false;
		}
		gladLoadGLLoader(SDL_GL_GetProcAddress);
			
		m_Open = true;

		m_FrameBuffer = std::make_shared<graphics::Framebuffer>(props.size.x , props.size.y);
		m_FrameBuffer->setClearColor({ props.cc.r , props.cc.g , props.cc.b , props.cc.a });

		InitializeScrnRender();
		HandleResize(props.size.x , props.size.y);

		return true;
	}


	void Window::BeginRender() {
		Y_RENDERER.Clear();
		Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(PushFramebuffer , m_FrameBuffer));
		return;
	}

	void Window::FlushEvents() {
		SDL_Event e;

		while (SDL_PollEvent(&e)) {
			HandleEvents(e);

			input::mouse::update();
			input::keyboard::update();
			input::joystick::update();
		}

		return;
	}

	void Window::EndRender() {

		Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(PopFramebuffer));
		Y_RENDERER.Flush();

		if (m_RenderToScrn) 
			RenderToScreen();

		SDL_GL_SwapWindow(m_Window);

		return;
	}

	void Window::Shutdown() {
		
		if (m_Window != nullptr) SDL_DestroyWindow(m_Window);
		SDL_Quit();

		return;
	}

	glm::ivec2 Window::GetSize() {
		int w , h;
		SDL_GetWindowSize(m_Window , &w , &h);
		return glm::ivec2{w , h};
	}

	glm::ivec2 Window::GetCorrectAspectRatioSize(int w , int h) {

		int fBufferWidth = (int)(h * m_WinProps.aspectRatio);
		int fBufferHeight = (int)(w * (1.f / m_WinProps.aspectRatio));

		if (h >= fBufferHeight) {
			fBufferHeight = w;
		} else {
			fBufferHeight = h;
		}

		return { fBufferWidth , fBufferHeight };

	}

}
}
