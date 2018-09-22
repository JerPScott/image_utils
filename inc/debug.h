#pragma once

#include <iostream>
#include <errno.h>
#include <string.h>

void print_last_error()
{
  char buffer[255];
  std::cerr << strerror_r(errno, buffer, sizeof(buffer));
  std::cerr << std::endl;
}
