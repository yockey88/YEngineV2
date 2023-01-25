#include "engine.hpp"
#include "log.hpp"

namespace Y {

	Engine* Engine::m_Instance = nullptr;

	bool Engine::Initialize(App* app) {

        if (!m_Initialized) {
			m_ActiveApp = app;

            if (!m_Window.Create(m_ActiveApp->GetWindowProperties())) {
                return false;
            }
			m_Renderer.Initialize();
			app->Initialize();
			m_Initialized = true;

			return true;
		}

		return false;
	}

	void Engine::Update() {
		
		m_Window.FlushEvents();
		m_ActiveApp->Update((1.f / 60.f));

		return;
	}

	void Engine::Render() {

		m_Window.BeginRender();
		m_ActiveApp->Render();
		m_Window.EndRender();

		return;
	}

	void Engine::Shutdown() {

		m_ActiveApp->Shutdown();
		delete m_ActiveApp;

		m_Renderer.Shutdown();
		m_Window.Shutdown();
		m_Log.Shutdown();
		m_Clock.Stop();

		m_Initialized = false;

		return;
	}

	Engine &Engine::Instance() {

		if (m_Instance == nullptr)
			m_Instance = new Engine;

		return *m_Instance;
	}

	void Engine::GetInfo() {
		Y_INFO("Engine Y {}" , m_Version);
#ifdef Y_CONFIG_DEBUG
		Y_INFO("[CONFIG]--> debug");
#endif
#ifdef Y_CONFIG_RELEASE
		Y_INFO("[CONFIG]--> release");
#endif
#ifdef Y_PLATFORM_WINDOWS
		Y_INFO("[Platform]--> windows");
#endif
#ifdef Y_PLATFORM_LINUX
		Y_INFO("[Platform]--> linux");
#endif
#ifdef Y_PLATFORM_MAC
		Y_INFO("[Platform]--> mac");
#endif
	}

	bool Engine::Run(App* app) {
		m_Clock.Start();
		m_Log.Initialize();
		
		Y_ASSERT((app != nullptr) , "Attempting to Run an Invalid App");
		GetInfo();

		if (!Initialize(app)) {
			Y_FATAL("Engine Initialization Failed");
			m_Log.Shutdown();
			return false;
		}
		Y_INFO("Engine Y V[0.0.2]");

		m_Running = true;
		while (m_Running) {
			Update();
			Render();
		}

		Shutdown();

		return true;
	}

}