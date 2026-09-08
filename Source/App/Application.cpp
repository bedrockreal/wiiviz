#include "Application.hpp"
#include "AppState.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	m_renderer.resize(scrWidth, scrHeight);

	// set glfw user pointer for callback use
	// glfwSetWindowUserPointer(m_window.nativeHandle(), this);

	m_wiimoteService.start(1);
	return 1;
}

void Application::run() {
	while (!m_window.shouldClose()) {
		m_window.pollEvents();

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

void Application::update() {}

void Application::buildSceneView(const AppState *appState) {
}
