'''
Created on Oct 12, 2017

@author: yali
'''

print("start importing")
import numpy as np
import random as rnd
from math import sin, cos
import matplotlib.pyplot as plt
import statistical_gap_threaded
import statistical_gap
import time
print("finished importing")


def random_point(r):
    t = rnd.randint(0,259)
    x = r * sin(t)
    y = r * cos(t)
    return (x,y)


def generate_groups(n, k):
    '''
    create k seperated groups of objects
    every group surround a random unit circle
    '''
    data = []

    # Add n random points to the data
    for _ in range(n):

        # Randomize the group the point belongs to
        group =  rnd.randint(0,k-1) * 3

        # create a random point
        point = np.array(random_point(rnd.random()))

        data.append(point+group)

    return data


def draw2D(data, title):
    x, y = zip(*data)
    plt.plot(x, y, 'o')
    plt.title(title)
    plt.show()


def main():
    n = 100
    k = 10
    print("creating {} groups with data size {}".format(k, n))
    data = generate_groups(n, k)
    print(data)
    #draw2D(data, "data")

    start_time = time.time()
    statistical_gap_threaded.gap_statistic(data)
    elapsed_time_1 = time.time() - start_time

    start_time = time.time()
    statistical_gap.gap_statistic(data)
    elapsed_time_2 = time.time() - start_time

    print("time with multiprocess - {}\ntime without - {}".format(elapsed_time_1,elapsed_time_2))


main()
