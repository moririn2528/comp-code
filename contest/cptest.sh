#!/bin/bash

problem_name=$1
problem_name=${problem_name##*\\}
base_url=${problem_name%_*}
contest_site=$2
contest_site=${contest_site##*contest\\}
contest_site=${contest_site%%\\*}
code_path=$2
test_dir=test/${contest_site}/${problem_name}

echo "contest site: ${contest_site}"
echo "problem name: ${problem_name}"

if [ ${contest_site} = "atcoder" ]; then
    contest_url=https://atcoder.jp/contests/${base_url}/tasks/${problem_name//-/_}
fi
if [ ${contest_site} = "codeforces" ]; then
    problem_name=${problem_name##*_}
    contest_url=https://codeforces.com/contest/${base_url}/problem/${problem_name^^}
fi
if [ ${contest_site} = "yukicoder" ]; then
    problem_name=${problem_name##*_}
    contest_url=https://yukicoder.me/problems/no/${problem_name}
fi
if [ ${contest_site} = "aoj" ]; then
    problem_name=${problem_name##*_}
    contest_url=https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=${problem_name}
fi
if [ ${contest_site} = "codechef" ]; then
    problem_name=${problem_name##*_}
    contest_url=https://www.codechef.com/${base_url}/problems/${problem_name^^}
fi


if [ ! -e ${test_dir} ]; then
    oj dl -d ${test_dir} ${contest_url}
fi

g++ -std=c++17 -g -I header -D_GLIBCXX_DEBUG -Wall -Wextra ${code_path} -o a.exe && oj test -c "./a.exe " -d ${test_dir} -D
read -p "Hit enter: "