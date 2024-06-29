#pragma once

#include <fstream>

namespace fe{
  
  /**
   * Utilities for interacting with files on disk.s
   */
  class FileUtils{
   private:
	// Delete constructors
	FileUtils() = delete;
	FileUtils(FileUtils& _fileUtils) = delete;
	FileUtils(FileUtils&& _fileUtils) = delete;
	
   public:
	
	/**
	 * @return Whether the specified file path is valid.  
	 */
	static bool Exists(const std::string& _path);
	
	/**
	 * @return A string containing the contents of the file at the specified path. 
	 */
	[[nodiscard]] static std::string ReadTextFile(const std::string& _path);
  };
}