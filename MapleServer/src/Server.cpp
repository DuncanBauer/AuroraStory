#include "Server.h"

#include <iostream>
#include <exception>

#include <Wz/WzObject.h>


int main(int argc, char** argv)
{
  std::cout << "Server\n";

  Maple::WzObject* ob = new Maple::WzObject("name");
  ob->print();
  delete ob;

  std::cin.ignore(1000, '\n');
  return 0;
}