#pragma once
#include <string>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class ShaderProgram 
{
private:
	unsigned int ID{};
	
public:
	[[nodiscard]] const unsigned int& GetID() const;
	[[nodiscard]] int GetUniformLocation(const char* uniform) const;
	void Use() const;
	explicit ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
	ShaderProgram(const ShaderProgram& shaderProgram);
	
	void SetInteger(const char* name, int value) const;
	void SetVec3(const char* name, const glm::vec3& value) const;
	void SetMatrix4(const char* name, const glm::mat4& value) const;
	
	~ShaderProgram();
};
