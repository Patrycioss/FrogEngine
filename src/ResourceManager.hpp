#pragma once

#include <unordered_map>

#include "Texture.hpp"
#include "Shader.hpp"

namespace fe
{
  class ResourceManager {
   private:
	static std::unordered_map<std::string, Texture> loadedTextures;
	static std::unordered_map<std::string, ShaderRef> loadedShaders;

   public:
	static Texture* LoadTexture(const std::string& _path);
	[[nodiscard]] static ShaderRef CreateShader(const std::string& _name, const std::string& _vertexPath, const std::string& _fragmentPath);
	[[nodiscard]] static ShaderRef GetShader(const std::string& _name);
	static bool UnloadTexture(const std::string& _path);
	static bool UnloadShader(const std::string& _name);
  };
}