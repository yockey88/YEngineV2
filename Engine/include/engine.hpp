#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "app.hpp"

#include "Core/timer.hpp"
#include "Managers/logManager.hpp" 
#include "Managers/renderManager.hpp" 

#include <iostream>
#include <chrono>
#include <memory>

#define EngineY Y::Engine::Instance()
#define Y_APP Y::Engine::Instance().GetApp()
#define Y_WINDOW Y::Engine::Instance().GetWindow()
#define Y_LOG Y::Engine::Instance().GetLog()
#define Y_RENDERER Y::Engine::Instance().GetRenderer()

namespace Y {

	struct EntryPoint {

	};

	class Engine {
		static Engine* m_Instance;
        App* m_ActiveApp;

		core::Timer m_Clock;
		core::Window m_Window;

		managers::LogManager m_Log;
		managers::RenderManager m_Renderer;

		bool m_Initialized, m_Running;
        std::string m_Version;

		Engine() : m_ActiveApp(nullptr) , m_Initialized(false), m_Running(false) , m_Version("{0.0.2}") {}

		[[nodiscard]] bool Initialize(App* app);
		void Update();
		void UpdateInput();
		void Render();
		void Shutdown();
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		public:
			static Engine& Instance();
			~Engine() { Shutdown();  }
			
			// RuntimeConfig ConfigEngine(AppConfig configuration || App* app);
				// <R -> ||> Depends on if we want to do something with the APP or the APP'S DATA </R>
			// <?> AppRuntimeData </?> Initialize(App* appToInit , RuntimeConfig configToInit);
			// Run(App* appToRun , AppRuntimeData dataNeededToRunApp);

			void GetInfo();
			bool Run(App* app);
			inline void Quit() { m_Running = false; }
			inline App& GetApp() { return *m_ActiveApp; }
			inline core::Window& GetWindow() { return m_Window; }
			inline managers::LogManager& GetLog() { return m_Log; }
			inline managers::RenderManager& GetRenderer() { return m_Renderer; }
	};

}

#endif