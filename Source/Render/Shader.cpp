#include "Shader.hpp"

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <stdlib.h>
#include <string.h>

using namespace wiiviz;

#define __INFO_LOG_SIZE	1024

static char *loadTextFromFile(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		perror(__FUNCTION__);
		return nullptr;
	}

	// Find the size of the file
    fseek(file, 0, SEEK_END);    // Move pointer to the end of the file
    long fileSize = ftell(file); // Get the current pointer position (size in bytes)
    rewind(file);                // Move pointer back to the start of the file
	
	// malloc the string
	char *text = reinterpret_cast<char *>(malloc(fileSize + 1));
	if (text == NULL) {
		perror(__FUNCTION__);
		return nullptr;
	}

	// read all content and return
	size_t bytesRead = fread(text, 1, fileSize, file);
    text[bytesRead] = '\0'; // Manually add the null terminator to make it a valid string
	
	return text;
}

void Shader::loadFromFile(const char *vsFile, const char *fsFile) {
	assert(vsFile != nullptr && fsFile != nullptr);
	char *vsCode = loadTextFromFile(vsFile);
	char *fsCode = loadTextFromFile(fsFile);

	GLuint vsHandle = compile(vsCode, GL_VERTEX_SHADER, "VERTEX");
	GLuint fsHandle = compile(fsCode, GL_FRAGMENT_SHADER, "FRAGMENT");

	createProgram(vsHandle, fsHandle);

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vsHandle);
	glDeleteShader(fsHandle);

	// cleanup
	free(vsCode);
	free(fsCode);
}

GLuint Shader::compile(const char *code, GLenum shaderType, const char *strType) {
	GLuint handle = glCreateShader(shaderType);
	glShaderSource(handle, 1, &code, NULL);
	glCompileShader(handle);
	checkCompileErrors(handle, strType);
	return handle;
}

void Shader::createProgram(GLuint vsHandle, GLuint fsHandle) {
	m_program = glCreateProgram();
	glAttachShader(m_program, vsHandle);
	glAttachShader(m_program, fsHandle);
	glLinkProgram(m_program);
	checkCompileErrors(m_program, "PROGRAM");
}

void Shader::checkCompileErrors(GLuint shader, const char *type)
{
	GLint success;
	GLchar infoLog[__INFO_LOG_SIZE];
	if (strcmp(type, "PROGRAM") != 0)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, __INFO_LOG_SIZE, NULL, infoLog);
			fprintf(stderr, "ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- \n", type, infoLog);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, __INFO_LOG_SIZE, NULL, infoLog);
			fprintf(stderr, "ERROR::SHADER_LINKING_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- \n", type, infoLog);
		}
	}
}
