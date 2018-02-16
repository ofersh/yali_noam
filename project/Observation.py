import numpy as np

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

