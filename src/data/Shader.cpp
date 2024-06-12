#include "src/data/Shader.hpp"

#include <stdexcept>
#include <glad/glad.h>
#include <gtc/type_ptr.hpp>

#include "src/fileIO/FileUtils.hpp"

namespace fe::Shader
{
  void DebugShader(const unsigned int _shader, const char* _name) {
	int success;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
	  char infoLog[512];
	  glGetShaderInfoLog(_shader, 512, nullptr, infoLog);
	  throw std::runtime_error("Failed to compile shader '" + std::string(_name) + "' with info: \n'" + std::string(infoLog) + "'\n");
	}
  }

  void DebugShaderProgram(const unsigned int _program) {
	int success;
	glGetProgramiv(_program, GL_LINK_STATUS, &success);

	if (!success) {
	  char infoLog[512];
	  glGetProgramInfoLog(_program, 512, nullptr, infoLog);
	  printf("%s", infoLog);
	  throw std::runtime_error("Failed to link shader program with info: \n'" + std::string(infoLog) + "'\n");
	}
  }

  void printProgramInfoLog(GLuint _obj) {
	int infologLength = 0;
	int charsWritten = 0;
	char* infoLog;

	glGetProgramiv(_obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0) {
	  infoLog = (char*)malloc(infologLength);
	  glGetProgramInfoLog(_obj, infologLength, &charsWritten, infoLog);
	  printf("%s\n", infoLog);
	  free(infoLog);
	}
  }

  ShaderRef Create(const std::string& _vertexPath, const std::string& _fragmentPath) {
	const std::string vertexShaderSource = FileUtils::ReadTextFile(_vertexPath);
//	printf("Loaded vertex shader source:\n %s\n", vertexShaderSource.c_str());

	const std::string fragmentShaderSource = FileUtils::ReadTextFile(_fragmentPath);
//	printf("Loaded fragment shader source:\n %s\n", fragmentShaderSource.c_str());

	const char* vertSSource = vertexShaderSource.c_str();
	const char* fragSSource = fragmentShaderSource.c_str();

	const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSSource, nullptr);
	glCompileShader(vertexShader);

	DebugShader(vertexShader, "VERTEX");

	const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSSource, nullptr);
	glCompileShader(fragmentShader);

	DebugShader(fragmentShader, "FRAGMENT");

	uint32_t ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	DebugShaderProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return ShaderRef{ID};
  }

  [[nodiscard]] int GetUniformLocation(ShaderRef _ref, const std::string& _uniform) {
	const int location = glGetUniformLocation(_ref.ID, _uniform.c_str());

	if (location == -1) {
	  printProgramInfoLog(_ref.ID);

	  throw std::runtime_error("Failed to get location of uniform with name: '" + std::string(_uniform) + "'\n");
	}

	return location;
  }

  void Use(ShaderRef _ref) {
	glUseProgram(_ref.ID);
  }

  void SetBool(ShaderRef _ref, const std::string& _name, bool _value) {
	glUniform1i(GetUniformLocation(_ref, _name), _value);
  }

  void SetInt(ShaderRef _ref, const std::string& _name, int _value) {
	glUniform1i(GetUniformLocation(_ref, _name), _value);
  }

  void SetFloat(ShaderRef _ref, const std::string& _name, float _value) {
	glUniform1f(GetUniformLocation(_ref, _name), _value);
  }

  void SetVec3(ShaderRef _ref, const std::string& _name, const glm::vec3& _value) {
	glUniform3f(GetUniformLocation(_ref, _name), _value.x, _value.y, _value.z);
  }

  void SetVec4(ShaderRef _ref, const std::string& _name, const glm::vec4& _value) {
	glUniform4f(GetUniformLocation(_ref, _name), _value.x, _value.y, _value.z, _value.a);
  }

  void SetMatrix4(ShaderRef _ref, const std::string& _name, const glm::mat4& _value) {
	glUniformMatrix4fv(GetUniformLocation(_ref, _name), 1, false, glm::value_ptr(_value));
  }

  void Delete(ShaderRef _ref) {
	glDeleteProgram(_ref.ID);
  }
}