#!/bin/bash

problem_name=$1
problem_name=${problem_name##*\\}
test_dir=test/${problem_name}
base_url=${problem_name%_*}
code_path=$2

echo ${problem_name}

# make test directory
if [ ! -e ${test_dir} ]; then
    oj dl -d ${test_dir} https://atcoder.jp/contests/${base_url}/tasks/${problem_name//-/_}
fi

g++ -std=c++17 -g -I header -D_GLIBCXX_DEBUG -Wall -Wextra ${code_path} -o a.exe && oj test -c "./a.exe " -d ${test_dir}
read -p "Hit enter: "