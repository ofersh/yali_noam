/*
 * Main.cpp
 *
 *  Created on: 25 בדצמ× 2017
 *      Author: stell
 */

#include <iostream>
#include "Matrix.h"

#define SIZE 5

using namespace std;
const int EMPTY = -1;

bool is_matrix_empty(bool** Sin, unsigned int N){
	for(unsigned int i=0; i<N; i++)
		for(unsigned int j=0; j<N; j++)
			if(Sin[i][j])
				return false;
	return true;
}

void clear_row_and_col(bool** Sin, unsigned int N, unsigned int r, unsigned int c){
	for(unsigned int i=0; i<N; i++){
		Sin[i][c] = false;
		Sin[r][i] = false;
	}
}

int find_match_matrix(bool** Sin, unsigned int* pIn, unsigned int* pOut, bool** Sout, unsigned int N=SIZE, unsigned int max_iter=5){
	/*
	 * N - size of the router
	 * Sin - graph with edges between input and output
	 * pIn - indicates the favorable next ouptut queue
	 * pOut - indicates the favorable next input queue
	 * Sout - match matrix
	 * reutrn value: curr_iter - amount of iterations the iSlip as made
	 */
	unsigned int curr_iter = 0;
	int grant[N] = {EMPTY};
	vector<unsigned int> accept[N];

	while(!is_matrix_empty(Sin, N) && curr_iter < max_iter){
		curr_iter++;
		// Grant: from output to input
		for(unsigned int j=0; j<N; j++){
			for(unsigned int i=0; i<N; i++){
				// starting from the pointer's index
				unsigned int i_ind = (i+pOut[j]) % N;

				if( Sin[i_ind][j] ){
					grant[j] = i_ind;
					break;
				}
			}
		}

		// Accept: from input to output
		for(unsigned int i=0; i<N; i++){
			for(unsigned int j=0; j<N; j++){
				unsigned int j_ind = (j+pIn[i]) % N;

				if(grant[j_ind] == i){
					Sout[i][j_ind] = true;
					clear_row_and_col(Sin,N,i,j_ind);
					pIn[i] = (j_ind+1) % N;
					pOut[j_ind] = (i+1) % N;
					break;
				}
			}
		}

	}
	cout << "stop here" << endl;
	return curr_iter;
}



int main(){
	bool mat[SIZE][SIZE] = {true,false,true,false,false,
							false,true,true,false,true,
							false,false,false,false,true,
							true,false,true,true,false,
							false,true,false,true,false};

	bool** Sin, **Sout;
	Sin = new bool*[SIZE];
	Sout = new bool*[SIZE];
	for(int i=0; i<SIZE; i++){
		Sin[i] = new bool[SIZE];
		Sout[i] = new bool[SIZE];

		for( int j=0; j<SIZE; j++){
			Sin[i][j] = mat[i][j];
			Sout[i][j] = false;
		}
	}
	unsigned int pIn[SIZE] = {0,2,2,1,4};
	unsigned int pOut[SIZE] = {1,2,2,0,0};

	cout << find_match_matrix(Sin,pIn, pOut, Sout,SIZE, 5);



	return 0;
}



