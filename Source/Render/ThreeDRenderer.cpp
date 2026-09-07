#include "ThreeDRenderer.hpp"
#include "Shader.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace wiiviz;

#define GL_BIND_SHADER_UNIFORM(progID, varName, varType)	\
	glUniform##varType(								\
			glGetUniformLocation(progID, #varName),	\
			1,										\
			GL_FALSE,								\
			glm::value_ptr(varName))

void ThreeDRenderer::beginFrame() {
	// clear the screen: should be done by window class

	// set the viewport
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	// setup MVP
	// note: the model matrix is model-specific, so it's not stored here
	view		= camera.getView();
	projection	= glm::perspective(
			projectionParams.fov,
			(float)(display_w) / (float)(display_h),
			projectionParams.nearZ,
			projectionParams.farZ);
}

void ThreeDRenderer::renderScene() {
}

void ThreeDRenderer::useShader(Shader *shader) {
	activeShader = shader;
	shader->bind();

	shader->setMat4("model", glm::mat4(1.0f));
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);
}
