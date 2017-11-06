from __future__ import division, print_function

import random as rnd
from math import sin, cos
import numpy as np
from collections import namedtuple

Frame_properties = namedtuple('Frame_properties', ['pivot', 'length', 'height', 'width'])
default_prop = Frame_properties((0, 0, 0), 10, 10, 2)


# Points creation

def random_point_in_borders(borders):
    num_features = len(borders)
    element = [0] * num_features

    for i in range(num_features):
        feature = rnd.random() * borders[i]
        element[i] = feature

    return element


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


def random_2d_point():
    r = rnd.random()
    phi = rnd.random() * 259

    x = r * sin(phi)
    y = r * cos(phi)

    return np.array((x, y))


# Generating the whole data

def uniform_square(frame_size, elements_number=200):
    """
    Generate uniform data points in a frame.
    :param frame_size:
    :param elements_number:
    :return:
    """
    square = []

    for n in range(elements_number):
        point = random_point_in_borders(frame_size)
        square += [point]

    return square


def generate_square_with_equal_dist_3d(elements_number=600):
    """
    Creating a data with equal distances between two neighbor points.
    used mainly to see if the returned k would be 1 (if I'm not mistaking)
    """
    data = []

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


    max_x = elements_number/ 2
    max_y = elements_number / 2

    x = 0.05
    y = 0.05

    return [np.array((x * i, y * j, 0)) for i in range(int(max_x)) for j in range(int(max_y))]


def generate_square_edges(square_prop=default_prop):
    """
    Create edges of square with given properties.
    :param square_prop:
    :return:
    """
    margin = default_prop.width / 2
    margin_arr = np.array([margin, margin, margin])
    pivot = np.array(square_prop.pivot) + margin_arr
    length = square_prop.length - (2 * margin)
    height = square_prop.height - (2 * margin)

    a = pivot
    b = a + np.array([0, 0, height])
    c = a + np.array([0, length / 2, height / 2])

    d = a + np.array([0, length, 0])
    e = d + np.array([0, 0, height])

    return [a, b, c, d, e]


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
            point = random_3d_point(square_prop.width / 2)
            clusters += [edge + point]
    return square + clusters


def choose_group(index, k, dim):
    z = index % k * k/2
    y = (index % k % 2) * k
    x = 0
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

        data.append(sphere_point + center_point)

    return data
