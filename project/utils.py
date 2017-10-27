'''
Created on Oct 12, 2017

@author: yali
'''

import numpy as np
import random as rnd
from math import sin, cos
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
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


def random_3d_point():
    r = rnd.random()
    phi = rnd.random() * 360
    theta = rnd.random() * 360

    x = r * sin(phi) * cos(theta)
    y = r * sin(phi) * sin(theta)
    z = r * cos(phi)

    return np.array((x, y, z))


def random_2d_point():
    r = rnd.random()
    phi = rnd.random() * 259

    x = r * sin(phi)
    y = r * cos(phi)

    return np.array((x, y))


def choose_groupe(_, k, dim):
    x = _ % k * 5
    y = (_ % k % 2) * 5
    z = 0
    if dim == 3:
        return np.array((x, y, z))
    else:
        return np.array((x, y))


def generate_groups(n, k, rand_point):
    '''
    create k seperated groups of objects
    every group surround a random unit circle
    '''
    data = []

    # Add n random points to the data
    for _ in range(n):

        # create a random point
        sphere_point = rand_point()

        # Randomize the group the point belongs to
        center_point = choose_groupe(_, k, len(sphere_point))

        data.append(sphere_point+center_point)

    return data


def generate_cloud():
    xs = []
    ys = []
    for i in range(1, 15):
        xs += [i] * 15
    for i in range(1, 15):
        ys += range(1, 16)
    return xs, ys


def generate_random_data(n, rand_point):
    '''
    create k seperated groups of objects
    every group surround a random unit circle
    '''
    data = []

    # Add n random points to the data
    for _ in range(n):

        # create a random point
        sphere_point = rand_point()
        
        # Add point to data
        data.append(sphere_point)

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


def draw_3d(data, title):
    x, y, z = zip(*data)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    ax.scatter(x, y, z, c='r', marker='o')
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')

    plt.show()


def draw_2d(data, title):
    x, y = zip(*data)
    plt.plot(x, y, 'o')
    plt.title(title)
    plt.show()
    
    
def draw_2d_line(data, title):
    x, y = zip(*data)
    plt.plot(x, y)
    plt.title(title)
    plt.show()
