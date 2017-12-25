/*
 * Main.cpp
 *
 *  Created on: 25 בדצמ× 2017
 *      Author: stell
 */

#include <iostream>
#include <vector>

using namespace std;
const int EMPTY = -1;

bool is_matrix_empty(bool** Sin, unsigned int N){
	for(unsigned int i=0; i<N; i++)
		for(unsigned int j=0; j<N; j++)
			if(Sin[i][j])
				return false;
	return true;
}

int find_match_matrix(unsigned int N, bool** Sin, unsigned int* pIn, unsigned int* pOut, bool** Sout){
	/*
	 * N - size of the router
	 * Sin - graph with edges between input and output
	 * pIn - indicates the favorable next ouptut queue
	 * pOut - indicates the favorable next input queue
	 * Sout - match matrix
	 */
	int rc = 0;
	int grant[N] = {EMPTY};
	vector<unsigned int> accept[N];

	while(!is_matrix_empty(Sin, N)){

		// Grant: from output to input
		for(unsigned int i=0; i<N; i++){
			for(unsigned int j=0; j<N; j++){
				// starting from the pointer's index
				unsigned int j_ind = j+pOut[i] % N;
				if(Sin[i][j_ind]){
					grant[i] = j_ind;
					accept[j_ind].push_back(i);
					break;
				}
			}
		}

		// Accept: from input to output

	}
}

int main(){
	vector<int> x[5];
	x[1].push_back(1);
	x[1].push_back(2);
	cout << "the len of the vector is: " << x[1].size() << endl;
	cout << "x[1][0] = " << x[1][0] << "| x[1][1] = " << x[1][1] << endl;

	return 0;
}



