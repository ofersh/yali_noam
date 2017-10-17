
from __future__ import print_function
import matplotlib.pyplot as plt
import statistical_gap_threaded


def generate_cloud():
    xs = []
    ys = []
    for i in range(1, 15):
        xs += [i] * 15
    for i in range(1, 15):
        ys += range(1, 16)
    return xs, ys

if __name__ == "__main__":
    xs, ys = generate_cloud()
    cloud = zip(xs,ys)
    print(cloud)
    statistical_gap_threaded.gap_statistic(cloud)