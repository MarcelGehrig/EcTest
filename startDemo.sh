#!/bin/bash

script="$(readlink -f $0)"
script_dir="$(dirname $script)"

echo "sudo $script_dir/install/bin/myecmasterdemodc -f eni_1MAXON.xml -i8254x 1 1 -perf"

