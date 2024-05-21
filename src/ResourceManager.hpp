#pragma once

#include <unordered_map>

#include "Texture.hpp"
#include "Shader.hpp"

namespace fe
{
  class ResourceManager {
   private:
	std::unordered_map<const char*, Texture> loadedTextures{};
	std::unordered_map<const char*, ShaderRef> loadedShaders{};

   public:
	Texture* LoadTexture(const char* _path, bool _hasAlpha);
	Texture* GetTexture(const char* _path);
	[[nodiscard]] ShaderRef CreateShader(const char* _name, const char* _vertexPath, const char* _fragmentPath);
	[[nodiscard]] ShaderRef GetShader(const char* _name);
	bool UnloadTexture(const char* _path);
	bool UnloadShader(const char* _name);
	
	ResourceManager& operator=(const ResourceManager& other) = delete;
  };
}