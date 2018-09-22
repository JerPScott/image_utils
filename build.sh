#!/bin/bash

g++ ./bmp.cpp \
  -o ./bin/bmp.exe \
  -std=c++11 \
  -Wall -Werror \
  -D__DEBUG__ -g

g++ ./png.cpp \
  -o ./bin/png.exe \
  -std=c++11 \
  -Wall -Werror \
  -D__DEBUG__ -g
