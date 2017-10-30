from __future__ import division,print_function
import numpy as np

import utils


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
        #utils.plot_clusters(self.centers)
        self.scatter()

    def randomize_centers(self):
        """
        Randomizing centers with a condition, to be at least `var/3` far from each other.
        :return:
        """
        found = False
        chosen_centers = []
        while not found:
            chosen_centers = list(np.random.choice(self.observations,
                                                   self.k,
                                                   replace=False))
            distances = [center_from.distance_from(center_to)
                         for center_from in chosen_centers
                         for center_to in chosen_centers if center_from != center_to]
            all_features = [obs.features for obs in self.observations]
            var = np.var(all_features)
            if self.k != 1 and all(d > var/(self.k + 1) for d in distances):
                found = True

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


class Observation(object):
    """
    Observation class. Holds a list of features.
    """
    def __init__(self, features, dist_func):
        self._features = np.array([])
        self._cluster = []
        self.features = features
        self.calc_distance = dist_func
        self._is_center = False

    def get_features(self):
        return self._features

    def set_features(self, features_list):
        self._features = np.array(features_list)

    def get_cluster(self):
        return self._cluster

    def clear_cluster(self):
        self._cluster = []

    def add_to_cluster(self, obs):
        self._cluster.append(obs)

    def set_is_center(self, boolean):
        self._is_center = boolean
        self._cluster = []

    def get_is_center(self):
        return self._is_center

    def distance_from(self, obs):
        if isinstance(obs, Observation):
            return self.calc_distance(self.features, obs.features)
        else:
            return self.calc_distance(self.features, obs)

    def find_center(self, centers):
        if self.is_center:
            self.add_to_cluster(self)
            return
        dist_from_centers = [self.distance_from(cn)
                             for cn in centers]
        center_index = dist_from_centers.index(min(dist_from_centers))
        centers[center_index].add_to_cluster(self)

    def nominate_center(self):
        if not self._cluster:
            return self
        else:
            features_sum = sum(o.features for o in self._cluster)
            observations_num = len(self._cluster)
            target_features = features_sum / observations_num
            distances_from_target = [obs.distance_from(target_features) for obs in self._cluster]
            min_dist = min(distances_from_target)
            index_of_min = distances_from_target.index(min_dist)
            return self._cluster[index_of_min]

    def __eq__(self, other):
        return np.array_equal(self._features, other.features)

    def __str__(self):
        if self.is_center:
            return "Center is {center} - Observations: {obs}".format(center=self.features,
                                                                     obs=[o.features for o in self.cluster])
        return str(self.features)

    features = property(get_features, set_features)
    cluster = property(get_cluster)
    is_center = property(get_is_center, set_is_center)


