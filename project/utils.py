'''
Created on Oct 12, 2017

@author: yali
'''

import numpy as np
import random as rnd
from math import sin, cos
import matplotlib.pyplot as plt
import time


def time_test(func):
    begin = time.time()
    func()
    end = time.time()
    print("{function} took {time:.6f} seconds".format(function=func.__name__, time=(end - begin)))


def latency(func):

    def time_measurement(*args, **kwargs):
        begin = time.time()
        returned_value = func(*args, **kwargs)
        end = time.time()
        print("{function} took {time}".format(function=func.__name__, time=(end-begin)))
        return returned_value

    return time_measurement


def random_point(r):
    t = rnd.randint(0,259)
    x = r * sin(t)
    y = r * cos(t)
    return x, y


def generate_groups(n, k):
    '''
    create k seperated groups of objects
    every group surround a random unit circle
    '''
    data = []

    # Add n random points to the data
    for _ in range(n):

        # Randomize the group the point belongs to
        group = rnd.randint(0, k-1) * 7

        # create a random point
        r = rnd.random() + 1
        point = np.array(random_point(r))

        data.append(point+group)

    return data


def euclidean_dist(seq1, seq2):
    """
    Simple euclidian distance function.

    :param seq1: Observation or list
    :param seq2: Observation or list
    :return: float
    """
    arr1 = np.array(seq1)
    arr2 = np.array(seq2)
    d = np.linalg.norm(arr1 - arr2)
    return d


def plot_info(plt_info):
    weights = plt_info[0]
    expected = plt_info[1]
    gaps = plt_info[2]
    rng = range(1, len(weights))

    print(gaps)

    plt.plot(rng, list(weights)[1:], 'r', label="Weight")
    plt.plot(rng, list(expected)[1:], 'g', label="Expected")
    plt.plot(rng, list(gaps)[1:], 'b', label="Gaps")
    plt.legend(loc='upper right')
    plt.show()

    gaps_diff = np.array(gaps[2:]) - np.array(gaps[1:-1])
    plt.plot(range(1,len(weights)-1), gaps_diff)
    plt.show()



def draw_2d(data, title):
    x, y = zip(*data)
    plt.plot(x, y, 'o')
    plt.title(title)
    plt.show()