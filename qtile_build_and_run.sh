#! /bin/bash

if [ $# -eq 3 ];
then
  cd ./cmake-build-$3/$1
  cmake --build .
  qtile run-cmd --float ./$2
else
  echo "Invalid argument count"
fi
