#!/bin/bash

set -e
rm -rf *.elf *.img
# removing -nostartfiles ==> linking fails b/c it needs _exit: "undefined reference to `_exit'"
arm-none-eabi-gcc -nostartfiles led.c -o led.elf
arm-none-eabi-objcopy led.elf -O binary led.img

