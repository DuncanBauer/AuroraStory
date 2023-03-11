#include <iostream>
#include "Crypto/MapleCryptoConstants.h"

int main(int argc, char** argv)
{
  std::cout << "MapleClient\n";
  std::cout << std::hex;
  for (unsigned int i : MapleCrypto::Constants::BYTE_SHUFFLE)
  {
    std::cout << i << ' ';
  }
  std::cout << std::dec;
  std::cin.ignore(1000, '\n');
}