/*
 * Matrix.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: yali
 */

#include "Matrix.h"

Matrix::Matrix(unsigned int N) {
	n = N;
	for( int i=0; i<(int)n; i++){
		bool* tmp = new bool[n];
		for(int j=0; j<(int)n; j++)
			tmp[j] = false;
		mat.push_back(tmp);
	}
}

Matrix::Matrix(unsigned int N, int* input) {
	n = N;
	for( int i=0; i<(int)n; i++){
		bool* tmp = new bool[n];
		for(int j=0; j<(int)n; j++)
			if(input[n*i + j])
				tmp[j] = true;
			else
				tmp[j] = false;
		mat.push_back(tmp);
	}

}

bool Matrix::get_index(int i, int j) {
	return mat[i][j];
}


void Matrix::clean_mat() {
	for(unsigned int i=0; i<this->n; i++)
		this->clean_row(i);
}


void Matrix::clean_row(int i) {
	for(unsigned int j=0; j<n; j++)
		mat[i][j] = false;
}

void Matrix::clean_col(int j) {
	for(unsigned int i=0; i<n; i++)
		mat[i][j] = false;
}



bool Matrix::is_empty() {
	for(unsigned int i=0; i<n; i++)
		for(unsigned int j=0; j<n; j++)
			if(mat[i][j])
				return false;
	return true;
}

void Matrix::set_false(int i, int j) {
	mat[i][j] = false;
}

void Matrix::set_true(int i, int j) {
	mat[i][j] = true;
}

void Matrix::print() {
	for(unsigned int i=0; i<n; i++){
		for(unsigned int j=0; j<n; j++){
			char p;
			if(mat[i][j])
				p = '1';
			else
				p = '0';
			cout << p << " ";
		}
		cout  << endl;
	}
	cout  << endl;
}

Matrix Matrix::find_match_matrix(unsigned int* pIn, unsigned int* pOut,
		int max_eval) {
	/*
	 * N - size of the router
	 * Sin - graph with edges between input and output
	 * pIn - indicates the favorable next ouptut queue
	 * pOut - indicates the favorable next input queue
	 * Sout - match matrix
	 * reutrn value: curr_iter - amount of iterations the iSlip as made
	 */
	Matrix result(this->n);
	int curr_eval = 0;
	Matrix grant(this->n);

	while(!this->is_empty() && curr_eval < max_eval){
		curr_eval++;

		// Grant stage
		// for each output
		for(unsigned int j=0; j<this->n; j++){
			// for each enternce
			for(unsigned int i=0; i<this->n; i++){
				// starting from the pointer's index
				unsigned int i_ind = (i+pOut[j]) % this->n;

				if(this->get_index(i_ind,j)){
					grant.set_true(i_ind,j);
					break;
				}
			}
		}

		grant.print();

		// Accept stage
		// for each enternce
		for(unsigned int i=0; i<this->n; i++){
			// for each output
			for(unsigned int j=0; j<this->n; j++){
				// starting from the pointer's index
				unsigned int j_ind = (j+pIn[i]) % this->n;

				if(grant.get_index(i, j_ind)){
					// Update the output matrix
					result.set_true(i, j_ind);

					// Update request matrix for next round
					this->clean_col(j_ind);
					this->clean_row(i);

					// on the first evaluation, change the pointer for pIn and pOut
					if(curr_eval == 1){
						pIn[i] = (j_ind + 1) % this->n;
						pOut[j_ind] = (i + 1) % this->n;
					}
					break;
				}
			}
		}
		grant.clean_mat();

	}

	return result;
}

Matrix::~Matrix() {
}
