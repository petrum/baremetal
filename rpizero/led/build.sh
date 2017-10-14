#!/bin/bash

set -e
arm-none-eabi-gcc -O0 -mfpu=vfp -nostartfiles -g led.c -o led.elf
arm-none-eabi-objcopy led.elf -O binary led.img

