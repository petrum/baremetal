#!/bin/bash

set -e
arm-none-eabi-gcc -nostartfiles led.c -o led.elf
arm-none-eabi-objcopy led.elf -O binary led.img

