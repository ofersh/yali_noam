'''
Created on Oct 27, 2017

@author: yali
'''
#import datasets_test as dst
import utils
from statistical_gap_threaded import gap_statistic as gs
from statistical_gap_threaded import gap_statistic_yali as gsy



def main():
    data = utils.generate_groups(500, 4, utils.random_3d_point)
    #k, plot_info, clusters = gs(data)
    k, plot_info, clusters = gsy(data)
    
    print("the returned k is : {}".format(k))
    utils.draw_3d(data)
    utils.plot_info(plot_info)
    

if __name__ == '__main__':
    main()