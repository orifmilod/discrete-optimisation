#!/usr/bin/python
# -*- coding: utf-8 -*-

import math
from collections import namedtuple
from ortools.constraint_solver import pywrapcp

def length(point1, point2):
    return math.sqrt((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2)

def create_data_model(input_data):
    """Stores the data for the problem."""
    data = {}


    arr = input_data.split('\n')
    n = int(arr[0])
    data['distance_matrix'] = [[0 for x in range(n)] for y in range(n)]

    points = []
    for i in range(n):
        x,y  = arr[i + 1].split(' ')
        points.append([float(x), float(y)])

    for i in range(len(points)):
        for j in range(len(points)):
            a = points[i]
            b = points[j]
            dist = length(a, b)
            print(dist)
            print(a, b, dist)
            data['distance_matrix'][i][j] = dist

    data['num_vehicles'] = 1
    data['depot'] = 0
    return data


def distance_callback(from_index, to_index, manager, data):
    """Returns the distance between the two nodes."""
    # Convert from routing variable Index to distance matrix NodeIndex.
    from_node = manager.IndexToNode(from_index)
    to_node = manager.IndexToNode(to_index)
    return data['distance_matrix'][from_node][to_node]



def solve_it(input_data):
    data = create_data_model(input_data)
    manager = pywrapcp.RoutingIndexManager(len(data['distance_matrix']),
                                           data['num_vehicles'], data['depot'])
    routing = pywrapcp.RoutingModel(manager)
    transit_callback_index = routing.RegisterTransitCallback(distance_callback)

import sys

if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        with open(file_location, 'r') as input_data_file:
            input_data = input_data_file.read()
        print(solve_it(input_data))
    else:
        print('This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/tsp_51_1)')

