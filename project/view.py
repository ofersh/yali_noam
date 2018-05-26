import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

data_borders = []

COLOR_PALLET = np.array([np.array([166, 206, 227]),
                         np.array([31, 120, 180]),
                         np.array([178, 223, 138]),
                         np.array([51, 160, 44]),
                         np.array([251, 154, 153]),
                         np.array([227, 26, 28]),
                         np.array([253, 191, 111]),
                         np.array([255, 127, 0]),
                         np.array([202, 178, 214]),
                         np.array([255, 255, 153])
                         ]) * 1 / 255


def view_result(data, centers, plt_info):
    # Un comment if we want only final result
    if len(data[0]) == 3:
        #plot_3d_data(data, False)
        plot_clusters(centers, 'gs_clusters.png')
    plot_info(plt_info, 'gstats.png')


def plot_info(plt_info, file_name=None):
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
    if file_name:
        plt.show()
        # plt.savefig(file_name)


def plot_clusters(centers, file_name=None):
    global data_borders
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    for c in centers:
        all_features = [obs.features for obs in c.cluster]
        x, y, z = zip(*all_features)
        ax.scatter(x, y, z)
        x, y, z = c.features
        ax.plot([x], [y], [z], marker='x', c='k', zorder=10)
    x, y, z = data_borders
    max_axis = max([x[1], y[1], z[1]])
    min_axis = min([x[0], y[0], z[0]])
    plt.xlim(min_axis, max_axis)
    plt.ylim(min_axis, max_axis)
    plt.gca().set_aspect('equal', adjustable='box')
    if file_name:
        plt.show()
        # plt.savefig(file_name)


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


def draw_fuzzy(data, matrix, k=3):
    color_list = COLOR_PALLET[0:k]
    color_mat = np.matmul(matrix, color_list)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    x, y, z = zip(*data)
    ax.scatter(x, y, z, c=color_mat)
    plt.show()


def draw_fuzzy_with_centers(data, matrix, k, centers, file_name=None, color_indices=None):
    centers = np.squeeze(np.asarray(centers))

    # if color_indices is None:
    #     color_indices = np.random.choice(range(len(COLOR_PALLET)), size=k, replace=False)
    color_indices = [j % len(COLOR_PALLET) for j in range(0, k * 2, 2)]
    color_list = COLOR_PALLET[color_indices]
    color_mat = np.matmul(matrix, color_list)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    x, y, z = zip(*data)

    ax.scatter(x, y, z, c=color_mat, zorder=1, alpha=1)

    for i in range(len(centers)):
        x, y, z = centers[i]
        ax.scatter(x, y, z, label=i, c=COLOR_PALLET[color_indices[i]], s=100)
        ax.plot([x], [y], [z], 'x', c='k', zorder=10)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    ax.legend(loc='upper right', prop={'size': 12})

    # if file_name:
    #     plt.savefig(file_name)
    #     #close_figures()
    plt.show()


def close_figures():
    plt.close('all')
