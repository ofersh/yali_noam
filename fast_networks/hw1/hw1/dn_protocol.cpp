
#include "dn_protocol.h"
#include <fstream>
#include <iostream>

using namespace std;


bool Dn_protocol::file_to_ip_packets(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip){
    fstream fin{ input_file_name, ios_base::in | ios_base::binary};
	fstream fout{ output_file_name, ios_base::out | ios_base::binary };

	char packet[PACKET_LENGTH] = {0};
	long read_size = 0;


	IP_HEADER iph, iph_for_writting;
	iph.source_ip = source_ip;
	iph.destination_ip = destination_ip;


	while (fin.read(packet, PACKET_LENGTH)) 
    {
		read_size = fin.tellg() % PACKET_LENGTH;
		if (read_size == 0)
			 read_size = PACKET_LENGTH;

		iph.total_length = (unsigned short) read_size + HEADER_LENGTH;
		iph.header_checksum = 0;
		calculate_checksum(iph);
		iph_for_writting = endian_conversion(iph);
		fout.write(reinterpret_cast<char*>(&iph_for_writting), HEADER_LENGTH);
		fout.write(packet, read_size);
    }

	return true;
}

bool Dn_protocol::ip_packets_to_file(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip)
{
	 fstream fin{ input_file_name, ios_base::in | ios_base::binary};
	 fstream fout{ output_file_name, ios_base::out | ios_base::binary };

	 char packet[PACKET_LENGTH] = {0};
	 IP_HEADER iph;
	 int i=0;
	 while (fin.read(reinterpret_cast<char*>(&iph) , HEADER_LENGTH))
	 {
		 iph = endian_conversion(iph);
		 i++;
		 if (!validate_header(iph, source_ip, destination_ip)){
			 cout << "the " << i << " package head is invalid" << endl;
			 return false;
		 }
		 long packet_size= iph.total_length - HEADER_LENGTH;
		 fin.read(packet, packet_size);
		 fout.write(packet, packet_size);
	 }

	return true;
}

void Dn_protocol::calculate_checksum(IP_HEADER &iph)
{
	// Calculate ip header checksum by Words

	int checksum = 0;
	unsigned short *words_p;
	words_p = reinterpret_cast<unsigned short*>(&iph);

	for (int i = 0; i < HEADER_LENGTH / 2; i++, words_p++)
	{
		checksum += *words_p;
	}

	unsigned short * short_checksum = reinterpret_cast<unsigned short*>(&checksum);
	iph.header_checksum = ~(short_checksum[0] + short_checksum[1]);
}

bool Dn_protocol::validate_header(IP_HEADER& iph , unsigned int source_ip, unsigned int destination_ip)
{
	if (iph.source_ip != source_ip || iph.destination_ip != destination_ip || iph.protocol != DN_PROTOCOL)
		return false;

	calculate_checksum(iph);

	return !iph.header_checksum;

	

}

void Dn_protocol::endian_conversion(unsigned int* num) {
	unsigned short* tmp = reinterpret_cast<unsigned short*>(num);
	endian_conversion(tmp);
	endian_conversion(tmp + 1);
}

void Dn_protocol::endian_conversion(unsigned short* s) {
	char tmp;
	char* tmp_short = reinterpret_cast<char*>(s);
	tmp = tmp_short[1];
	tmp_short[1] = tmp_short[0];
	tmp_short[0] = tmp;
}

Dn_protocol::IP_HEADER Dn_protocol::endian_conversion(IP_HEADER& iph) {
	IP_HEADER res = iph;
	endian_conversion(&res.total_length);
	endian_conversion(&res.id);
	endian_conversion(&res.header_checksum);
	endian_conversion(&res.source_ip);
	endian_conversion(&res.destination_ip);
	return res;
}

