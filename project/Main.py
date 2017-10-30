'''
Created on Oct 27, 2017

@author: yali
'''
#import datasets_test as dst
from __future__ import print_function
import k_means
import utils
from statistical_gap_threaded import gap_statistic as gs
from statistical_gap_threaded import gap_statistic_yali as gsy



def main():
    #data = utils.generate_groups(500, 4, utils.random_3d_point)
    #k, plot_info, clusters = gs(data)
    #k, plot_info, clusters = gsy(data)
    k = 5
    data = utils.generate_5_clusters()
    #k, plot_info, cluster = gsy(data)
    km = k_means.Kmeans(k, data)
    centers = km.clusterize()
    print("the returned k is : {}".format(k))
    map(print, centers)
    utils.plot_clusters(centers)
    #utils.plot_info(plot_info)
    

if __name__ == '__main__':
    main()