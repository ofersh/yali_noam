from __future__ import division, print_function
from sklearn import datasets, preprocessing, decomposition

from statistical_gap import gap_statistic as gs
import xlrd
import view
import data_generator as dg
from fuzzy_c_means import FuzzyCMeans
import numpy as np


def verified_data_set():
    wb = xlrd.open_workbook("./datasets_example/s-originals/s1-groundtruth-plot.xls")
    sheet = wb.sheet_by_index(0)
    x = sheet.col_slice(colx=1, start_rowx=15)
    y = sheet.col_slice(colx=2, start_rowx=15)
    obs_x = (val.value for val in x)
    obs_y = (val.value for val in y)
    obs_x = map(int, obs_x)
    obs_y = map(int, obs_y)

    data = zip(obs_x, obs_y)
    # print(data)
    # scaled = preprocessing.scale(data)
    # print(scaled)
    k, plot_info, centers = gs(data)
    print("the returned k is : {}".format(k))
    view.view_result(data, centers, plot_info)


def test_iris():
    iris_dat = datasets.load_iris()
    data = iris_dat.data
    target = iris_dat.target
    test_data(data, target)


def test_digits():
    digits_dat = datasets.load_digits()
    data = digits_dat.data
    target = digits_dat.target
    test_data(data, target)


def test_wine():
    wine_dat = datasets.load_wine()
    data = wine_dat.data
    target = wine_dat.target
    test_data(data, target)


def test_data(data, target=None):
    data = _get_3most_dominant_features(data)
    k, plot_info, centers = gs(data)
    print("the returned k is : {}".format(k))
    view.view_result(data, centers, plot_info)
    if target is not None:
        dataset_accuracy(data, target, centers)



def five_clusters():
    exp_k = 5
    data = dg.generate_5_clusters()
    k, plot_info, centers = gs(data)

    print("the expected number of k is: {}".format(exp_k))
    print("the returned k is : {}".format(k))
    view.view_result(data, centers, plot_info)


def k_clusters(k=2):
    exp_k = k
    n = k * 150
    data = dg.generate_groups(n, k, dg.random_3d_point)
    k, plot_info, centers = gs(data)

    print("the expected number of k is: {}".format(exp_k))
    print("the returned k is : {}".format(k))
    view.view_result(data, centers, plot_info)


def c_clusters(k=3, expected_clusters=3):
    exp_k = k
    n = k * 150
    data = dg.generate_groups(n, expected_clusters, dg.random_3d_point)
    #data = dg.uniform_square([3,4,5], 1000)
    fuzzyCMeans = FuzzyCMeans(data)
    centers, matrix = fuzzyCMeans.find_c_means(k, epsilon=1e-5)
    view.draw_fuzzy_with_centers(data, matrix, k, centers)
    np.savetxt("cmeans.mat.csv", matrix, delimiter=',')


def dataset_accuracy(data, target, clusters):
    dl = map(list, data)
    dl = list(dl)
    hits = 0
    for center in clusters:
        center_ind = dl.index(list(center.features))
        center_target = target[center_ind]
        print(center_target)

        for obs in center.cluster:
            obs_ind = dl.index(list(obs.features))
            obs_target = target[obs_ind]
            if obs_target == center_target:
                hits += 1

    print("{:.2f}% success rate according to real groups.".format((hits / len(data)) * 100))


def _get_3most_dominant_features(data):
    pca = decomposition.PCA(n_components=3)
    data = preprocessing.StandardScaler().fit_transform(data)
    return pca.fit_transform(data)
