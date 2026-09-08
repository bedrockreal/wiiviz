#pragma once

#include <glm/ext/vector_double2.hpp>
namespace wiiviz {
	struct MouseButtonEvent {
		int button;
		int action;
	};
	struct KeyEvent {
		int key;
		int action;
	};
	struct MouseScrollEvent {
		glm::dvec2 offset;
	};

	enum EventType {
		MouseButton,
		Key,
		MouseScroll
	};

	struct InputEvent {
		EventType type;
		int modifiers;
		union {
			KeyEvent			key;
			MouseButtonEvent	mouseButton;
			MouseScrollEvent	mouseScroll;
		};
	};
} // namespace wiiviz
