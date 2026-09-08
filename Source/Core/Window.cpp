#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <concepts>
#include <cstdio>
#include <type_traits>

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
		BIND_CALLBACK_TO_METHOD(Key, &Window::keyCallback);
		BIND_CALLBACK_TO_METHOD(CursorPos, &Window::cursorCallback);
	}

	// callbacks implementation
	void Window::keyCallback(int key, int scancode, int action, int mods) {
		m_modifiersDown = mods;
		printf("keyCallback(%d, %d, %d, %d)\n", key, scancode, action, mods);
	}

} // namespace wiiviz
