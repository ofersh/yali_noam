'''
Created on Oct 27, 2017

@author: Bali
'''
from __future__ import print_function
import datasets_test as dst
import logging
logging.basicConfig(level=logging.INFO)


def main():
    # dst.verified_data_set()
    #dst.c_clusters(k=3, expected_clusters=3)
    dst.k_clusters(4)

if __name__ == '__main__':
    main()
