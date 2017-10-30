'''
Created on Oct 12, 2017

@author: yali
'''

from __future__ import division
import numpy as np
import random as rnd
from math import sin, cos
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import time
from collections import namedtuple


Square_prop = namedtuple('square_properties', ['pivot', 'length', 'height', 'width'])
default_prop = Square_prop((0, 0, 0), 10, 10, 2)


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


def uniform_square(elements_number=700):
    """
    Generate uniform square of points.
    :param elements_number: int
    :return:
    """
    square = []

    for n in range(elements_number):
        point = random_point_in_borders([10, 6, 2])
        square += [point]

    return square


def random_point_in_borders(borders):
    num_features = len(borders)
    element = [0] * num_features

    for i in range(num_features):
        feature = rnd.random() * borders[i]
        element[i] = feature

    return element


def generate_data_with_edges(elements_number, borders):
    data = []

    for _ in range(elements_number):
        element = random_point_in_borders(borders)
        data.append(np.array(element))

    return data


def generate_square_with_equal_dist_3d(elements_number=40):
    data = []
    
    max_x = elements_number/2
    max_y = elements_number/2
    
    x = 0.05
    y = 0.05
    
    return [np.array((x*i, y*j, 0)) for i in range(int(max_x)) for j in range(int(max_y))]
    
    
    
    dots = int((elements_number / 3) / 2)
    x_array = np.linspace(0.0, 0.2, 3)
    y_array = np.linspace(0.0, 1.0, dots)
    z_array = np.linspace(0.0, 1.0, dots)
    
    y = 0
    z = 0
    
    for i in range(elements_number):
        
        if (y % dots) == 0:
            y = 0
            z += 1
                    
        tmp_x = x_array[i % 3]
        tmp_y = y_array[y]
        tmp_z = z_array[z]
        
        data.append(np.array([tmp_x, tmp_y, tmp_z]))
        
        y += 1
        
    return data


def generate_square_edges(square_prop=default_prop):
    """
    Create edges of square with given properties.
    :param square_prop:
    :return:
    """
    margin = default_prop.width/2
    margin_arr = np.array([margin, margin, margin])
    pivot = np.array(square_prop.pivot) + margin_arr
    length = square_prop.length - (2 * margin)
    height = square_prop.height - (2 * margin)

    a = pivot
    b = a + np.array([0, 0, height])
    c = a + np.array([0, length/2, height/2])

    d = a + np.array([0, length, 0])
    e = d + np.array([0, 0, height])

    return [a, b, c, d, e]


def random_3d_point(r=1):
    """
    Generate 3d point within radius = r
    :param r: float
    :return:
    """
    r = rnd.random() * r
    phi = rnd.random() * 2 * np.pi
    theta = rnd.random() * 2 * np.pi

    x = r * sin(phi) * cos(theta)
    y = r * sin(phi) * sin(theta)
    z = r * cos(phi)

    return np.array([x, y, z])


def generate_5_clusters(max_points=100, square_prop=default_prop):
    """
    Create 5 distinctive clusters.
    :param square_prop:
    :param max_points:
    :return:
    """
    square = generate_square_edges()
    clusters = []
    for edge in square:
        for n in range(0, max_points):
            point = random_3d_point(square_prop.width/2)
            clusters += [edge + point]
    return square + clusters


def random_2d_point():
    r = rnd.random()
    phi = rnd.random() * 259

    x = r * sin(phi)
    y = r * cos(phi)

    return np.array((x, y))


def choose_group(index, k, dim):
    x = index % k * 3
    y = (index % k % 2) * 3
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
    for i in range(n):

        # create a random point
        sphere_point = rand_point()

        # Randomize the group the point belongs to
        center_point = choose_group(i, k, len(sphere_point))

        data.append(sphere_point+center_point)

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

    plt.figure(2)
    plt.subplot(211)
    plt.plot(rng, list(weights)[1:], 'r', label="Weight")
    plt.plot(rng, list(expected)[1:], 'g', label="Expected")
    plt.plot(rng, list(gaps)[1:], 'b', label="Gaps")
    plt.legend(loc='upper right')

    plt.subplot(212)
    gaps_diff = np.array(gaps[2:]) - np.array(gaps[1:-1])
    plt.plot(range(1, len(weights)-1), gaps_diff)
    plt.show()


def plot_clusters(centers):

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    for c in centers:
        all_features = [obs.features for obs in c.cluster]
        x, y, z = zip(*all_features)
        ax.scatter(x, y, z)
        ax.scatter(*c.features, marker='*', c='k')

    plt.xlim(0, 10)
    plt.ylim(0, 10)
    plt.gca().set_aspect('equal', adjustable='box')
    plt.show()


def draw_3d(data):
    x, y, z = zip(*data)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    ax.scatter(x, y, z, c='r', marker='o')
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    plt.xlim(-1, 15)
    plt.ylim(-1, 15)
    plt.gca().set_aspect('equal', adjustable='box')
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
