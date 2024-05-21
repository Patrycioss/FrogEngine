#pragma once

#include <string>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

namespace fe{
  struct ShaderRef {
	uint32_t ID;
  };
}

namespace fe::Shader
{
  
  ShaderRef Create(const std::string& _vertexPath, const std::string& _fragmentPath);

  [[nodiscard]] int GetUniformLocation(ShaderRef _ref, const char* _uniform);
  void Use(ShaderRef _ref);
  void SetInteger(ShaderRef _ref, const char* _name, int _value);
  void SetVec3(ShaderRef _ref, const char* _name, const glm::vec3& _value);
  void SetMatrix4(ShaderRef _ref, const char* _name, const glm::mat4& _value);
  void Delete(ShaderRef _ref);
}