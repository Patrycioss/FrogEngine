#pragma once

#include <unordered_map>
#include <string>

#include "src/data/Texture.hpp"

namespace fe
{
  /**
   * Used for managing assets that are used in the game.
   */
  class AssetManager {
   private:
	// Delete constructors
	AssetManager() = delete;
	AssetManager(AssetManager& _assetManager) = delete;
	AssetManager(AssetManager&& _assetManager) = delete;
	
	static std::unordered_map<std::string, Texture> loadedTextures;

   public:
	/**
	 * Loads in a texture or if it's already loaded it will return the stored one.
	 * @param _path The file path leading to the texture.
	 * @return A pointer to the loaded texture.
	 */
	static Texture* LoadTexture(const std::string& _path, bool _hardPixels = false);
	
	/**
	 * Tries to unload a texture from memory.
	 * @param _path The file path of the texture.
	 * @return Whether it has succeeded or not.
	 */
	static bool UnloadTexture(const std::string& _path);
  };
}