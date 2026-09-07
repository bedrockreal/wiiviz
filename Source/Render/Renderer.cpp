#include "Renderer.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace wiiviz;

extern Camera camera;

void Renderer::beginFrame() {
	clear();
}

void Renderer::renderScene() {
}

void Renderer::resize(int framebufferWidth, int framebufferHeight) {
	m_viewportWidth = framebufferWidth;
	m_viewportHeight = framebufferHeight;
	updateViewport();
}
