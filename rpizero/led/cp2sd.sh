#!/bin/bash
SD=/media/petrum/5F5B-7B54
cp led.img $SD && ls -ltr $SD && umount $SD
sleep 4
reboot-rpi.sh

