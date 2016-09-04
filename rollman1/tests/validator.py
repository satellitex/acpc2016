#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import re

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
    m = re.match(r'^(0|[1-9](\d)*) (0|[1-9](\d)*|(\d)+\.(\d)+) (0|[1-9](\d*))$', line)
    assert m, 'strange line \"{}\" at 1'.format(line.strip())
    line_split = line.split()
    L = int(line_split[0])
    p = float(line_split[1])
    d = int(line_split[2])
    assert L_MIN <= L <= L_MAX, 'L out of range: {}'.format(L)
    assert p_MIN < p <= p_MAX, 'rho out of range: {}'.format(p)
    assert d_MIN <= d <= d_MAX, 'd out of range: {}'.format(d)
    assert d <= L, 'd <= L is false, that is, !{} <= {}'.format(d, L)

    lines = sys.stdin.readlines()
    assert len(lines) == 2, '{} extra line(s) detected.'.format( len(lines) )

    S_list = lines[0].split()
    c_list = lines[1].split()

    assert len(S_list) == L, 'Invalid number of argument(s) of S: {}'.format(len(S_list))
    assert len(c_list) == d, 'Invalid number of argument(s) of c: {}'.format(len(c_list))

    for i in S_list:
        s = float(i)
        assert 1 <= s <= 100, 's out of range: {}'.format(s)
    csum = 0
    for i in c_list:
        c = int(i)
        csum += c
        assert 1 <= c <= 200, 'c out of range: {}'.format(c)
    assert csum <= L, 'Too long c: {}'.format(csum)

if __name__ == '__main__':
    main()
