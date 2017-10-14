from __future__ import division
import clustering
import matplotlib.pyplot as plt
from math import log10
import multiprocessing as mp


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
        cluster_points = cluster.get_points()
        nr = len(cluster_points)
        dr = 0
        for i in range(nr):
            for j in range(i+1, nr):
                dr += clustering.calc_distance(cluster_points[i], cluster_points[j])
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
    :param weights: dictionary
    :return: int
    """
    min_gap = min(gaps)
    min_gap_ind = gaps.index(min_gap)
    return  min_gap_ind


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


def present(clusters, p):
    if p == 2:
        i = 0
        for cluster in clusters:
            i += 1
            points = zip(*cluster.get_points())
            xs = points[0]
            ys = points[1]
            plt.plot(xs, ys, 'o')

        plt.show()


def k_gap_calc(k, data, weights, gaps, expected, n, p):
    """
    Calculate weight, expected weight and gap for given k.

    :param k: int
    :param data: array of arrays
    :param weights: list
    :param gaps:    list
    :param expected: list
    :param n:   int
    :param p:   int
    :return:    None
    """
    clusters = clustering.k_means(data, k)
    weight = general_distance(clusters)
    weights[k-1] = (log10(weight))
    gap, expect = calc_gap(weight, k, p, n, 1)
    gaps[k-1] = gap
    expected[k-1] = expect


def gap_statistic(data):
    """
    find the recommended number of clusters in given data set

    :param data: sequence of arrays
    :return: int
    """
    mg = mp.Manager()
    k_max = 20
    n = len(data)
    p = len(data[0])
    weights = mg.list([0] * (k_max-1))
    gaps = mg.list([0] * (k_max-1))
    expected = mg.list([0] * (k_max-1))
    rng = range(1, k_max)

    num_of_workers = mp.cpu_count()
    print("number of workers is : {}".format(num_of_workers))
    pool = mp.Pool(num_of_workers)

    for k in rng:
        pool.apply_async(k_gap_calc, args=(k, data, weights, gaps, expected, n, p))

    pool.close()
    pool.join()

    plt.figure(1)
    plt.plot(rng, list(weights), 'r', label="Weight")
    plt.plot(rng, list(expected), 'g', label="Expected")
    plt.plot(rng, list(gaps), 'b', label="Gaps")
    plt.legend(loc='upper right')
    plt.show()

    print("the right k is: {}".format(find_k(list(gaps))))

    #vitrack = find_k(weights)


