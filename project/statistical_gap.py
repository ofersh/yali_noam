import clustering


def general_distance(clusters):
    """
    summarize the distance of each point from it's center
    :param clusters: Centroid
    :return: float
    """
    pass


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
    weights = {}

    for k in range(1, n):

        clusters = clustering.k_means(data, k)

        weights[k] = general_distance(clusters)

    vitrack = find_k(weights)

    pass