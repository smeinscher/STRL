#! /bin/bash

if [ $# -eq 1 ];
then
  cmake -B ./cmake-build-"${1,,}" -S . "-DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_BUILD_TYPE=$1" 
else
  echo "Invalid argument count" 
fi


