#!/usr/bin/python3
# -*- coding: utf-8 -*-

import random
import itertools

NUMOFCASE = 1

X_MIN = 1
X_MAX = 50
Y_MIN = 1
Y_MAX = 50
Z_MIN = 1
Z_MAX = 50
p_MIN = 0
p_MAX = 50

seq = 0

def generate():
    global seq

    filename = '02_XYZmax_{:02}.in'.format(seq)

    f = open(filename, 'w')
    X = 2
    Y = 5
    Z = 5
    p = X*Y*Z

    material_all = list(itertools.product(range(X), range(Y), range(Z)))
    material = random.sample(material_all, p)

    f.write("{} {} {}\n".format(X, Y, Z))
    f.write("{}\n".format(p))
    for i in range(p):
        f.write("{} {} {}\n".format(material[i][0], material[i][1], material[i][2]))

    possibility = random.randint(0, 10)
    for y in range(Y):
        for x in range(X):
            random_var = random.randint(0, 10)
            v = 0
            if random_var >= possibility:
                v = 1
       	    if x != 0:
                f.write(" ")
            f.write("{}".format(v))
            if x == X-1:
                f.write("\n")
    f.close()

def main():
    global seq

    for i in range(NUMOFCASE):
        generate()
        seq += 1

if __name__ == '__main__':
    main()
