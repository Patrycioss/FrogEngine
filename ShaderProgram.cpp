#include "ShaderProgram.hpp"

#include <stdexcept>
#include <fstream>

class ShaderProgramException final : public std::runtime_error {
 public:
  explicit ShaderProgramException(const std::string &message) : runtime_error(message) {}
};

void DebugShader(const unsigned int shader, const char *name) {
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
	char infoLog[512];
	glGetShaderInfoLog(shader, 512, nullptr, infoLog);
	throw ShaderProgramException("Failed to compile shader '" + std::string(name) + "' with info: \n'" + std::string(infoLog) + "'\n");
  }
}

void DebugShaderProgram(const unsigned int program) {
  int success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (!success) {
	char infoLog[512];
	glGetProgramInfoLog(program, 512, nullptr, infoLog);
	printf("%s", infoLog);
	throw ShaderProgramException("Failed to link shader program with info: \n'" + std::string(infoLog) + "'\n");
  }
}

void printProgramInfoLog(GLuint obj) {
  int infologLength = 0;
  int charsWritten = 0;
  char *infoLog;

  glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

  if (infologLength > 0) {
	infoLog = (char *)malloc(infologLength);
	glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
	printf("%s\n", infoLog);
	free(infoLog);
  }
}

const unsigned int &ShaderProgram::GetID() const {
  return ID;
}

[[nodiscard]] int ShaderProgram::GetUniformLocation(const char *uniform) const {
  const int location = glGetUniformLocation(ID, uniform);

  if (location == -1) {
	printProgramInfoLog(ID);
	printf("%s \n", glIsProgram(ID) ? "YES" : "NO");

	throw ShaderProgramException("Failed to get location of uniform with name: '" + std::string(uniform) + "'\n");
  }

  return location;
}

void ShaderProgram::Use() const {
  glUseProgram(ID);
}

std::string ReadTextFile(const std::string &path) {
  std::ifstream file;

  std::string contents;
  file.open(path);

  std::string line;

  while (std::getline(file, line)) {
	contents.append(line);
	contents.append("\n");
	line.clear();
  }

  file.close();
  return {contents};
}

ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) {
  const std::string vertexShaderSource = ReadTextFile(vertexPath);
  printf("Loaded vertex shader source:\n %s\n", vertexShaderSource.c_str());

  const std::string fragmentShaderSource = ReadTextFile(fragmentPath);
  printf("Loaded fragment shader source:\n %s\n", fragmentShaderSource.c_str());

  const char *vertSSource = vertexShaderSource.c_str();
  const char *fragSSource = fragmentShaderSource.c_str();

  const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertSSource, nullptr);
  glCompileShader(vertexShader);

  DebugShader(vertexShader, "VERTEX");

  const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragSSource, nullptr);
  glCompileShader(fragmentShader);

  DebugShader(fragmentShader, "FRAGMENT");

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  DebugShaderProgram(ID);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {
  printf("Deleting shader program \n");
  glDeleteProgram(ID);
}

ShaderProgram::ShaderProgram(const ShaderProgram &shaderProgram) {
  ID = shaderProgram.ID;
}

void ShaderProgram::SetInteger(const char *name, int value) const {
  glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetVec3(const char *name, const glm::vec3 &value) const {
  glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void ShaderProgram::SetMatrix4(const char *name, const glm::mat4 &value) const {
  glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(value));
}