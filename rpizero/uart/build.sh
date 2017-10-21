#!/bin/bash

set -e
./clean.sh

arm-none-eabi-g++ -O3 -nostartfiles -std=c++11 --entry=0x8000 main.cpp -o uart.elf
arm-none-eabi-nm uart.elf
arm-none-eabi-objcopy uart.elf -O binary uart.img
size uart.elf | tee uart.size

