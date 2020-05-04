#!/bin/bash
SRC=$(dirname "${BASH_SOURCE[0]}")
cd $SRC
set -e
./build.sh
mkdir -p ~/log
load2rpi.sh rgb.img #> ~/log/last-load-rgb.log

