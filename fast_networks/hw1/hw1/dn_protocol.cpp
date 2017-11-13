
#include "dn_protocol.h"
#include <fstream>
#include <iostream>

using namespace std;


bool Dn_protocol::file_to_ip_packets(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip){
    fstream fin{ input_file_name, ios_base::in | ios_base::binary};
	fstream fout{ output_file_name, ios_base::out | ios_base::binary };

	char packet[PACKET_LENGTH] = {0};
	char packet_with_iph[PACKET_LENGTH + HEADER_LENGTH];
	long read_size = 0;

	int read_bytes = 0;

	IP_HEADER iph;
	iph.source = source_ip;
	iph.destination = destination_ip;


	while (fin.read(packet, PACKET_LENGTH)) 
    {
		read_size = fin.tellg() % PACKET_LENGTH;
		if (read_size == 0)
			 read_size = PACKET_LENGTH;

		read_bytes += read_size;
		iph.total_length = (unsigned short) read_size + HEADER_LENGTH;
		calculate_checksum(iph);
		fout.write(reinterpret_cast<char*>(&iph), HEADER_LENGTH);
		fout.write(packet, read_size);
    }

	cout << "the program read " << read_bytes << " bytes" << endl;
	return true;
}

bool Dn_protocol::ip_packets_to_file(string input_file_name, string output_file_name, unsigned int source_ip, unsigned int destination_ip)
{
	return false;
}


const void Dn_protocol::calculate_checksum(IP_HEADER &iph)
{
	// Calculate ip header checksum by Words

	int checksum = 0;
	short *words_p;
	words_p = reinterpret_cast<short*>(&iph);

	iph.header_checksum = 0;

	for (int i = 0; i < HEADER_LENGTH / 2; i++, words_p++)
	{
		checksum += *words_p;
	}
	iph.header_checksum = ~checksum;
}

const void Dn_protocol::write_packet(IP_HEADER, char packet[PACKET_LENGTH], char * target)
{
	

}

void Dn_protocol::endian_conversion(unsigned int* num) {
	unsigned short* tmp = reinterpret_cast<unsigned short*>(num);
	endian_conversion(tmp);
	endian_conversion(tmp + 1);
}

void Dn_protocol::endian_conversion(unsigned short* s) {
	char tmp;
	char* tmp_short = reinterpret_cast<char*>(s);
	tmp = tmp_short[0];
	tmp_short[1] = tmp_short[0];
	tmp_short[0] = tmp;
}

void Dn_protocol::endian_conversion(IP_HEADER& iph) {

	endian_conversion(&iph.total_length);
	endian_conversion(&iph.id);
	endian_conversion(&iph.header_checksum);
	endian_conversion(&iph.source);
	endian_conversion(&iph.destination);


}

