#!/bin/bash

script="$(readlink -f $0)"
script_dir="$(dirname $script)"

insmod /home/mgehrig2/projects/020_EtherCAT/EC-Master-V2.9-Linux_x64-Eval/Sources/LinkOsLayer/Linux/atemsys/atemsys.ko

echo "0000:00:19.0" > /sys/bus/pci/drivers/e1000e/unbind
