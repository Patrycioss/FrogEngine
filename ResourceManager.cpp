#include "ResourceManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::unordered_map<const char*, Texture> ResourceManager::loadedTextures{};

Texture& ResourceManager::LoadTexture(const char *path, bool hasAlpha) {
  uint32_t format = GL_RGB;
  
  if (hasAlpha){
	format = GL_RGBA;
  }
  
  auto ref = loadedTextures.emplace(path, Texture{format, format});
  
  int width, height, nrChannels;
  unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
  ref.first->second.Generate(width, height, data);
  stbi_image_free(data);
  return ref.first->second;
}

Texture &ResourceManager::GetTexture(const char *path) {
  return loadedTextures.at(path);
}

bool ResourceManager::UnloadTexture(const char *path) {
  return loadedTextures.erase(path) > 0;
}