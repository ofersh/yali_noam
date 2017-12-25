/*
 * Matrix.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: yali
 */

#include "Matrix.h"

Matrix::Matrix(int N) {
	n = N;
	for( int i=0; i<n; i++)
		mat.push_back(new bool[n]);
}

Matrix::Matrix(int N, int* input) {
	n = N;
	for( int i=0; i<n; i++){
		bool* tmp = new bool[n];
		for(int j=0; j<n; j++)
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

void Matrix::clean_row(int i) {
	for(int j=0; j<n; j++)
		mat[i][j] = false;
}

void Matrix::clean_col(int j) {
	for(int i=0; i<n; i++)
		mat[i][j] = false;
}

bool Matrix::is_empty() {
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
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
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			cout << mat[i][j];
		cout << endl;
	}
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

	while(!this->is_empty() && curr_eval < 0){
		curr_eval++;


	}



	return result;
}

Matrix::~Matrix() {
}
