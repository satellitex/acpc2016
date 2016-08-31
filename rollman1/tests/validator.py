#!/usr/bin/env python3
# -*- coding: utf-8 -*-

L_MIN = 1
L_MAX = 2000
p_MIN = 0
p_MAX = 100000000
d_MIN = 1
d_MAX = 2000
c_MIN = 1
c_MAX = 200
S_MIN = 1
S_MAX = 100

def main():
    line = input()
    assert len(line.split()) == 3, 'Too many or too less argument(s) at line 1'
    m = re.match(r'^
