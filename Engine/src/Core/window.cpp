#include "engine.hpp"
#include "factory.hpp"
#include "Core/window.hpp"
#include "Graphics/framebuffer.hpp" 
#include "Graphics/vertex.hpp"
#include "Graphics/shader.hpp"
#include "Graphics/GLErrorHelper.hpp"

#include "glad/glad.h"

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

namespace Y::core {

	WindowProperties::WindowProperties() {
		pos.x = SDL_WINDOWPOS_CENTERED; pos.y = pos.x;
		size.x = 1920; size.y = 1080;
		sizeMin.x = 1024; sizeMin.y = 576;
		flags = SDL_WINDOW_OPENGL;
		aspectRatio = 16.f / 9.f;
		cc.x = static_cast<float>(0x2f) / static_cast<float>(0xFF);
		cc.y = static_cast<float>(0x61) / static_cast<float>(0xFF);
		cc.z = static_cast<float>(0xc4) / static_cast<float>(0xFF);
		cc.w = static_cast<float>(0xFF) / static_cast<float>(0xFF);
		title = "[Engine Y v{0.0.2}]";
	}

	void Window::InitializeScrnRender() {
		vertArray = factory::GetMainWindowVA();
		shader = factory::GetMainWindowShader();
	}

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
			default: break;
		}

		return;
	}

	void Window::RenderToScreen() {
		Y_ASSERT(vertArray->IsValid() , "Attempting to render with invalid VertexArray -> Did you forget to call upload()?");
		if (vertArray->IsValid()) {
			glClearColor(0 , 0 , 0 , 1);
			vertArray->Bind();
			glBindTexture(GL_TEXTURE_2D , frameBuffer->GetTextureID()); Y_CHECK_GL_ERROR;
			shader->Bind();

			glm::vec2 scale = fBufferSize / (glm::vec2)GetSize();
			glm::mat4 model(1.0);
			model = glm::scale(model , {scale.x , scale.y , 1.f });
			shader->SetUniformMat4("model" , model);
			glDrawElements(GL_TRIANGLES , vertArray->GetEltCount() , GL_UNSIGNED_INT , 0); Y_CHECK_GL_ERROR;

			shader->Unbind();
			glBindTexture(GL_TEXTURE_2D , 0); Y_CHECK_GL_ERROR;
			vertArray->Unbind();
		}

		return;
	}

	void Window::HandleResize(int w , int h) {

		int fBufferWidth = (int)(h * winProps.aspectRatio);
		int fBufferHeight = (int)(w * (1.f / winProps.aspectRatio));

		if (h >= fBufferHeight) {
			fBufferHeight = w;
		} else {
			fBufferHeight = h;
		}

		fBufferSize = { fBufferWidth , fBufferHeight };

		return;
	}

	bool Window::Create(const WindowProperties& props) {
		winProps = props;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			Y_FATAL("SDL Initialization Failure -> {}" , SDL_GetError());
			return false;
		}

		window = SDL_CreateWindow(props.title.c_str() , props.pos.x , props.pos.y , props.size.x , props.size.y , props.flags);

		if (window == nullptr) {
			Y_FATAL("WINDOW CREATION FAILURE <SDL ERROR>-> {}" , SDL_GetError());
			return false;
		}

#ifdef MACHY_PLATFORM_MAC
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS , SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK , SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION , 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION , 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER , 1);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE , 8); 

		SDL_SetWindowMinimumSize(window , props.sizeMin.x , props.sizeMin.y);

		glContext = SDL_GL_CreateContext(window);
		if (glContext == nullptr) {
			Y_ERROR("OpenGl context is null | See SDL Error -> {}" , SDL_GetError());
			return false;
		}
		gladLoadGLLoader(SDL_GL_GetProcAddress);

		open = true;

		frameBuffer = std::make_shared<graphics::Framebuffer>(props.size.x , props.size.y);
		glm::vec4 cc = { props.cc.r , props.cc.g , props.cc.b , props.cc.a };
		frameBuffer->SetClearColor(cc);

		InitializeScrnRender();
		HandleResize(props.size.x , props.size.y);

		return true;
	}

	void Window::BeginRender() {
		auto& rm = Y_RENDERER;
		rm.Clear();
		rm.Submit(Y_SUBMIT_RENDER_CMND(PushFramebuffer , frameBuffer));
	}

	void Window::FlushEvents() {
		SDL_Event e;

		while (SDL_PollEvent(&e)) {
			HandleEvents(e);
		}

		return;
	}

	void Window::EndRender() {

		// auto& rm = Y_RENDERER;
		// rm.Submit(Y_SUBMIT_RENDER_CMND(PopFramebuffer));
		// rm.Flush();

		if (RenderingToScrn()) 
			RenderToScreen();

		auto& rm = Y_RENDERER;
		rm.Submit(Y_SUBMIT_RENDER_CMND(PopFramebuffer));
		rm.Flush();

		SDL_GL_SwapWindow(window);

		return;
	}

	void Window::Shutdown() {
		
		if (window != nullptr) SDL_DestroyWindow(window);
		SDL_Quit();

		return;
	}

	glm::ivec2 Window::GetSize() {
		int w , h;
		SDL_GetWindowSize(window , &w , &h);
		return glm::ivec2{w , h};
	}

	glm::ivec2 Window::GetCorrectAspectRatioSize(int w , int h) {

		int fBufferWidth = (int)(h * winProps.aspectRatio);
		int fBufferHeight = (int)(w * (1.f / winProps.aspectRatio));

		if (h >= fBufferHeight) {
			fBufferHeight = w;
		} else {
			fBufferHeight = h;
		}

		return { fBufferWidth , fBufferHeight };

	}

}
