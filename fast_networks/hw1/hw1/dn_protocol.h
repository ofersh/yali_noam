//
//  dn_protocol.hpp
//  hw1
//
//  Created by Noam Stolero on 10/11/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef dn_protocol_hpp
#define dn_protocol_hpp

#include <stdio.h>
#include <string>

using std::string;

class Dn_protocol {
public:
	static bool file_to_ip_packets(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip);
    static bool ip_packets_to_file(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip);
    
private:

	struct IP_HEADER
	{
		IP_HEADER() {
			version = 4;
			header_len = 5;	//header length in 32bits. (32*5)
			tos = 0;
			id = 0;
			flags = 0;
			fragment_offset = 0;
			ttl = TTL;
			protocol = DN_PROTOCOL;	//protocol number of DN
			header_checksum = 0;
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

	static const int PACKET_LENGTH = 256;
	static const int HEADER_LENGTH = 20;
	static const int DN_PROTOCOL = 143;
	static const int TTL = 240;

<<<<<<< HEAD
	static void calculate_checksum(IP_HEADER &iph);
	static bool validate_header(IP_HEADER& iph , unsigned int source_ip, unsigned int destination_ip);
=======
	static const void calculate_checksum(IP_HEADER &iph);
	static const void write_packet(IP_HEADER, char packet[PACKET_LENGTH], char* target);
	static void endian_conversion(IP_HEADER&);
	static void endian_conversion(unsigned short* s);
	static void endian_conversion(unsigned int*);


	

>>>>>>> 69f96e924ad206644faa3b1c92cb87826ee9531e
};

#endif /* dn_protocol_hpp */
