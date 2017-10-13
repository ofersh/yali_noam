'''
@author: yali
'''
from __future__ import division,print_function
import numpy as np
import random as rnd


def calc_distance(a, b):
    """
    Returns the Euculadean distance from a to b
    @param a: array
    @param b: array
    @return: float
    """
    result = np.linalg.norm(a - b, 2)
    return result


class Centroid(object):
    def __init__(self, center):
        self._current_center = center
        self._new_center = None
        self._points = []

    def add_point(self, point):
        """
        Add a point to the cluster with old_center as the center of the group
        @param point: array
        """
        self._points.append(point)

    def reset_points(self):
        self._points = []

    def set_center(self, center):
        self._current_center = center

    def get_center(self):
        """

        :return: nd.array
        """
        return self._new_center

    def __eq__(self, other):
        """

        :param other: Centroid
        :return: bool
        """
        return all(self._current_center == other._current_center)

    def get_points(self):
        return self._points

    def find_center(self):
        """
        Find the new center of the group.
        """
        if len(self._points) == 0:
            return

        # find an imaginary point which is the center of the group
        real_center = sum(self._points) / len(self._points)

        # Find the closest point
        distances = [
            calc_distance(point, real_center) for point in self._points
        ]
        closest_index = distances.index(min(distances))

        self._new_center = self._points[closest_index]

    def is_same_center(self):
        """
        Check if the new point is the same as the old one
        """
        # For first iteration
        if self._new_center is None:
            return False

        # Check if new point equals to the first point
        if (self._new_center == self._current_center).all():
            return True
        self._current_center = self._new_center
        return False

    def calc_distance(self, point):
        """
        Calculate the distance of a point from the center of the group
        @param point: array
        @return: float
        """
        return calc_distance(point, self._current_center)

    def __str__(self):
        return "the center: {} | {}".format(self._current_center, self._points)


def get_random_centers(data, k):
    """
    return k random points from the received data
    @param data: list points
    @param k: number of random points from the list
    @return: list of random points
    """
    random_group = []
    real_points = rnd.sample(data, k)

    for point in real_points:
        random_group.append(Centroid(point))
    return np.unique(random_group)


def same_centers(centers):
    """
    Verify if the centers have changed.
    For every centroid, check if the center has changed
    @param centers: list of Centroids
    @return: True if centers have changed else if not
    """
    for center in centers:
        if not center.is_same_center():
            return False
    return True


def assign_to_centers(point, centers):
    """
    Finds the closest center point to the given point
    Calculating distances and adding the given point to the list of point of the center
    @param point: array
    @param centers: list of Centroids
    @return: None
    """
    for center in centers:
        if point is center.get_center():
            center.add_point(point)
            return

    distances = [center.calc_distance(point) for center in centers]
    closest_index = distances.index(min(distances))

    centers[closest_index].add_point(point)


def find_new_centers(centers):
    """
    Find the new center for each group
    @param centers: list of Centroids
    """
    map(lambda c: c.find_center(), centers)


def k_means(data, k):
    """
    perform the k_means algorithm.
    seperate the data into k clusters
    @param data: array of arrays
    @param k: int
    @return: list of Centroids
    """
    i = 0
    centers = get_random_centers(data, k)

    while not same_centers(centers):

        i+=1
        if i > 300:
            break
        # Clear the groups of the centers
        for center in centers:
            center.reset_points()

        # For every group in the data, fin the right center
        for point in data:
            assign_to_centers(point, centers)

        find_new_centers(centers)

    return centers


