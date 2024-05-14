#pragma once

#include <unordered_map>

#include "Texture.hpp"

class ResourceManager{
 private:
  static std::unordered_map<const char*, Texture> loadedTextures;
  
 public:
  static Texture& LoadTexture(const char* path, bool hasAlpha);
  static Texture& GetTexture(const char* path);
  static bool UnloadTexture(const char* path);
};