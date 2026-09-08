#include "Window.hpp"
#include "Input/InputEvent.hpp"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>

namespace wiiviz {
	template <typename T>
	struct StaticCallbackFactory {};

	template <typename... Args>
	struct StaticCallbackFactory<void(Window::*)(Args...)> {
		using MethodType = void(Window::*)(Args...);
		using StaticCallbackType = void(*)(GLFWwindow*, Args...);

		template <MethodType method>
		static StaticCallbackType create() {
			return [](GLFWwindow *glfwWindow, Args... args) {
				Window *windowInstance = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
				if (windowInstance == nullptr || windowInstance->nativeHandle() != glfwWindow) {
					fprintf(stderr, "Error: GLFW Window User Pointer isn't properly set!\n");
				}
				(windowInstance->*method)(args...);
			};
		}
	};

#define BIND_CALLBACK_TO_METHOD(callbackKind, method)	\
	glfwSet##callbackKind##Callback(				\
			m_handle,								\
			StaticCallbackFactory<decltype(method)>::create<method>())

	void Window::bindCallbacks() {
		// BIND_CALLBACK_TO_METHOD(FramebufferSize, &Window::framebufferSizeCallback);
		BIND_CALLBACK_TO_METHOD(CursorPos, &Window::cursorCallback);
		BIND_CALLBACK_TO_METHOD(Key, &Window::keyCallback);
		BIND_CALLBACK_TO_METHOD(MouseButton, &Window::mouseButtonCallback);
		BIND_CALLBACK_TO_METHOD(Scroll, &Window::scrollCallback);
	}

	// callbacks implementation
	void Window::keyCallback(int key, int scancode, int action, int mods) {
		m_modifiersDown = mods;

		InputEvent event;
		event.type = EventType::Key;
		event.key.key = key;
		event.key.action = action;
		event.modifiers = m_modifiersDown;

		pushEvent(event);
		// printf("keyCallback(%d, %d, %d, %d)\n", key, scancode, action, mods);
	}

	void Window::mouseButtonCallback(int button, int action, int mods) {
		m_modifiersDown = mods;

		InputEvent event;
		event.type = EventType::MouseButton;
		event.mouseButton.button = button;
		event.mouseButton.action = action;
		event.modifiers = m_modifiersDown;

		pushEvent(event);
	}

	void Window::scrollCallback(double xoffset, double yoffset) {
		InputEvent event;
		event.type = EventType::MouseScroll;
		event.mouseScroll.xoffset = xoffset;
		event.mouseScroll.yoffset = yoffset;
		event.modifiers = m_modifiersDown;
		pushEvent(event);
	}

	bool Window::popEvent(InputEvent *ret) {
		if (eventQueue.empty()) return 0;
		memcpy(ret, &eventQueue.front(), sizeof(InputEvent));
		eventQueue.pop();
		return 1;
	}

} // namespace wiiviz
