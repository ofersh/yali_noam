/*
 * Matrix.h
 *
 *  Created on: Dec 25, 2017
 *      Author: yali
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <vector>
using namespace std;


class Matrix {
public:
	Matrix(int N);
	Matrix(int N, int* input);
	bool get_index(int i, int j);
	void clean_row(int i);
	void clean_col(int i);
	bool is_empty();
	void set_false(int i, int j);
	void set_true(int i, int j);
	void print();
	Matrix find_match_matrix(unsigned int* pIn, unsigned int* pOut, int max_eval);
	virtual ~Matrix();

private:
	vector<bool*> mat;
	int n;
};

#endif /* MATRIX_H_ */
