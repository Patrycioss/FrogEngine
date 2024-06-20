#include "src/fileIO/FileUtils.hpp"

namespace fe{
  bool FileUtils::Exists(const std::string& _path) {
	if (FILE* file = fopen(_path.c_str(), "r")){
	  fclose(file);
	  return true;
	}
	return false;
  }
  
  std::string FileUtils::ReadTextFile(const std::string& _path) {
	std::ifstream file;

	std::string contents;
	file.open(_path);

	std::string line;

	while (std::getline(file, line)) {
	  contents.append(line);
	  contents.append("\n");
	  line.clear();
	}

	file.close();
	return {contents};
  }
}