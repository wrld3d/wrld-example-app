#!/usr/bin/env bash

curl -L  http://sourceforge.net/projects/astyle/files/latest/download -o astyle.tar.gz
tar -zxvf astyle.tar.gz
rm -f astyle.tar.gz
pushd astyle/build/clang
make
popd
./astyle/build/clang/bin/astyle --style=allman --indent=tab --preserve-date -n --recursive "./*.cpp" "./*.h" "./*.java"
./astyle/build/clang/bin/astyle --style=allman --indent=tab --preserve-date -n --mode=c --recursive "./*.mm"
rm -rf ./astyle