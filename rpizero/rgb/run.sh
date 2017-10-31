#!/bin/bash
set -e
./build.sh
mkdir -p ~/log
load2rpi.sh rgb.img > ~/log/last-load-rgb.log

