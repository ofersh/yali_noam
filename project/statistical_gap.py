from __future__ import division

from math import log10
import multiprocessing as mp
import logging

import k_means
import utils
import data_generator as dg

sg_logger = logging.getLogger("stats_gap")


def general_distance(clusters):
    """
    summarize the distance of each point from it's center

    dr = Sum of distances from center in cluster r.
    nr = Number of elements in cluster r.
    see page 2 gap.pdf
    :param clusters: sequence of Centroids
    :return: float
    """
    i = 1
    weight = 0
    for center in clusters:
        observations = center.cluster
        nr = len(observations)
        dr = 0
        for i in range(nr):
            for j in range(i+1, nr):
                dr += observations[i].distance_from(observations[j])
        if nr == 0:
            print(center)
            nr = 1
        cluster_weight = dr / (nr * 2)
        weight += cluster_weight
        
    return weight


def inner_weights(k, data, weights):
    """
    Calculate weight, expected weight and gap for given k.

    :param k: number of clusters.
    :param data: data to clusterize
    :param weights: target list.
    :return:    None
    """
    kmean = k_means.Kmeans(k, data)
    centers = kmean.clusterize()
    weight = general_distance(centers)
    weights[k] += weight


def monte_carlo_iteration(n, frame, k_max, expected, i):
    sg_logger.info("starting the {} iterate in monte carlo".format(i))
    data = dg.uniform_square(frame, n)
    for k in range(1, k_max):
        inner_weights(k, data, expected)

    sg_logger.info('finished the {} iterate in monte carlo'.format(i))


def calc_expected(n, frame, k_max, iterations=40):
    """
    change to be fully independent, might use it in rpyc
    :param k_max:
    :param iterations:
    :return:
    """
    mg = mp.Manager()
    expected = mg.list([0.0] * k_max)
    num_of_workers = mp.cpu_count()
    pool = mp.Pool(num_of_workers)

    for i in range(iterations):
        pool.apply_async(monte_carlo_iteration, args=(n, frame, k_max, expected, i))
        
    pool.close()
    pool.join()
    
    for i in range(1, k_max):
        if expected[i] == 0.0:
            expected[i] = 1.0
        expected[i] = (expected[i]/iterations)

    return expected


def gap_statistic(data):
    """
    find the recommended number of clusters in given data set

    :param data: sequence of arrays
    :return: int
    """
    sg_logger.info("finding the best k")
    mg = mp.Manager()
    n = len(data)
    k_max = min([17, n])
    weights = mg.list([0.0] * k_max)
    gaps = mg.list([0.0] * k_max)
    rng = range(1, k_max)
    frame = utils.find_data_frame(data)
    
    expected = calc_expected(n, frame, k_max, 15)

    num_of_workers = mp.cpu_count()
    sg_logger.debug("using {} cores".format(num_of_workers))
    pool = mp.Pool(num_of_workers)
    
    for k in rng:
        pool.apply_async(inner_weights, args=(k, data, weights))

    pool.close()
    pool.join()

    weights[0] = 1
    expected[0] = 1
    weights = list(map(log10, weights))
    expected = list(map(log10, expected))
    for i in rng:
        gaps[i] = expected[i] - weights[i]

    k = gaps.index(max(gaps))
    km = k_means.Kmeans(k, data)
    centers = km.clusterize()
    plot_info = (weights, expected, gaps)
    return k, plot_info, centers
