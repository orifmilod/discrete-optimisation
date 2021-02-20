#!/usr/bin/python
# -*- coding: utf-8 -*-

from collections import namedtuple
import subprocess
import os


Item = namedtuple("Item", ['index', 'value', 'weight'])

def solve_it(file_location):
    # Modify this code to run your optimization algorithm
    os.system('g++ -std=c++11 solution.cpp')
    cmd  ='./a.out ' + file_location
    out = subprocess.run(cmd.split(' '), stdout=subprocess.PIPE)
    return out.stdout.decode()


if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        print(file_location)

        print(solve_it(file_location))
    else:
        print('This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/ks_4_0)')

