#!/bin/bash

script="$(readlink -f $0)"
script_dir="$(dirname $script)"


. "$script_dir/config.sh.in"


rm -rf "$build_dir" "$install_dir"


mkdir -p $build_dir
mkdir -p $install_dir
pushd $build_dir
cmake	-DCMAKE_INSTALL_PREFIX=$install_dir \
		-DADDITIONAL_INCLUDE_DIRS=$include_dir \
		-DADDITIONAL_LINK_DIRS=$link_dir \
		-DCMAKE_BUILD_TYPE=Release \
		$source_dir
make
make install
popd

mkdir -p $install_dir/bin/
cp $link_layer_lib_path $install_dir/bin/
cp $eni_xml_path $install_dir/bin/
