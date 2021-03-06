#! /bin/sh
#
# Copyright (c), Recep Aslantas.
#
# MIT License (MIT), http://opensource.org/licenses/MIT
# Full license can be found in the LICENSE file
#

# check if deps are pulled
git submodule update --init --recursive

cd $(dirname "$0")

# general deps: gcc make autoconf automake libtool cmake

# libxml2
# deps:
#   pkg-config zlib1g-dev node curl libpython-dev
cd ./lib/libxml2
sh ./autogen.sh
./configure
make -j8

# jemalloc
cd ../jemalloc
sh ./autogen.sh
./configure
make -j8

# curl
cd ../curl
sh ./buildconf
./configure
make -j8

# libuv
cd ../libuv
sh ./autogen.sh
./configure
make -j8

# libds
cd ../libds
sh ./autogen.sh
./configure
make -j8

# jansson
cd ../jansson
autoreconf -i
./configure
make -j8

# test - cmocka
cd ../../test/lib/cmocka
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug ..
make -j8
cd ../../../../
