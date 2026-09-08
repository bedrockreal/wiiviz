#include "Application.hpp"
#include "AppState.hpp"
#include <Core/Input/InputEvent.hpp>

#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_double2.hpp>
#include <glm/ext/vector_int2.hpp>

using namespace wiiviz;

static void glConfigure() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef	__APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#endif
}

static inline bool gladLoadPointers() {
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

bool Application::init() {
	if (!glfwInit()) return 0;
	glConfigure();

	const int scrWidth = 800;
	const int scrHeight = 600;

	if (!m_window.create(scrWidth, scrHeight, "test")) {
		return 0;
	}
	m_window.activate();
	m_window.setVSync(true);
	m_window.bindCallbacks();

    if (!gladLoadPointers())
    {
        glfwTerminate();
        return 0;
    }

	m_imgui.init(&m_window);
	m_renderer.init();

	m_wiimoteService.start(1);
	return 1;
}

void Application::run() {
	while (!m_window.shouldClose()) {
		m_window.pollEvents();

		glm::ivec2 size = m_window.framebufferSize();
		m_renderer.resize(size.x, size.y);

		m_imgui.beginFrame();

		update();

		m_renderer.beginFrame();
		m_renderer.renderScene(&m_sceneView);
		m_ui.render(nullptr);
		m_renderer.endFrame();

		m_imgui.endFrame();

		m_window.swapBuffers();
	}
}

void Application::quit() {
	m_wiimoteService.stop();

	m_renderer.shutdown();
	m_imgui.shutdown();
	m_window.destroy();

	glfwTerminate();
}

void Application::update() {
	updateInputState();
	m_cameraController.updateCamera(&m_inputState, &m_sceneView.camera);
}

void Application::updateInputState() {
	glm::vec2 newScrollDelta(0.f, 0.f);

	InputEvent ev;
	while (m_window.popEvent(&ev)) {
		switch (ev.type) {
			// printf("ev.type = %d\n", ev.type);
			// as of now, only care about mouse scroll
			case EventType::MouseScroll:
				newScrollDelta += ev.mouseScroll.offset;
				break;
			case EventType::MouseButton:
				// ignore repeat event
				if (ev.mouseButton.action != GLFW_REPEAT) {
					switch (ev.mouseButton.button) {
						case GLFW_MOUSE_BUTTON_LEFT:
							m_inputState.leftMouse = ev.mouseButton.action;
							break;
						case GLFW_MOUSE_BUTTON_RIGHT:
							m_inputState.rightMouse = ev.mouseButton.action;
							break;
						case GLFW_MOUSE_BUTTON_MIDDLE:
							m_inputState.middleMouse = ev.mouseButton.action;
							break;
						default:
							break;
					}
				}
				break;
			default:
				break;
		}
	}
		// printf("shift = %d\n", m_inputState.shift);
		// printf("ctrl = %d\n", m_inputState.ctrl);
		// printf("alt = %d\n", m_inputState.alt);
		// printf("leftMouse = %d\n", m_inputState.leftMouse);
		// printf("rightMouse = %d\n", m_inputState.rightMouse);
		// printf("middleMouse = %d\n", m_inputState.middleMouse);
	
		m_inputState.scrollDelta = newScrollDelta;
		m_inputState.shift = m_window.isModifierDown(GLFW_MOD_SHIFT);
		m_inputState.ctrl = m_window.isModifierDown(GLFW_MOD_CONTROL);
		m_inputState.alt = m_window.isModifierDown(GLFW_MOD_ALT);

		glm::vec2 newMousePos = m_window.getCursorPos();
		m_inputState.mouseDelta = newMousePos - m_inputState.mousePos;
		m_inputState.mousePos = newMousePos;
}

void Application::buildSceneView(const AppState *appState) {
}
