'''
Created on Sep 23, 2017

@author: yali
'''
from __future__ import print_function, division
from sklearn import datasets
import clustering
import statistical_gap


def find_index_of_array_in_array_of_arrays(data, target):
    i = 0

    for d in data:
        if (d == target).all():
            return i
        i += 1

    return -1


def accuracy (clusters, iris_data_set):
    elements = 0
    hits = 0

    iris_data_list = iris_data_set.data.tolist()

    for cluster in clusters:

        elements += len(cluster.get_points())
        center_index = find_index_of_array_in_array_of_arrays(iris_data_set.data, cluster.get_center())
        #center_index = iris_data_list.index(cluster.get_center().tolist())

        print("a center is: {}".format(iris_data_set.target[center_index]))

        for elem in cluster.get_points():
            i = find_index_of_array_in_array_of_arrays(iris_data_set.data, elem)

            if iris_data_set.target[i] == iris_data_set.target[center_index]:
                hits += 1

    print(hits / elements)


def main():
    iris_data_set = datasets.load_iris()
    statistical_gap.gap_statistic(iris_data_set.data)
    #clusters = clustering.k_means(iris_data_set.data, 3)
    #accuracy(clusters, iris_data_set)
    #map(print, clusters)


if __name__ == '__main__':
    main()
