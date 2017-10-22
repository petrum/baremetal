#!/bin/bash

set -e
./clean.sh
# removing -nostartfiles ==> linking fails b/c it needs _exit: "undefined reference to `_exit'"
arm-none-eabi-g++ -nostdlib -std=c++11 --entry=0x8000 main.cpp -o led.elf
arm-none-eabi-nm led.elf | c++filt
arm-none-eabi-objcopy led.elf -O binary led.img
size led.elf | tee led.size

