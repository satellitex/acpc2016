#!/bin/bash

if [ $# -lt 2 ]; then
  echo "usage: ./differ.sh [file1.cpp] [file2.cpp] (optional [judge.cc])"
else
  # 対象
  \clang++ -O2 -std=c++1z $1 -o __differ_sh_runnable_1
  \clang++ -O2 -std=c++1z $2 -o __differ_sh_runnable_2

  if [ $# -eq 3 ]; then
    # 出力検証器
    \clang++ -O2 -std=c++1z $3 -o __differ_sh_judge_cc
  fi

  for file in `\find . -name "in*.txt"`; do
    ./__differ_sh_runnable_1 < $file > __differ_sh_1.out
    ./__differ_sh_runnable_2 < $file > __differ_sh_2.out

    if [ $# -eq 3 ]; then
      ./__differ_sh_judge_cc __differ_sh_1.out __differ_sh_2.out > /dev/null 2>&1
    else
      diff __differ_sh_1.out __differ_sh_2.out > /dev/null 2>&1
    fi

    if [ $? -eq 0 ]; then
      echo -e "\033[0;32mSuccess: \"${file}\"\033[0;39m"
    else
      echo -e "\033[0;31mFailed: \"${file}\"\033[0;39m"
      echo "< $(<__differ_sh_1.out)"
      echo "> $(<__differ_sh_2.out)"
    fi
  done
  rm __differ_sh_runnable_1 __differ_sh_runnable_2 __differ_sh_judge_cc __differ_sh_1.out __differ_sh_2.out
fi