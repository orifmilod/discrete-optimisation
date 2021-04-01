#!/usr/bin/python3
# -*- coding: utf-8 -*-


import subprocess
import os

def solve_it(input_data):
    # Modify this code to run your optimization algorithm
    #Clean the file data
    file = open("data.txt","w")
    file.close()

    f = open("data.txt", "a")
    f.write(input_data)
    f.close()

    solution = 'greedy.cpp' if input_data.replace('\n', ' ').split(' ')[0] == "50" else "d-satur.cpp"
    os.system('g++ -std=c++17 -o sol ' + solution)
    cmd = './sol'
    out = subprocess.run(cmd.split(' '), stdout=subprocess.PIPE)

    os.remove('data.txt')
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

