#!/usr/bin/python3
# -*- coding: utf-8 -*-


import subprocess
import os

def solve_it(input_data):
    # Modify this code to run your optimization algorithm
    arr = input_data.replace('\n',' ')
    os.system('g++ -std=c++17 -o sol solution2.cpp')
    cmd = './sol ' + arr
    out = subprocess.run(cmd.split(' '), stdout=subprocess.PIPE)
    return out.stdout.decode()

import sys

if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        with open(file_location, 'r') as input_data_file:
            input_data = input_data_file.read()
        print(solve_it(input_data))
    else:
        print('This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/gc_4_1)')

