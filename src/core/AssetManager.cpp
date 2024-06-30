#include "src/core/AssetManager.hpp"

#include <stdexcept>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "src/fileIO/FileUtils.hpp"

namespace fe
{
  std::unordered_map<std::string, Texture> AssetManager::loadedTextures{};
  
  Texture* AssetManager::LoadTexture(const std::string& _path, bool _hardPixels) {

	if (loadedTextures.contains(_path)){
	  return &loadedTextures.at(_path);
	}
	
	if (!FileUtils::Exists(_path)){
	  throw std::runtime_error("Path: '" + _path + "' is invalid!");
	}
	

	int width, height, nrChannels;
	unsigned char* data = stbi_load(_path.c_str(), &width, &height, &nrChannels, 0);
	
	uint32_t format = GL_RGB;
	if (nrChannels > 3){
	  format = GL_RGBA;
	}

	auto ref = loadedTextures.emplace(_path, Texture{format, _hardPixels});
	
	ref.first->second.Generate(width, height, data);
	stbi_image_free(data);
	return &ref.first->second;
  }

  bool AssetManager::UnloadTexture(const std::string& _path) {
	return loadedTextures.erase(_path) > 0;
  }
}