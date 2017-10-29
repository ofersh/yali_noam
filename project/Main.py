'''
Created on Oct 27, 2017

@author: yali
'''
#import datasets_test as dst
import utils
from statistical_gap_threaded import gap_statistic as gs


def main():
    data = utils.generate_square_with_equal_dist_3d()
    k, plot_info, clusters = gs(data)
    
    print("the returned k is : {}".format(k))
    utils.draw_3d(data)
    utils.plot_info(plot_info)
    

if __name__ == '__main__':
    main()