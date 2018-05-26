'''
Created on Oct 27, 2017

@author: Bali
'''
from __future__ import print_function
import datasets_test as dst
import logging
import view
logging.basicConfig(level=logging.INFO)


def main():
    # dst.verified_data_set()
    dst.test_wine()
    #dst.c_clusters(k=10, expected_clusters=3)
    #dst.k_clusters(4)
    #view.close_figures()

if __name__ == '__main__':
    main()
