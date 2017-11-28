//
//  dn_protocol.hpp
//  hw1
//
//  Created by Noam Stolero on 10/11/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef ip_file_handler_h
#define ip_file_handler_h

#include <stdio.h>
#include <string>

using std::string;

class ip_file_handler {
public:
	static bool file_to_ip_packets(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip);
    static bool ip_packets_to_file(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip);
    
private:

	struct IP_HEADER
	{
		/* Header struct contains all relevant fields.
		*/
		IP_HEADER() { //constructor for initialization.
			version = 4;
			header_len = 5;	//header length in 32bits. (32*5)
			tos = 0;
			total_length = 0;
			id = 0;
			flags = 0;
			fragment_offset = 0;
			ttl = TTL;
			protocol = DN_PROTOCOL;	//protocol number of DN
			header_checksum = 0;
			source_ip = 0;
			destination_ip = 0;
		}
		unsigned char  version : 4;
		unsigned char  header_len : 4;
		unsigned char  tos = 0;
		unsigned short total_length;
		unsigned short id = 0;
		unsigned short  flags : 3;
		unsigned short  fragment_offset : 13;
		unsigned char  ttl;
		unsigned char  protocol;
		unsigned short header_checksum;
		unsigned int source_ip;
		unsigned int destination_ip;
	};

	// Constants.
	static const int PACKET_LENGTH = 256;
	static const int HEADER_LENGTH = 20;
	static const int DN_PROTOCOL = 143;
	static const int TTL = 240;


	static bool validate_header(IP_HEADER& iph , unsigned int source_ip, unsigned int destination_ip);
	static void calculate_checksum(IP_HEADER &iph);
	static IP_HEADER endian_conversion(IP_HEADER);
};

#endif /* ip_file_handler */
