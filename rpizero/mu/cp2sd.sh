#!/bin/bash
set -e
SD=/media/petrum/5F5B-7B54
echo 'kernel=mu.img' > $SD/config.txt
cat $SD/config.txt
cp mu.img $SD && ls -ltr $SD && umount $SD

SEC=10
echo "Rebooting in $SEC sec..."
for i in $(seq $SEC); do
    echo -n "."
    sleep 1
done
echo
reboot-rpi.sh

