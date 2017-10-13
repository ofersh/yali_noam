from __future__ import division
import clustering
import matplotlib.pyplot as plt
from math import sqrt, log10


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


def find_k(weights):
    """
    find the recommended k
    TODO: find the way to get the right k
    :param weights: dictionary
    :return: int
    """
    pass


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


def gap_statistic(data):
    """
    find the recommended number of clusters in given data set

    :param data: sequence of arrays
    :return: int
    """

    n = len(data)
    p = len(data[0])
    weights = []
    gaps = []
    expected = []
    rng = range(1, 20)
    for k in rng:

        print("\nnow creating {} clusters".format(k))

        clusters = clustering.k_means(data, k)

        #present(clusters, p)

        weight = general_distance(clusters)
        weights.append(log10(weight))
        gap, expect = calc_gap(weight, k, p, n, 1)
        gaps.append(gap)
        expected.append(expect)

    print(weights)
    plt.figure(1)
    x = plt.plot(rng, weights, 'r', label="Weight")
    plt.plot(rng, expected, 'g', label="Expected")
    plt.plot(rng, gaps, 'b', label="Gaps")
    plt.legend(loc='upper right')
    plt.show()
    vitrack = find_k(weights)



    pass