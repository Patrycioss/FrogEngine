#include "ResourceManager.hpp"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace FrogEngine
{
  Texture* ResourceManager::LoadTexture(const char* _path, bool _hasAlpha) {
	uint32_t format = GL_RGB;

	if (_hasAlpha) {
	  format = GL_RGBA;
	}

	auto ref = loadedTextures.emplace(_path, Texture{format, format});

	int width, height, nrChannels;
	unsigned char* data = stbi_load(_path, &width, &height, &nrChannels, 0);
	ref.first->second.Generate(width, height, data);
	stbi_image_free(data);
	return &ref.first->second;
  }

  Texture* ResourceManager::GetTexture(const char* _path) {
	return &loadedTextures.at(_path);
  }

  bool ResourceManager::UnloadTexture(const char* _path) {
	return loadedTextures.erase(_path) > 0;
  }

  ShaderRef ResourceManager::CreateShader(const char* _name, const char* _vertexPath, const char* _fragmentPath) {
	
	auto t = loadedShaders.find(_name);
	ShaderRef shader = Shader::Create(_vertexPath, _fragmentPath);
	
	if (loadedShaders.contains(_name)){
	  	Shader::Delete(loadedShaders[_name]);
		loadedShaders[_name] = shader;
	}
	else {
	  loadedShaders.emplace(_name, shader);
	}
	
	return shader;
  }

  ShaderRef ResourceManager::GetShader(const char* _name) {
	return loadedShaders.at(_name);
  }

  bool ResourceManager::UnloadShader(const char* _name) {

	auto t = loadedShaders.find(_name);
	
	if (t == loadedShaders.end()) 
	  return false;
	
	ShaderRef value = t->second;
	printf("Deleting shader program with ID: {%u} \n", value.ID);
	glDeleteProgram(value.ID);
	
	loadedShaders.erase(t);
	
	return true;
  }
}