#!/bin/bash

gcc bianli.c md5.c -Wall -lpthread -o md5_test
./md5_test -f m -o /home/mayday/Desktop/linux_test/ -d /home/mayday/Desktop/linux_test/C/
./md5_test -f a -o /home/mayday/Desktop/linux_test/ -d /home/mayday/Desktop/linux_test/C/

