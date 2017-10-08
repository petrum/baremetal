#!/bin/bash

arm-none-eabi-g++ -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -c pmain.cpp
arm-none-eabi-as start.asm -o start.o

