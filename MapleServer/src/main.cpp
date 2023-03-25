#include "Master.h"

#include <iostream>
#include <exception>

int main(int argc, char** argv)
{
  std::cout << "Main\n";
  Master m;
  m.run();
  std::cin.ignore(1000, '\n');
  return 0;
}