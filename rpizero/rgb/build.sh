#!/bin/bash

set -e
./clean.sh
# removing -nostartfiles ==> linking fails b/c it needs _exit: "undefined reference to `_exit'"
arm-none-eabi-g++ -O3 -nostdlib -nostartfiles -std=c++11 --entry=0x8000 main.cpp -o rgb.elf
#arm-none-eabi-nm rgb.elf | c++filt
arm-none-eabi-objcopy rgb.elf -O binary rgb.img
size rgb.elf | tee rgb.size
