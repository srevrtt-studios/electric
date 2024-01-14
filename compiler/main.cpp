#include <iostream>
#include <string>

#include "utils.h"

int main(int argc, char *argv[]) {
  std::string src = Utils::readElectricSrcFile("../test.ectr");
  std::cout << src << std::endl;

  return 0;
}
