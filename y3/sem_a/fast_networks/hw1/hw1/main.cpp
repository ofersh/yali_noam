#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

#include "ip_file_handler.h"

using namespace std;


int main(int argc, const char * argv[]) {

	ip_file_handler dn;
	string input = "shtil.jpg";
	string network = "shtil.bin";
	string destination = "shtil_out.txt";
	cout << "Writing " << input << " to the network" << endl;
	if(!dn.file_to_ip_packets(input, network, 1, 2)){
		cout << "Failed to write the packets" << endl;
		exit(1);
	}
	cout << "Finished writing " << input << " to the network" << endl;

	cout << "Reading to " << destination << " from the network" << endl;
	if(!dn.ip_packets_to_file(network, destination, 3, 1)){
		cout << "Failed to read the packets" << endl;
		exit(1);
	}

	cout << "Finished reading to " << destination << " from the network" << endl;


	return 0;
}
