/*
 * Main.cpp
 *
 *  Created on: 25 ����� 2017
 *      Author: stell
 */

#include <iostream>
#include "Matrix.h"

#define SIZE 5
using namespace std;

void print_pointers(unsigned int* pters, unsigned int size, string type )
{
	for (unsigned int i = 0; i < size; ++i) {
		cout << i << " "<< type<< pters[i];
	}
	cout<<endl;
}




void matrix_run(){
	int input[] = {1,0,1,0,0,
				   0,1,1,0,1,
				   0,0,0,0,1,
				   1,0,1,1,0,
				   0,1,0,1,0};
	Matrix sIn(SIZE, input);
	unsigned int pIn[SIZE] = {0,2,2,1,4};
	unsigned int pOut[SIZE] = {1,2,2,0,0};
	print_pointers(pIn, SIZE, "pIn: ");
	print_pointers(pOut, SIZE, "pOut: ");
	sIn.print();


	Matrix sOut = sIn.find_match_matrix(pIn, pOut, 5);

	print_pointers(pIn, SIZE, "pIn: ");
	print_pointers(pOut, SIZE, "pOut: ");
	sOut.print();
}

int main(){
	matrix_run();
	return 0;
}



