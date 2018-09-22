#!/bin/bash

g++ ./bmp.cpp \
  -o bmp.exe \
  -std=c++11 \
  -Wall -Werror \
  -D__DEBUG__ -g

g++ ./png.cpp \
  -o png.exe \
  -std=c++11 \
  -Wall -Werror \
  -D__DEBUG__ -g
