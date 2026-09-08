#pragma once

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
		double xoffset;
		double yoffset;
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
