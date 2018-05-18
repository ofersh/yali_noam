import view
from Observation import Observation
import numpy as np


class FuzzyCMeans(object):

    def __init__(self, data):
        self._data = None
        self.n = len(data)
        self.data = data
        self.org_data = data

    @property
    def data(self):
        return self._data

    @data.setter
    def data(self, data):
        self._data = [Observation(features)
                      for features in data]

    def find_c_means(self, num_centers, beta=1, epsilon=1e-6):
        centers = self.choose_random_centers(num_centers)  # Need to choose the centers randomly, like we did in k_means

        membership_matrix = self.update_matrix(centers, beta)  # Need to update the matrix according to centers
        i = 0
        while True:
            if not i % 10:
                print("Iteration number: ", i)
                ## view.draw_fuzzy(self.org_data, membership_matrix, num_centers)
            old_centers = np.copy(centers)
            centers = self.find_new_centers(membership_matrix)

            membership_matrix = self.update_matrix(centers, beta)

            if not self.improved(old_centers, centers, epsilon):
                break
            i += 1

        print("finished after ", i, " iterations")
        return centers, membership_matrix

    def choose_random_centers(self, c):
        """
        Randomizing centers with a kmeans++ initialization.
        probabilty = D(x)^2 where D(x) is distance from closest center.
        :return:
        """
        # Choose the first center to begin with
        chosen_centers = [np.random.choice(self.data).features]
        distance_list = [0] * self.n

        # Find c centers
        while len(chosen_centers) < c:
            for i in range(self.n):
                obs = self.data[i]
                # Find the distance from the nearest center
                dist = min([obs.distance_from(center) ** 2 for center in chosen_centers])
                distance_list[i] = dist

            # Normalizing the probabilities of the distances to [0,1]
            sum_of_distances = sum(distance_list)
            probabilities = list(map(lambda x: x / sum_of_distances, distance_list))

            # Choose the new center to add
            chosen_centers += [np.random.choice(self.data, p=probabilities).features]

        return np.matrix(chosen_centers)

    def find_new_centers(self, coef_mat):
        new_centers = [self.calc_center(coef_mat[:, i]) for i in range(np.ma.size(coef_mat, 1))]

        return new_centers

    def update_matrix(self, centers, beta):
        '''
        Update the coefficients matrix according to the current centers and the data
        Args:
            centers: np.array

        Returns: A matrix of coefficients
            np.matrix
        '''
        new_matrix = [self.calc_obs_coefficients(obs, centers, beta) for obs in self.data]
        return np.matrix(new_matrix)

    def improved(self, old_centers, centers, epsilon):
        diffs = old_centers - centers
        if all([np.linalg.norm(d, 2) for d in diffs]) < epsilon:
            return False
        return True

    def calc_obs_coefficients(self, obs, centers, beta):
        '''
        Calculating the coefficients for an observation, according to the current centers
        Args:
            obs: Observation
            centers: list of np.arrays
            beta: float

        Returns: np.array
            List of coefficients for an observation
        '''
        coefficients = np.array([np.exp(-beta * obs.distance_from(c) ** 2) for c in centers])
        return coefficients/sum(coefficients)

    def calc_center(self, coefficients):
        '''
        The new center is the weighted mean of the old center
        According to the coefficients matrix
        Args: array of the coefficients for the current center
            coefficients: np.array

        Returns: the new center
            np.array
        '''
        # Debug purposes
        if len(coefficients) != self.n:
            self.print_error_and_exit('len(coefficients) != self.n')

        nominator = sum([coefficients[i] * self.data[i].features for i in range(self.n)])

        denominator = sum(coefficients)

        new_center = nominator / denominator

        return new_center

    def print_error_and_exit(self, message):
        print('*' * 50)
        print(' ' * 10 + message)
        print('*' * 50)
        exit()



