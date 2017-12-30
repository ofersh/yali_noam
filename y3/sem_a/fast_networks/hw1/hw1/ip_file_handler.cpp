
#include "ip_file_handler.h"
#include <fstream>
#include <iostream>

using namespace std;


bool ip_file_handler::file_to_ip_packets(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip){
    /*	Read file break it down to 256 size packet, adds header that complies to DN protcol. */
	fstream fin{ input_file_name, ios_base::in | ios_base::binary};
	fstream fout{ output_file_name, ios_base::out | ios_base::binary };

	char packet[PACKET_LENGTH] = {0};
	long read_size = 0;

	IP_HEADER iph, iph_for_writting;
	iph.source_ip = source_ip;
	iph.destination_ip = destination_ip;

	bool working = true;
	while (working) 
    {
		/* Read 256 or less bytes. Build header and write it as a packet. */
		
		// Read data.
		if (!fin.read(packet, PACKET_LENGTH))
			working = false;
		read_size = fin.gcount();

		// Generate header.
		iph.total_length = (unsigned short) read_size + HEADER_LENGTH;
		iph.header_checksum = 0;
		calculate_checksum(iph);
		
		// Write new packet. after big endian conversion.
		iph_for_writting = endian_conversion(iph);
		fout.write(reinterpret_cast<char*>(&iph_for_writting), HEADER_LENGTH);
		fout.write(packet, read_size);
    }

	return true;
}

bool ip_file_handler::ip_packets_to_file(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip)
{
	/*	Read file, containing DN protocol headers and combine all the packets into one file */
	 fstream fin{ input_file_name, ios_base::in | ios_base::binary};
	 fstream fout{ output_file_name, ios_base::out | ios_base::binary };

	 char packet[PACKET_LENGTH] = {0};
	 IP_HEADER iph;
	 bool working = true;
	 while (working)
	 {
		 /* Read header, if the header is valid, read the packet and write it to file */

		 // Read header and validate
		 fin.read(reinterpret_cast<char*>(&iph), HEADER_LENGTH);
		 iph = endian_conversion(iph);
		 if (!validate_header(iph, source_ip, destination_ip))
			 return false;
		 // Read packet and write to file
		 long packet_size = iph.total_length - HEADER_LENGTH;
		 if (!fin.read(packet, packet_size))
			 working = false;
		 fout.write(packet, packet_size);
	 }

	return true;
}

void ip_file_handler::calculate_checksum(IP_HEADER &iph)
{
	// Calculate ip header checksum by Words

	int checksum = 0;
	unsigned short *words_p;
	words_p = reinterpret_cast<unsigned short*>(&iph);

	// Sum all the header as groups of short
	for (int i = 0; i < HEADER_LENGTH / 2; i++, words_p++)
	{
		checksum += *words_p;
	}

	// The sum of the header can be longer than 2^16 but not more the 2^17
	unsigned short * short_checksum = reinterpret_cast<unsigned short*>(&checksum);
	iph.header_checksum = ~(short_checksum[0] + short_checksum[1]);	 
}

bool ip_file_handler::validate_header(IP_HEADER& iph , unsigned int source_ip, unsigned int destination_ip)
{
	// Verify that the packet header is not corrupted
	if (iph.source_ip != source_ip || iph.destination_ip != destination_ip || iph.protocol != DN_PROTOCOL)
		return false;

	// Verify that the header's fields have not been corrupted during the transittion
	calculate_checksum(iph);
	return !iph.header_checksum;

	

}

ip_file_handler::IP_HEADER ip_file_handler::endian_conversion(IP_HEADER iph) {
	// Convert the header from little endian to big endian
	int len = sizeof(iph);
	char* bytes = reinterpret_cast<char*>(&iph);

	for(int i=0; i<len; i+=2){
		char tmp = bytes[i];
		bytes[i] = bytes[i+1];
		bytes[i+1] = tmp;
	}

	return iph;
}

