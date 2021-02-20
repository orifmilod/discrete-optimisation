#!/usr/bin/python3
# -*- coding: utf-8 -*-

from collections import namedtuple
import subprocess
import os

Item = namedtuple("Item", ['index', 'value', 'weight'])

def solve_it(input_data):
    # Modify this code to run your optimization algorithm
    arr = input_data.replace('\n',' ')
    os.system('g++ -std=c++11 -o sol solution.cpp')
    cmd = './sol ' +arr 
    out = subprocess.run(cmd.split(' '), stdout=subprocess.PIPE)
    return out.stdout.decode()


if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        with open(file_location, 'r') as input_data_file:
            input_data = input_data_file.read()
        print(solve_it(input_data))
    else:
        print('This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/ks_4_0)')


