from __future__ import division,print_function
import numpy as np

import utils
from Observation import Observation


class Kmeans(object):
    """
    Kmeans class. Holds sequence of Observation and list of centers.


    """
    def __init__(self, k, data, dist_func=utils.euclidean_dist):
        """
        Init kmean object
        :param k:
        :type k: int
        :param data:
        :type data: seq[seq]
        :param dist_func: function
        """
        self._distance = dist_func
        self._k = None
        self._centers = []
        self._observations = []
        self._finished = False
        self.k = k
        self.observations = data
        self.n = len(data)

    def set_k(self, k):
        if k < 0:
            raise ValueError("K cant be negative.")
        self._k = k

    def get_k(self):
        return self._k

    def get_observations(self):
        return self._observations

    def set_observations(self, obs_list):
        self._observations = [Observation(features, self._distance)
                              for features in obs_list]

    def get_centers(self):
        return self._centers

    def set_data(self, data):
        self.observations = data

    k = property(get_k, set_k)
    observations = property(get_observations, set_observations)
    centers = property(get_centers)

    def find_centers(self):
        if not any(self._centers):
            self.randomize_centers()
        else:
            self.find_new_centers()
        self.mark_centers()
        self.scatter()

    def randomize_centers(self):
        """
        Randomizing centers with a kmeans++ initialization.
        probabilty = D(x)^2 where D(x) is distance from closest center.
        :return:
        """
        # Choose the first center to begin with
        chosen_centers = [np.random.choice(self.observations)]
        distance_list = [0] * self.n
        
        # Find k centers
        while len(chosen_centers) < self.k:
            for i in range(self.n):
                obs = self.observations[i]
                # Find the distance from the nearest center
                dist = min([obs.distance_from(center)**2 for center in chosen_centers])
                distance_list[i] = dist
                
            # Normalizing the probabilities of the distances to [0,1]
            sum_of_distances = sum(distance_list)
            probabilities = list(map(lambda x: x/sum_of_distances, distance_list))
            
            # Choose the new center to add
            chosen_centers += [np.random.choice(self.observations, p=probabilities)]
            
        self._centers = chosen_centers

    def mark_centers(self):
        for obs in self._centers:
            obs.is_center = True

    def unmark_center(self):
        for obs in self._centers:
            obs.is_center = False

    def find_new_centers(self):
        new_centers = []
        for cn in self._centers:
            new_center = cn.nominate_center()
            new_centers.append(new_center)
        self.unmark_center()
        if self._centers == new_centers:
            self._finished = True
        self._centers = new_centers

    def scatter(self):
        for obs in self.observations:
            obs.find_center(self._centers)

    def clusterize(self):
        while not self._finished:
            self.find_centers()
        return self._centers


