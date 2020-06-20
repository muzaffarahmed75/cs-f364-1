#!/bin/bash
set -e
trap "rm main" EXIT
g++ -std=c++17 -O2 src/main.cpp src/graph.cpp src/io.cpp -Wl,--stack,268435456 -o main
if [[ ! -d output ]]
then
    mkdir output
fi
set +e
for fn in $@
do
    if [[ ! -f $fn ]]
    then
        continue
    fi
    bsnm=$(basename $fn .txt)
    fnc="${bsnm}_clean.txt"
    fn0="output/${bsnm}.dfs.out.txt"
    fn1="output/${bsnm}.dcsc.out.txt"
    sed /^#/d < $fn > $fnc
    echo -e "-------------------------------------"
    ./main 0 < $fnc > $fn0
    printf "\033[0;33m"
    echo $fn0
    printf "\033[0m"
    tail -n 6 $fn0
    echo -e "\n-------------------------------------"
    ./main 1 < $fnc > $fn1
    printf "\033[0;33m"
    echo $fn1
    printf "\033[0m"
    tail -n 6 $fn1
    echo
    rm $fnc
done
unset fn fnc fn0 fn1