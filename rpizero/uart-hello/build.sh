#!/bin/bash

arm-none-eabi-gcc -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -c pmain.c
arm-none-eabi-as start.asm -o start.o
arm-none-eabi-ld start.o pmain.o -o uart-hello.elf
arm-none-eabi-objcopy uart-hello.elf -O binary uart-hello.bin

