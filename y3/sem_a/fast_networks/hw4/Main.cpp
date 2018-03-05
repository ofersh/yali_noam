#include "Router.h"
#include <iostream>
#include <fstream>

using namespace std;



int main(){

	int N=8, K=6, s;
	double p;

	fstream output = fstream("result.csv", ios::out);

	Router router = Router(N, K);
	output << "P, S1, S2, S3" << endl;
	for (p = 0.5; p <= 0.95; p+=0.05) {
		cout << "running p: " << p << endl;
		output<<p;
		for (s = 1; s <= 3; ++s) {
			router.reset_router();
			double real_packets = router.run(s, p) / K;
			double avg_pkt = real_packets/router.iterations;
			double avg_delay = (avg_pkt * p) / N;
			output<<", "<< avg_delay;
		}
		output << endl;
	}

	return 0;
}
