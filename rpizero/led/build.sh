#!/bin/bash

set -e
rm -rf *.elf *.img
# removing -nostartfiles ==> linking fails b/c it needs _exit: "undefined reference to `_exit'"
arm-none-eabi-gcc -O3 -nostartfiles -std=gnu11 led.c -o led.elf
arm-none-eabi-nm led.elf
arm-none-eabi-objcopy led.elf -O binary led.img

