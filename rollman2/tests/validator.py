#!/Users/kagetaku/.pyenv/shims/python3
# -*- coding: utf-8 -*-

import sys
import re

X_MIN = 1
X_MAX = 50
Y_MIN = 1
Y_MAX = 50
Z_MIN = 1
Z_MAX = 50
p_MIN = 0
p_MAX = 50

def main():
    line = input()
    assert len(line.split()) == 3, 'Too many or too less argument(s) at line 1'
    m = re.match(r'^(0|[1-9](\d)*) (0|[1-9](\d)*) (0|[1-9](\d*))$', line)
    assert m, 'strange line \"{}\" at 1'.format(line.strip())
    line_split = line.split()
    X = int(line_split[0])
    Y = float(line_split[1])
    Z = int(line_split[2])
    assert X_MIN <= X <= X_MAX, 'X out of range: {}'.format(X)
    assert Y_MIN <= Y <= Y_MAX, 'Y out of range: {}'.format(Y)
    assert Z_MIN <= Z <= Z_MAX, 'Z out of range: {}'.format(Z)

    line = input()
    m = re.match(r'^(0|[1-9](\d)*)$', line)
    assert m, 'strange line \"{}\"'.format(line)
    p = int(line)
    assert p_MIN <= p <= p_MAX, 'p out of range: {}'.format(p)

    lines = sys.stdin.readlines()
    assert len(lines) == p+Y, '{} extra line(s) detected.'.format( p+Y-len(lines) )

    coord_list = []

    for index, line in enumerate(lines[0:p]):
        m = re.match(r'^(0|[1-9](\d)*) (0|[1-9](\d)*) (0|[1-9](\d)*)$', line)
        assert m, 'strange line \"{}\" at {}'.format(line, 3+index)
        stripped = line.split()
        x = int(stripped[0])
        y = int(stripped[1])
        z = int(stripped[2])
        assert 0 <= x < X, 'x out of range: {} at {}'.format(x, 3+index)
        assert 0 <= y < Y, 'y out of range: {} at {}'.format(x, 3+index)
        assert 0 <= z < Z, 'z out of range: {} at {}'.format(x, 3+index)
        coord_list.append((x, y, z))
    t = set()
    tt = [x for x in coord_list if x in t or t.add(x)]
    assert tt == [], 'material duplicated:\n  {}'.format(tt)

    #net_pattern = r'^'
    #for i in range(X):
    #    if i != 0:
    #        net_pattern += r' '
    #    net_pattern += r'(0|1)'
    #net_pattern += r'$'

    for index, line in enumerate(lines[p:len(lines)-1]):
        # python bawled up 'sorry, but this version only supports 100 named groups'
        # m = re.match(net_pattern, line)
        assert len(line) == 2*X, 'Too many or less arguments at {}'.format(3+p+index)       # paying attention to return code.
        for i in range(len(line)-1):
            if i % 2 == 0 :
                assert (line[i] == '0') or (line[i] == '1'), 'strange line at {}\n i = {}, line[i] = {}'.format(3+p+index, i, line[i])
            else:
                assert line[i] == ' ', 'strange line at {}\n i = {}, line[i] = {}'.format(3+p+index, i, line[i])
        assert line[len(line) - 1] == '\n'
if __name__ == '__main__':
    main()
