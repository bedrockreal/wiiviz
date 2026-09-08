#pragma once

#include "AppState.hpp"
#include <Core/Window.hpp>
#include <Render/Renderer.hpp>
#include <Render/SceneView.hpp>
#include <UI/UIManager.hpp>
#include <UI/ImGuiLayer.hpp>
#include <Wiimote/Service.hpp>

namespace wiiviz {
	class Application {
	public:
		bool init();
		void run();
		void quit();

	private:
		Window m_window;
		Renderer m_renderer;
		SceneView m_sceneView;
		UIManager m_ui;
		ImGuiLayer m_imgui;
		Wiimote::Service m_wiimoteService;

		AppState m_appState;

		void update();
		void buildSceneView(const AppState *appState);
	};
}
