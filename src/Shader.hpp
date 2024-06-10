#pragma once

#include <string>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

namespace fe
{
  struct ShaderRef {
	uint32_t ID;
  };
  
  namespace Shader{
	ShaderRef Create(const std::string& _vertexPath, const std::string& _fragmentPath);

	[[nodiscard]] int GetUniformLocation(ShaderRef _ref, const char* _uniform);
	void Use(ShaderRef _ref);
	void SetBool(ShaderRef _ref, const char* _name, bool _value);
	void SetInt(ShaderRef _ref, const char* _name, int _value);
	void SetFloat(ShaderRef _ref, const char* _name, float _value);
	void SetVec3(ShaderRef _ref, const char* _name, const glm::vec3& _value);
	void SetVec4(ShaderRef _ref, const char* _name, const glm::vec4& _value);
	void SetMatrix4(ShaderRef _ref, const char* _name, const glm::mat4& _value);
	void Delete(ShaderRef _ref);
  }
}