from Observation import Observation
import numpy as np


class FuzzyCMeans(object):

    def find_c_means(self, data, c, m=2, epsilon=0.2):
        n = len(data)
        new_membership_matrix = np.matrix([[0.0] * c] * n) # Creating a matrix with size n X c
        old_membership_matrix = np.matrix([[0.0] * c] * n)

        centers = choose_random_centers(data) # Need to choose the centers randomly, like we did in k_means

        fill_matrix(new_membership_matrix, centers, data)  # Need to update the matrix according to centers
        
        while True:

            old_membership_matrix = new_membership_matrix

            find_new_centers(old_membership_matrix, centers)

            new_membership_matrix = update_matrix(old_membership_matrix, old_membership_matrix)

            if improvment(new_membership_matrix, old_membership_matrix) < epsilon :
                break

            pass

        scatter_to_clusters(centers, new_membership_matrix, data)

        return centers
