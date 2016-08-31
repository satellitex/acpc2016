#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random

NUMOFCASE = 10

L_MIN = 1
L_MAX = 2000
p_MIN = 0
p_MAX = 100000000
d_MIN = 1
#d_MAX = 2000
c_MIN = 1
c_MAX = 200
S_MIN = 1
S_MAX = 100

seq = 0

def generate():
    global seq

    filename = '50_random_{:02}.in'.format(seq)

    f = open(filename, 'w')
    L = random.randint(L_MIN, L_MAX)
    p = random.random() * p_MAX
    while p < 0.001:
        p = random.random() * p_MAX
    d = random.randint(d_MIN, L)
    f.write("{} {:.3f} {}\n".format(L, p, d));
    S_list = []
    for i in range(L):
        if i is not 0:
            f.write(" ")
        f.write( "{:.3f}".format(max(S_MIN, random.random() * S_MAX)) )

    f.write("\n")
    csum = 0
    for i in range(d):
        if i is not 0:
            f.write(" ")
        #print("{} {} {}".format(L-csum, d-i, L-csum - (d-i) + 1))
        c = random.randint(c_MIN, (L - csum) - (d - i) + 1)
        csum += c
        f.write( "{}".format( random.randint(c_MIN, c) ) )
    f.write("\n")
    f.close()

def main():
    global seq

    for i in range(NUMOFCASE):
        generate()
        seq += 1

if __name__ == '__main__':
    main()
