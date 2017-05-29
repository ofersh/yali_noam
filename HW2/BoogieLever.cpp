//
//  BoogieLever.cpp
//  hw2
//
//  Created by Noam Stolero on 27/05/2017.
//  Copyright Â© 2017 Noam Stolero. All rights reserved.
//

#include "BoogieLever.hpp"

#include <iostream>
#include <sstream>

using namespace std;

/* commmand fucntion */
// break down the command and store in command struct
void BoogieLever::Command::setNewCmd(string buffer){

	stringstream ss(buffer);
	string firstArg,secArg;

	// if there is no comma, then the command can only be exit,print or load
	if(buffer.find(',')==buffer.npos){
		getline(ss,firstArg,' ');
		getline(ss,secArg,' ');

		if(firstArg=="print"){
			cmdNumber=PRINT;
			return;
		}

		if(firstArg=="exit"){
			cmdNumber=EXIT;
			return;
		}

		if(firstArg=="load"){
			fileName = secArg;
			cmdNumber = LOAD;
			return;

		}
	}else{
		// if there is comma then the commands can only be in/out bound or balance

		getline(ss,firstArg,',');
		getline(ss,secArg,',');

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

		if(secArg=="outbound"){
			cmdNumber = OUTBOUND;
			return;
		}
	}

	// if commands have not been appropriatly entered
	cmdNumber = 0;
}


/* BoogieLever functions */

// constructor
BoogieLever::BoogieLever(int len,const char *files[]){
	init_graphs(len,files);
}


void BoogieLever::run(){

	string buffer;
	Command cmd;
	bool exit=false;

	while(!exit){
		getline(cin,buffer);
		cmd.setNewCmd(buffer);		// get the current command
		switch (cmd.cmdNumber) {
		case LOAD:
			try{
				clerk.load(cmd.fileName);
			}catch(runtime_error &e)
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
		default:		// if command wasn't entered properly
			cerr << "USAGE: <port_name>,outbound/inbound/balance *or* ‘exit’ to terminate. " << endl;
			break;
		}
	}
}


// initialize graph with entered files
void BoogieLever::init_graphs(int len, const char *files[]){

	string outputFileName;

	if(len<3){	// need to have at least 3 argumets
		cerr << "not enough arguments have been entered" << endl;
		exit(1);
	}
	string currentArg=files[1];
	int i=0;

	if (currentArg!="-i"){		// -i must be entered
		cerr<<"program arguments must start with -i"<<endl;
		exit(1);
	}

	/*
     read all input files
	 */
	for (i=2 ; i<len; ++i)
	{
		currentArg=files[i];
		if(currentArg=="-o")
			break;
		try {
			// load file into graph
			clerk.load(currentArg);
		}catch(runtime_error &e)
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
    clerk.setOutputFile(outputFileName);
}
