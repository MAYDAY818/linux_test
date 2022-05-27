##!/bin/bash

gcc bianli.c -lpthread -o bianli

./bianli -f a -o /home/mayday/linux_test/ -d /home/mayday/linux_test/C/
sleep 10
./bianli -f m -o /home/mayday//linux_test/ -d /home/mayday/linux_test/C/
sleep 10
./bianli -f s -o /home/mayday/linux_test/ -d /home/mayday/linux_test/C/
sleep 10
./bianli -f s -o /home/mayday/linux_test/ -l /home/mayday/linux_test/C/ceshi.sh 


