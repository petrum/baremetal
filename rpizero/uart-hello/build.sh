#!/bin/bash

arm-none-eabi-gcc -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -c pmain.c
arm-none-eabi-as start.asm -o start.o

