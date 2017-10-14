#!/bin/bash

set -e
rm -rf *.elf *.img
# removing -nostartfiles ==> linking fails b/c it needs _exit: "undefined reference to `_exit'"
arm-none-eabi-g++ -O3 -nostartfiles -std=gnu11 led.cpp -o led.elf
arm-none-eabi-nm led.elf
arm-none-eabi-objcopy led.elf -O binary led.img

