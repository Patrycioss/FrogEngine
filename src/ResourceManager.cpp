#include "ResourceManager.hpp"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "FileUtils.hpp"

namespace fe
{
  std::unordered_map<std::string, Texture> ResourceManager::loadedTextures{};
  std::unordered_map<std::string, ShaderRef> ResourceManager::loadedShaders{};
  
  Texture* ResourceManager::LoadTexture(const std::string& _path) {

	if (loadedTextures.contains(_path)){
	  return &loadedTextures.at(_path);
	}
	
	if (!FileUtils::Exists(_path.c_str())){
	  std::cerr << "Path: '" << _path << "' is invalid!\n";
	}
	
	auto ref = loadedTextures.emplace(_path, Texture{GL_RGBA, GL_RGBA});

	int width, height, nrChannels;
	unsigned char* data = stbi_load(_path.c_str(), &width, &height, &nrChannels, 0);
	ref.first->second.Generate(width, height, data);
	stbi_image_free(data);
	return &ref.first->second;
  }

  bool ResourceManager::UnloadTexture(const std::string& _path) {
	return loadedTextures.erase(_path) > 0;
  }

  ShaderRef ResourceManager::CreateShader(const std::string& _name, const std::string& _vertexPath, const std::string& _fragmentPath) {
	
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

  ShaderRef ResourceManager::GetShader(const std::string& _name) {
	return loadedShaders.at(_name);
  }

  bool ResourceManager::UnloadShader(const std::string& _name) {

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