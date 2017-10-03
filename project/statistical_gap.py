from __future__ import division
import clustering
import matplotlib.pyplot as plt

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
        dr = sum(cluster.calc_distance(element) for element in cluster.get_points())
        nr = len(cluster.get_points())
        if nr == 0:
            pass
        weight += (1/(2*nr))*dr

    return weight



def find_k(weights):
    """
    find the recommended k
    TODO: find the way to get the right k
    :param weights: dictionary
    :return: int
    """
    pass


def gap_statistic(data):
    """
    find the recommended number of clusters in given data set

    :param data: sequence of arrays
    :return: int
    """

    n = len(data)
    weights = []

    for k in range(30, n):

        print("\nnow creating {} clusters".format(k))

        clusters = clustering.k_means(data, k)

        weights.append(general_distance(clusters))

    print(weights)
    plt.plot(range(30, n), weights)
    plt.show()
    vitrack = find_k(weights)

    pass