from __future__ import division

import matplotlib.pyplot as plt
from math import log10
import multiprocessing as mp

import k_means
import utils


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


def k_gap_calc(kmean, weights, gaps, expected, n, p, new_param):
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


def get_expected_weights(n, k, iterations):
        
    total_weights = {}
       
    for i in range(iterations):
        print("starting the {} iterate in monte carlo".format(i))
        data = utils.generate_random_data(n, utils.random_3d_point)
            
        for j in range(1,k):
            print("finidng clusters with {}".format(j))
            if i == 0:
                # In order to initialize the dictionary
                total_weights[str(j)] = 0
                    
            km = k_means.Kmeans(k, data)
            clusters = km.clusterize()
            weight = general_distance(clusters)
                
            total_weights[str(j)] += weight
                
        del data
        
    expected_weights = {str(key) : value/iterations for key, value in total_weights.items()}
    return expected_weights
    

def gap_statistic(data):
    """
    find the recommended number of clusters in given data set

    :param data: sequence of arrays
    :return: int
    """
    mg = mp.Manager()
    k_max = min([10, len(data)])
    n = len(data)
    p = len(data[0])
    weights = mg.list([0] * k_max)
    gaps = mg.list([0] * k_max)
    expected = mg.list([0] * k_max)
    rng = range(1, k_max)
    expected_weights = get_expected_weights(n, k_max, 100)
    utils.draw_2d_line(zip(range(1,k_max),expected_weights.values()), 'expected_weights')

    num_of_workers = mp.cpu_count()
    print("number of workers is : {}".format(num_of_workers))
    pool = mp.Pool(num_of_workers)

    for k in rng:
        km = k_means.Kmeans(k, data)
        pool.apply_async(k_gap_calc, args=(km, weights, gaps, expected, n, p, expected_weights))

    pool.close()
    pool.join()

    plot_info = (weights, expected, gaps)
    return find_k(gaps), plot_info


