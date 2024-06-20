#pragma once

#include <string>
#include <glm.hpp>

namespace fe
{
  /**
   * Contains the ID of the Shader.
   */
  struct ShaderRef {
	uint32_t ID;
  };

  namespace Shader
  {

	/**
	 * Create a Shader.
	 * @param _vertexPath The path to the vertex shader.
	 * @param _fragmentPath The path to the fragment shader.
	 * @return A ShaderRef containing the ID of the Shader.
	 */
	ShaderRef Create(const std::string& _vertexPath, const std::string& _fragmentPath);

	/**
	 * @return The location of the given uniform name.
	 */
	[[nodiscard]] int GetUniformLocation(ShaderRef _ref, const std::string& _uniform);

	/**
	 * Use the shader for rendering purposes.
	 */
	void Use(ShaderRef _ref);

	/**
	 * Set the value of a boolean uniform in the shader.
	 */
	void SetBool(ShaderRef _ref, const std::string& _name, bool _value);

	/**
	 * Set the value of an integer uniform in the shader.
	 */
	void SetInt(ShaderRef _ref, const std::string& _name, int _value);

	/**
	 * Set the value of a float uniform in the shader.
	 */
	void SetFloat(ShaderRef _ref, const std::string& _name, float _value);

	/**
	 * Set the value of a vector3 uniform in the shader.
	 */
	void SetVec3(ShaderRef _ref, const std::string& _name, const glm::vec3& _value);

	/**
	 * Set the value of a vector4 uniform in the shader.
	 */
	void SetVec4(ShaderRef _ref, const std::string& _name, const glm::vec4& _value);

	/**
	 * Set the value of an a 4x4 matrix uniform in the shader.
	 */
	void SetMatrix4(ShaderRef _ref, const std::string& _name, const glm::mat4& _value);

	/**
	 * Delete the shader.
	 */
	void Delete(ShaderRef _ref);
  }
}