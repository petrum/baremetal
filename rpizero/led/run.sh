#!/bin/bash
set -e
SRC=$(dirname "${BASH_SOURCE[0]}")
cd $SRC
./build.sh
mkdir -p ~/log
load2rpi.sh led.img > ~/log/last-load-led.log

