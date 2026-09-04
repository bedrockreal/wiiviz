#pragma once

#include <glad/glad.h>

#include <cstdlib>

namespace wiiviz {
	struct Shader {
	public:
		Shader(const char *vsFile, const char *fsFile) {
			load(vsFile, fsFile);
			compile();
			createProgram();
		}
		~Shader() {
			if (vsCode != nullptr) free(vsCode);
			if (fsCode != nullptr) free(fsCode);
		}

		unsigned int ID;
		char *vsCode;
		char *fsCode;
		unsigned int vsHandle;
		unsigned int fsHandle;
		// void activate() {
		// 	glUseProgram(ID);
		// }
	private:
		void load(const char *vsFile, const char *fsFile);
		void compile();
		void createProgram();
		void checkCompileErrors(GLuint shader, const char *type);
	};
} // namespace wiiviz
