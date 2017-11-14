//
//  main.cpp
//  hw1
//
//  Created by Noam Stolero on 10/11/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

#include "dn_protocol.h"

using namespace std;

struct tmp{
	unsigned short  flags : 3;
	unsigned short  fragment_offset : 13;
};

int main(int argc, const char * argv[]) {
<<<<<<< HEAD
	Dn_protocol dn;
	string input = "C:/Users/yali/Documents/GitHub/yali_noam/fast_networks/hw1/hw1/dog.jpg";
	string destination = "C:/Users/yali/Documents/GitHub/yali_noam/fast_networks/hw1/hw1/dog.bin";
	string final = "C:/Users/yali/Documents/GitHub/yali_noam/fast_networks/hw1/hw1/dog_out.jpg";
	dn.file_to_ip_packets(input, destination, 1, 2);
	dn.ip_packets_to_file(destination, final, 1, 2);

=======
//	Dn_protocol dn;
//	string input = "C:/Users/stell/git/yali_noam/fast_networks/hw1/hw1/shtil.jpg";
//	string destination = "C:/Users/stell/git/yali_noam/fast_networks/hw1/hw1/out.bin";
//	dn.file_to_ip_packets(input, destination, 1, 2);
//
>>>>>>> 69f96e924ad206644faa3b1c92cb87826ee9531e
//	fstream check{ destination, ios_base::in | ios::binary };
//	char temp[20];
//	check.read(temp, 20);
//	for (int i = 0; i < 20; i++) {
//		unsigned int p = temp[i];
//		cout << p;
//	}
	



	return 0;
}
