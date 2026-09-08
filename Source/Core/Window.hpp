#pragma once

#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/ext/vector_double2.hpp>

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
		void pollEvents() { glfwPollEvents(); }
		void swapBuffers() { glfwSwapBuffers(m_handle); }

		void setVSync(bool enabled) {
			glfwSwapInterval(enabled);
		}

		void bindCallbacks();

		int width() const;
		int height() const;
		int framebufferWidth() const {
			int fbWidth, fbHeight;
			glfwGetFramebufferSize(m_handle, &fbWidth, &fbHeight);
			return fbWidth;
		}
		int framebufferHeight() const {
			int fbWidth, fbHeight;
			glfwGetFramebufferSize(m_handle, &fbWidth, &fbHeight);
			return fbHeight;
		}

		bool isKeyJustPressed(int key) const {
			return glfwGetKey(m_handle, key) == GLFW_PRESS;
		}

		glm::dvec2 getCursorPos() {
			glfwGetCursorPos(m_handle, &m_cursorPos.x, &m_cursorPos.y);
			return m_cursorPos;
		}

		GLFWwindow* nativeHandle() { return m_handle; }

	private:
		GLFWwindow* m_handle = nullptr;

		glm::dvec2 m_cursorPos;
		int m_modifiersDown;

		void keyCallback(int key, int scancode, int action, int mods);
		void cursorCallback(double xpos, double ypos) {
			m_cursorPos.x = xpos;
			m_cursorPos.y = ypos;
		}
		void scrollCallback(double xoffset, double yoffset) { /* TODO: push command to queue */ }

	};
} // namespace wiiviz
