#!/bin/bash

set -e
arm-none-eabi-gcc -O0 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mcpu=arm1176jzf-s -nostartfiles -g led.c -o led.elf
arm-none-eabi-objcopy led.elf -O binary led.img

