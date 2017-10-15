#!/bin/bash
set -e
./build.sh
mkdir -p ~/log
load2rpi.sh led.img > ~/log/last-load.log

