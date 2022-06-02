#!/usr/bin/python3
# -*- coding: utf-8 -*-

from collections import namedtuple
import subprocess

Item = namedtuple("Item", ['index', 'value', 'weight'])

def solve_it(file_location):
    # Modify this code to run your optimization algorithm
    cmd = 'g++ -std=c++17 -o sol solution.cpp'
    process = subprocess.Popen(cmd.split(' '))
    stdout, stderr = process.communicate()
    process.communicate()
    cmd = './sol ' + file_location
    out = subprocess.run(cmd.split(' '), stdout=subprocess.PIPE)
    return out.stdout.decode()


if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        with open(file_location, 'r') as input_data_file:
            input_data = input_data_file.read()
        print(solve_it(file_location))
    else:
        print('This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/ks_4_0)')


