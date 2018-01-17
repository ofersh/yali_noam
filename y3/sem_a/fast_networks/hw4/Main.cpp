/*
 * Main.cpp
 *
 *  Created on: 16 Jan 2018
 *      Author: noam
 */

#include "Router.h"
#include <iostream>

using namespace std;



int main(){

	int N=8, K=6, s;
	double p;



	Router router = Router(N, K);
	for (s = 1; s <= 3; ++s) {
		cout<<"For s=1:"<<endl;
		for (p = 0.5; p <= 0.95; p+=0.05) {
			router.run(s, p);
			cout<<p<<", "<<(router.pending_packets()/(double(K)/s))/router.iterations<<endl;

		}
	}
	cout << "number of packets is:  " << router.pending_packets() << endl;

	return 0;
}
