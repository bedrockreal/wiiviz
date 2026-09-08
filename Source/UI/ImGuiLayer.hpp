#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Core/Window.hpp>

namespace wiiviz {
	class ImGuiLayer {
	public:
		bool init(Window *window);
		void shutdown();

		void beginFrame();
		void endFrame();

		// void applyDarkTheme();
	};
} // namespace wiiviz

