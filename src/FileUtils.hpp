#pragma once

#include <fstream>

namespace FileUtils{
  
  inline bool Exists(const char* _path){
	if (FILE* file = fopen(_path, "r")){
	  fclose(file);
	  return true;
	}
	return false;
  }
}