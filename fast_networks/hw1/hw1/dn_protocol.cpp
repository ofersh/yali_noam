
#include "dn_protocol.h"
#include <fstream>
#include <iostream>

using namespace std;


bool Dn_protocol::file_to_ip_packets(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip){
    fstream fin{ input_file_name, ios_base::in | ios_base::binary};
	fstream fout{ output_file_name, ios_base::out | ios_base::binary };

	char packet[PACKET_LENGTH] = {0};
	char packet_with_iph[PACKET_LENGTH + HEADER_LENGTH] = {0};
	long read_size = 0;

	int read_bytes = 0;

	IP_HEADER iph;
	iph.source_ip = source_ip;
	iph.destination_ip = destination_ip;


	while (fin.read(packet, PACKET_LENGTH)) 
    {
		read_size = fin.tellg() % PACKET_LENGTH;
		if (read_size == 0)
			 read_size = PACKET_LENGTH;

		read_bytes += read_size;
		iph.total_length = (unsigned short) read_size + HEADER_LENGTH;
		iph.header_checksum = 0;
		calculate_checksum(iph);
		fout.write(reinterpret_cast<char*>(&iph), HEADER_LENGTH);
		fout.write(packet, read_size);
    }

	cout << "the program read " << read_bytes << " bytes" << endl;
	return true;
}

bool Dn_protocol::ip_packets_to_file(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip)
{
	 fstream fin{ input_file_name, ios_base::in | ios_base::binary};
	 fstream fout{ output_file_name, ios_base::out | ios_base::binary };

	 char packet[PACKET_LENGTH] = {0};
	 IP_HEADER iph;
	 long read_size = 0;

	 int read_bytes = 0;

	 while (fin.read(reinterpret_cast<char*>(&iph) , HEADER_LENGTH))
	 {
		 if (!validate_header(iph, source_ip, destination_ip)){
			 return false;
		 }
		 long packet_size= iph.total_length - HEADER_LENGTH;
		 cout<<"packet size is:"<<packet_size<<endl;
		 fin.read(packet, packet_size);
		 fout.write(packet, packet_size);
	 }

	return false;
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
