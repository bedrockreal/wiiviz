#include "Renderer.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace wiiviz;

void Renderer::beginFrame() {
	clear();
}

void Renderer::renderScene(const SceneView *scene) {
	RenderContext ctx;
	ctx.view = scene->camera.getViewMatrix();
	ctx.proj = scene->camera.getProjectionMatrix((float)m_viewportWidth / (float)m_viewportHeight);
	ctx.viewProj = ctx.proj * ctx.view;
	ctx.cameraPosition = scene->camera.getPosition();

	m_gridRenderer.render(&ctx);
	for (int i = 0; i < scene->devices.size(); ++i) {
		m_wiimoteRenderer.render(&ctx, &scene->devices[i]);
	}
}

void Renderer::resize(int framebufferWidth, int framebufferHeight) {
	m_viewportWidth = framebufferWidth;
	m_viewportHeight = framebufferHeight;
	updateViewport();
}
