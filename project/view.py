import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

data_borders = []


def view_result(data, centers, plt_info):
    if len(data[0]) == 3:
        plot_3d_data(data, False)
        plot_clusters(centers, False)
    plot_info(plt_info)


def plot_info(plt_info, show=True):
    weights = plt_info[0]
    expected = plt_info[1]
    gaps = plt_info[2]
    rng = range(1, len(weights))

    plt.figure()
    plt.subplot(211)
    plt.plot(rng, list(weights)[1:], 'r', label="Weight")
    plt.plot(rng, list(expected)[1:], 'g', label="Expected")
    plt.plot(rng, list(gaps)[1:], 'b', label="Gaps")
    plt.legend(loc='upper right')

    plt.subplot(212)
    plt.stem(rng, gaps[1:])
    if show:
        plt.show()


def plot_clusters(centers, show=True):

    global data_borders
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    for c in centers:
        all_features = [obs.features for obs in c.cluster]
        x, y, z = zip(*all_features)
        ax.scatter(x, y, z)
        ax.scatter(*c.features, marker='*', c='k')
    x, y, z = data_borders
    max_axis = max([x[1], y[1], z[1]])
    min_axis = min([x[0], y[0], z[0]])
    plt.xlim(min_axis, max_axis)
    plt.ylim(min_axis, max_axis)
    plt.gca().set_aspect('equal', adjustable='box')
    if show:
        plt.show()


def plot_3d_data(data, show=True):

    x, y, z = zip(*data)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    ax.scatter(x, y, z, c='r', marker='o')
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    plt.xlim(-1, 15)
    plt.ylim(-1, 15)
    plt.gca().set_aspect('equal', adjustable='box')
    if show:
        plt.show()


def draw_2d(data, title):
    x, y = zip(*data)
    plt.plot(x, y, 'o')
    plt.title(title)
    plt.show()


def draw_2d_line(data, title):
    x, y = zip(*data)
    plt.plot(x, y)
    plt.title(title)
    plt.show()


def calc_color(coef, colors):
    weighted_color = [np.abs(c) * col for c in coef for col in colors]
    new_color = np.sum(weighted_color, axis=0)
    return new_color/len(coef)




def draw_fuzzy(data, matrix, k=3):
    ls = np.random.RandomState(None)
    color_list = ls.rand(k, 3)
    # color_mat = np.matmul(matrix, color_list)
    color_mat = [calc_color(coef, color_list) for coef in data]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    x, y, z = zip(*data)

    ax.scatter(x, y, z, c=color_mat)
    plt.show()





