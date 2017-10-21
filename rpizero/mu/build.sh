#!/bin/bash

set -e
./clean.sh

arm-none-eabi-g++ -O3 -nostartfiles -std=c++11 --entry=0x8000 main.cpp -o mu.elf
arm-none-eabi-nm mu.elf
arm-none-eabi-objcopy mu.elf -O binary mu.img
size mu.elf | tee mu.size

