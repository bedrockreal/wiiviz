#pragma once

#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <type_traits>

#define DEFINE_SET_UNIFORM_MTX_METHOD(mtxDim)	\
	void setMat##mtxDim(const char *name, const glm::mat##mtxDim& value) {	\
		glUniformMatrix##mtxDim##fv(	\
				glGetUniformLocation(m_program, name),	\
				1,										\
				GL_FALSE,								\
				&value[0][0]);					\
	}

#define DEFINE_SET_UNIFORM_MTX_METHODS()	\
	DEFINE_SET_UNIFORM_MTX_METHOD(2);		\
	DEFINE_SET_UNIFORM_MTX_METHOD(3);		\
	DEFINE_SET_UNIFORM_MTX_METHOD(4);		\
	DEFINE_SET_UNIFORM_MTX_METHOD(2x3);		\
	DEFINE_SET_UNIFORM_MTX_METHOD(3x2);		\
	DEFINE_SET_UNIFORM_MTX_METHOD(2x4);		\
	DEFINE_SET_UNIFORM_MTX_METHOD(4x2);		\
	DEFINE_SET_UNIFORM_MTX_METHOD(3x4);		\
	DEFINE_SET_UNIFORM_MTX_METHOD(4x3)

#define DEFINE_SET_UNIFORM_VEC_METHOD(size)	\
	void setVec##size(const char *name, const glm::vec##size& value) {	\
		glUniform##size##fv(	\
				glGetUniformLocation(m_program, name),	\
				1,										\
				&value[0]);					\
	}

#define DEFINE_SET_UNIFORM_VEC_METHODS()	\
	DEFINE_SET_UNIFORM_VEC_METHOD(2);		\
	DEFINE_SET_UNIFORM_VEC_METHOD(3);		\
	DEFINE_SET_UNIFORM_VEC_METHOD(4)

#define DEFINE_SET_UNIFORM_FLOAT_METHOD(count)	\
	template <typename... Args>					\
	requires (sizeof...(Args) == count			\
			&& (std::same_as<Args, float> && ...))	\
	void setFloat##count(const char *name, Args... values) {	\
		glUniform##count##f(	\
				glGetUniformLocation(m_program, name),	\
				values...);								\
	}

#define DEFINE_SET_UNIFORM_FLOAT_METHODS()	\
	DEFINE_SET_UNIFORM_FLOAT_METHOD(1);		\
	DEFINE_SET_UNIFORM_FLOAT_METHOD(2);		\
	DEFINE_SET_UNIFORM_FLOAT_METHOD(3);		\
	DEFINE_SET_UNIFORM_FLOAT_METHOD(4)

namespace wiiviz {
	struct Shader {
	public:
		// Shader() {}
		// Shader(const char *vsFile, const char *fsFile);
		void loadFromFile(const char *vsFile, const char *fsFile);
		void destroy();

		void bind() const { glUseProgram(m_program); }
		void unbind() const { glUseProgram(0); }

		// wraps glUniform___(...) (risky!)
		template <typename F, typename... Args>
		void doSetUniform(F glFunc, const char *name, const Args&... args) {
			glFunc(glGetUniformLocation(m_program, name), args...);
		}

		DEFINE_SET_UNIFORM_MTX_METHODS();
		DEFINE_SET_UNIFORM_VEC_METHODS();
		DEFINE_SET_UNIFORM_FLOAT_METHODS();
	private:
		GLuint m_program = 0;
		GLuint compile(const char *code, GLenum shaderType, const char *strType);
		void createProgram(GLuint vsHandle, GLuint fsHandle);
		void checkCompileErrors(GLuint shader, const char *type);
	};
} // namespace wiiviz
