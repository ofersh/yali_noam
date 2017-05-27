//
//  BoogieLever.cpp
//  hw2
//
//  Created by Noam Stolero on 27/05/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include "BoogieLever.hpp"

#include <iostream>
#include <sstream>

using namespace std;

void BoogieLever::Command::setNewCmd(string buffer){
	stringstream ss(buffer);
	string firstArg,secArg;
	getline(ss,firstArg,',');

	if(firstArg=="print"){
		cmdNumber=PRINT;
		return;
	}
	if(firstArg=="exit"){
		cmdNumber=EXIT;
		return;
	}

	getline(ss,secArg,',');

	if(firstArg=="load"){
		fileName = secArg;
		cmdNumber = LOAD;
		return;
	}

	port=firstArg;

	if(secArg=="balance"){
		cmdNumber = BALANCE;
		getline(ss,date);
		return;
	}

	if(secArg=="inbound"){
		cmdNumber = INBOUND;
		return;
	}

	if(secArg=="balance"){
		cmdNumber = OUTBOUND;
		return;
	}

	cmdNumber = 0;
}


BoogieLever::BoogieLever(int len, char *files[]):clerk{},outputFileName{}{
	init_graphs(len,files);
}



void BoogieLever::run(){
	string buffer;
	Command cmd;
	bool exit=false;
	while(!exit){
		getline(cin,buffer);
		cmd.setNewCmd(buffer);
		switch (cmd.cmdNumber) {
		case LOAD:
			try{
				clerk.load(cmd.fileName);
			}catch(Clerk::invalidInputException &e)
			{
				cerr<<e.what()<<endl;
			}
			break;
		case OUTBOUND:
			clerk.outboundQuery(cmd.port);
			break;
		case INBOUND:
			clerk.inboundQuery(cmd.port);
			break;
		case BALANCE:
			clerk.balance(cmd.port,cmd.date);
			break;
		case PRINT:
			clerk.print();
			break;
		case EXIT:
			exit=true;
			break;
		default:
			cout << "wrong input, try again" << endl;
			break;
		}



	}
}



void BoogieLever::init_graphs(int len, char *files[]){
	string currentArg=files[1];
	int i=0;

	if (currentArg!="-i"){
		cerr<<"program arguments must start with -i"<<endl;
		exit(1);
	}

	/*
     read all input files
	 */
	for (i=2 ; i<len; ++i)
	{
		currentArg=files[i];
		if(currentArg!="-o")
			break;
		try {
			clerk.load(currentArg);
		}catch(Clerk::invalidInputException &e)
		{
			cerr<<e.what()<<endl;
			exit(1);
		}
	}
	/* set output file.*/
	if (i<len && currentArg=="-o")
		outputFileName=files[++i];
	else
		outputFileName="output.dat";
}
