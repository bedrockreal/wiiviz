#pragma once

#include "Input/InputEvent.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/ext/vector_double2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <queue>

static int modifiersPressed;

namespace wiiviz {
	class Window {
	public:
		bool create(int width, int height, const char* title) {
			m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);

			// set glfw user pointer for callback use
			glfwSetWindowUserPointer(m_handle, this);

			return m_handle != nullptr;
		}

		void activate() { glfwMakeContextCurrent(m_handle); }
		void destroy() { glfwDestroyWindow(m_handle); }

		bool shouldClose() const {
			return glfwWindowShouldClose(m_handle);
		}
		void pollEvents() {
			// before polling glfw, clear the event queue
			while (!eventQueue.empty()) eventQueue.pop();
			glfwPollEvents();
		}
		void swapBuffers() { glfwSwapBuffers(m_handle); }

		void setVSync(bool enabled) {
			glfwSwapInterval(enabled);
		}

		void bindCallbacks();

		int width() const;
		int height() const;

		glm::ivec2 framebufferSize() const {
			glm::ivec2 ret;
			glfwGetFramebufferSize(m_handle, &ret.x, &ret.y);
			return ret;
		}
		bool isKeyDown(int key) const {
			return glfwGetKey(m_handle, key) == GLFW_PRESS;
		}

		bool isModifierDown(int mod) const {
			return m_modifiersDown & mod;
		}

		glm::dvec2 getCursorPos() {
			glfwGetCursorPos(m_handle, &m_cursorPos.x, &m_cursorPos.y);
			return m_cursorPos;
		}

		GLFWwindow* nativeHandle() { return m_handle; }

		bool popEvent(InputEvent *ret);

	private:
		GLFWwindow* m_handle = nullptr;

		glm::dvec2 m_cursorPos;
		int m_modifiersDown;

		// void framebufferSizeCallback(int width, int height) {
		// 	// m_framebufferSize = glm::ivec2(width, height);
		// }
		void cursorCallback(double xpos, double ypos) {
			m_cursorPos.x = xpos;
			m_cursorPos.y = ypos;
		}

		std::queue<InputEvent> eventQueue;
		void pushEvent(InputEvent event) { eventQueue.push(event); }

		void keyCallback(int key, int scancode, int action, int mods);
		void mouseButtonCallback(int button, int action, int mods);
		void scrollCallback(double xoffset, double yoffset);
	};
} // namespace wiiviz
