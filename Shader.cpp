#include "Shader.hpp"

#include <stdexcept>
#include <fstream>
#include <glad/glad.h>

namespace FrogEngine::Shader
{
  class ShaderException final : public std::runtime_error {
   public:
	explicit ShaderException(const std::string& _message) : runtime_error(_message) {}
  };

  void DebugShader(const unsigned int _shader, const char* _name) {
	int success;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
	  char infoLog[512];
	  glGetShaderInfoLog(_shader, 512, nullptr, infoLog);
	  throw ShaderException("Failed to compile shader '" + std::string(_name) + "' with info: \n'" + std::string(infoLog) + "'\n");
	}
  }

  void DebugShaderProgram(const unsigned int _program) {
	int success;
	glGetProgramiv(_program, GL_LINK_STATUS, &success);

	if (!success) {
	  char infoLog[512];
	  glGetProgramInfoLog(_program, 512, nullptr, infoLog);
	  printf("%s", infoLog);
	  throw ShaderException("Failed to link shader program with info: \n'" + std::string(infoLog) + "'\n");
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

  [[nodiscard]] int GetUniformLocation(ShaderRef _ref, const char* _uniform) {
	const int location = glGetUniformLocation(_ref.ID, _uniform);

	if (location == -1) {
	  printProgramInfoLog(_ref.ID);

	  throw ShaderException("Failed to get location of uniform with name: '" + std::string(_uniform) + "'\n");
	}

	return location;
  }

  void Use(ShaderRef _ref) {
	glUseProgram(_ref.ID);
  }

  std::string ReadTextFile(const std::string& _path) {
	std::ifstream file;

	std::string contents;
	file.open(_path);

	std::string line;

	while (std::getline(file, line)) {
	  contents.append(line);
	  contents.append("\n");
	  line.clear();
	}

	file.close();
	return {contents};
  }

  ShaderRef Create(const std::string& _vertexPath, const std::string& _fragmentPath) {
	const std::string vertexShaderSource = ReadTextFile(_vertexPath);
	printf("Loaded vertex shader source:\n %s\n", vertexShaderSource.c_str());

	const std::string fragmentShaderSource = ReadTextFile(_fragmentPath);
	printf("Loaded fragment shader source:\n %s\n", fragmentShaderSource.c_str());

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

  void SetInteger(ShaderRef _ref, const char* _name, int _value) {
	glUniform1i(GetUniformLocation(_ref, _name), _value);
  }

  void SetVec3(ShaderRef _ref, const char* _name, const glm::vec3& _value) {
	glUniform3f(GetUniformLocation(_ref, _name), _value.x, _value.y, _value.z);
  }

  void SetMatrix4(ShaderRef _ref, const char* _name, const glm::mat4& _value) {
	glUniformMatrix4fv(GetUniformLocation(_ref, _name), 1, false, glm::value_ptr(_value));
  }

  void Delete(ShaderRef _ref) {
	glDeleteProgram(_ref.ID);
  }
}