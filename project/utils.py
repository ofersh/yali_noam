'''
Created on Oct 12, 2017

@author: yali
'''

from __future__ import division
import numpy as np
import time
import logging
import view

utils_logger = logging.getLogger("utils_log")


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


def find_data_frame(data):
    """
    finds the max/min value of each feature.
    returning a box shaped frame
    :param data:
    :return:
    """

    num_features = len(data[0])
    max_values = np.array([0.0] * num_features)
    min_values = np.array([0.0] * num_features)

    features_list = list(zip(*data))

    for i in range(num_features):
        max_values[i] = max(features_list[i])
        min_values[i] = min(features_list[i])

    frame_size = max_values - min_values
    view.data_borders = tuple(zip(min_values, max_values))

    utils_logger.info("the data borders are {}".format(view.data_borders))

    return frame_size


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
