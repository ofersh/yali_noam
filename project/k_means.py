from __future__ import division, print_function
import numpy as np

import view
import utils
from Observation import Observation


class Kmeans(object):
    """
    Kmeans class. Holds sequence of Observation and list of centers.


    """
    def __init__(self, k, data, dist_func=utils.euclidean_dist, plot=False):
        """
        Init kmean object
        :param k:
        :type k: int
        :param data:
        :type data: seq[seq]
        :param dist_func: function
        """
        self._distance = dist_func
        self._plot = plot
        self._k = None
        self._centers = []
        self._observations = []
        self._finished = False
        self._org_data = data
        self.k = k
        self.observations = data
        self.n = len(data)

        # For Plotting
        self._membership_mat = np.matrix([[0]*self.k]*self.n)
        self._file_name = './plots/kmeans/k_means{iteration}.png'
        if k < 11:
            self._colors_indices = np.random.choice(range(10), size=k, replace=False)
        else:
            self._colors_indices = np.random.choice(range(10), size=k)

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
        for i in range(self.n):
            self._membership_mat[i] = 0
            obs = self.observations[i]
            ind = obs.find_center(self._centers)
            if ind is None:
                ind = self._centers.index(obs)
            self._membership_mat[i, ind] = 1

    def clusterize(self):
        iteration = 0
        while not self._finished:
            iteration += 1
            self.find_centers()
            if self._plot:
                centers = [c.features for c in self._centers]

                tmp = self._membership_mat.sum(axis=1)
                if tmp.max() > 1:
                    print('Max tmp = %s' % tmp.max())
                # Preparing the plots
                file_name = self._file_name.format(iteration=iteration)

                view.draw_fuzzy_with_centers(self._org_data, self._membership_mat, self.k,
                                             centers=centers, file_name=file_name,
                                             color_indices=self._colors_indices)
        return self._centers
