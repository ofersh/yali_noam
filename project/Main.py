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
    data = utils.uniform_square()
    k, plot_info, centers = gsy(data)
    print("the returned k is : {}".format(k))
    utils.plot_clusters(centers)
    utils.plot_info(plot_info)


if __name__ == '__main__':
    main()