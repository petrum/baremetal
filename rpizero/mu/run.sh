#!/bin/bash
set -e
./build.sh
mkdir -p ~/log
load2rpi.sh mu.img connect

