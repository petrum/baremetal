#!/bin/bash
set -e
ID=$1
FILE=$2

SD=/media/petrum/$ID
echo "kernel=$FILE" > $SD/config.txt
cat $SD/config.txt
./build.sh

cp $FILE $SD && ls -ltr $SD && umount $SD

SEC=10
echo "Rebooting in $SEC sec..."
for i in $(seq $SEC -1 1); do
    echo -n "$i "
    sleep 1
done
echo
reboot-rpi.sh

