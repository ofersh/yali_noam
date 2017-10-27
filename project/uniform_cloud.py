
from __future__ import print_function
import matplotlib.pyplot as plt
import statistical_gap_threaded
import utils


if __name__ == "__main__":
    xs, ys = utils.generate_cloud()
    cloud = zip(xs,ys)
    utils.draw_2d(cloud, "uniform")
    print(cloud)
    #k, plot_info = statistical_gap_threaded.gap_statistic(cloud)
    #print("k is {}".format(k))
    #utils.plot_info(plot_info)