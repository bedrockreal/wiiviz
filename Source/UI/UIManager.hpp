#pragma once

#include "UIContext.hpp"

#include <imgui.h>

namespace wiiviz {
	class UIManager {
	public:
		void render(UIContext *ctx) {
			ImGui::Begin("Hello, world!");
			ImGui::End();
		}
	};
} // namespace wiiviz
