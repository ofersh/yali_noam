from __future__ import division

import matplotlib.pyplot as plt
from math import log10
import multiprocessing as mp

import k_means


def general_distance(clusters):
    """
    summarize the distance of each point from it's center

    dr = Sum of distances from center in cluster r.
    nr = Number of elements in cluster r.
    see page 2 gap.pdf
    :param clusters: sequence of Centroids
    :return: float
    """
    weight = 0
    for cluster in clusters:
        observations = cluster.cluster
        nr = len(observations)
        dr = 0
        for i in range(nr):
            for j in range(i+1, nr):
                dr += observations[i].distance_from(observations[j])
        if nr == 0:
            print(cluster)
            nr = 1
        cluster_weight = dr / (nr * 2)
        weight += cluster_weight

    return weight


def find_k(gaps):
    """
    find the recommended k
    TODO: find the way to get the right k
    :param gaps: list
    :return: int
    """
    max_gap = max(gaps[1:])
    max_gap_ind = gaps.index(max_gap)
    return max_gap_ind


def calc_gap(weight, k, p, n, const=0):
    """

    :param weight: float
    :param k: int
    :param p: int
    :param n: int
    :param const: float
    :return: float
    """
    expected_weight = log10((p*n)/12) - (2/p)*log10(k) + const
    return expected_weight - log10(weight), expected_weight


def k_gap_calc(kmean, weights, gaps, expected, n, p):
    """
    Calculate weight, expected weight and gap for given k.

    :param kmean: k_means.Kmean
    :param weights: list
    :param gaps:    list
    :param expected: list
    :param n:   int
    :param p:   int
    :return:    None
    """
    clusters = kmean.clusterize()
    weight = general_distance(clusters)
    gap, expect = calc_gap(weight, kmean.k, p, n, 1)

    weights[kmean.k] = (log10(weight))
    gaps[kmean.k] = gap
    expected[kmean.k] = expect


def gap_statistic(data):
    """
    find the recommended number of clusters in given data set

    :param data: sequence of arrays
    :return: int
    """
    mg = mp.Manager()
    k_max = min([25, len(data)])
    n = len(data)
    p = len(data[0])
    weights = mg.list([0] * k_max)
    gaps = mg.list([0] * k_max)
    expected = mg.list([0] * k_max)
    rng = range(1, k_max)

    num_of_workers = mp.cpu_count()
    print("number of workers is : {}".format(num_of_workers))
    pool = mp.Pool(num_of_workers)

    for k in rng:
        km = k_means.Kmeans(k, data)
        pool.apply_async(k_gap_calc, args=(km, weights, gaps, expected, n, p))

    pool.close()
    pool.join()

    plot_info = (weights, expected, gaps)
    return find_k(gaps), plot_info


