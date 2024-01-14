#include <iostream>
#include <string>
#include <fstream>

#include "utils.h"

std::string Utils::readElectricSrcFile(const char *filename) {
  std::string src, line;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "ERROR: Failed to open Electric source file \"" << filename << "\"!" << std::endl;
    exit(1);
  }

  while (std::getline(file, line)) {
    src += line + '\n';
  }

  file.close();
  return src;
}
