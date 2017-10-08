#!/bin/bash
./clean.sh

arm-none-eabi-gcc -std=gnu99 -Wall -Wextra -O2 -nostdlib -nostartfiles -ffreestanding  -c pmain.c
arm-none-eabi-as -c start.asm -o start.o

# the order of *.o is important
arm-none-eabi-ld -T boot.ld -o uart-hello.elf -O2 -nostdlib start.o pmain.o
arm-none-eabi-objcopy uart-hello.elf -O binary uart-hello.bin
