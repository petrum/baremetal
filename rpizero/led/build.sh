#!/bin/bash

set -e
arm-none-eabi-gcc -O0 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -nostartfiles -g led.c -o led.elf
arm-none-eabi-objcopy led.elf -O binary led.img

