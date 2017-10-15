#!/bin/bash
SD=/media/petrum/5F5B-7B54
cp led.img $SD && ls -ltr $SD && umount $SD

SEC=10
echo "Rebooting in $SEC sec..."
for i in $(seq $SEC); do
    echo -n "."
    sleep 1
done
echo
reboot-rpi.sh

