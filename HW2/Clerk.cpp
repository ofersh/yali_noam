//
//  Clerk.cpp
//  hw2
//
//  Created by Noam Stolero on 27/05/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include "Clerk.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::istringstream;
using std::stoi;
using std::for_each;



static const string ALPHA{"abcdefghijklmnopqrstuvwxyz\
    ABCDEFGHIJKLMNOPQRSTUVWXYZ "},\
	DATE{"0123456789:/ "},\
	NUMBERS{"0123456789"};




	void Clerk::load(string fileName){

		ifstream inputFile{fileName};
		if (inputFile.fail())
			throw OpenFileException::getExcept(fileName, 0);

		string rootPort;
		Date rootOutBoundDate=handleFirstLine(inputFile, fileName, rootPort);

		//read rest of the lines.
		string inBoundPortName, inBoundDateStr, outBoundDateStr, cargo,line;
		Date inBoundDate,OutBoundDate;
		int lineNum=2, cargoAmount;
		getline(inputFile, line);
		istringstream iss{line};
		do{
			getline(iss,inBoundPortName,',');
			if (inBoundPortName.find_first_not_of(ALPHA)!=inBoundDateStr.npos)
				throw InvalidInputException::getExcept(fileName, lineNum);
			getline(iss, inBoundDateStr, ',');
			if (inBoundDateStr.find_first_not_of(DATE)!=inBoundDateStr.npos)
				throw InvalidInputException::getExcept(fileName, lineNum);
			getline(iss, cargo, ',');
			if (inBoundDateStr.find_first_not_of(NUMBERS)!=inBoundDateStr.npos)
				throw InvalidInputException::getExcept(fileName, lineNum);
			getline(iss, outBoundDateStr , ',');
			if (inBoundDateStr.find_first_not_of(DATE)!=inBoundDateStr.npos)
				throw InvalidInputException::getExcept(fileName, lineNum);
			cargoAmount=stoi(cargo);
			inBoundDate.setDate(inBoundDateStr);


		}while(getline(inputFile, line));

	}



	Date Clerk::handleFirstLine(ifstream & inputFile, string fileName,string &portName){

		string line, outBoundportName, outBoundDate;
		Date dateOfDelivery;
		int lineNum=1;

		//handle first line
		getline(inputFile,outBoundportName , ',');
		if (outBoundportName.find_first_of(ALPHA)!=outBoundportName.npos)
			throw InvalidInputException::getExcept(fileName, lineNum);
		Port outBoundPort{outBoundportName}; //create outbound port.
		//read outbound date.
		lineNum++;
		getline(inputFile,outBoundDate , ',');
		if (outBoundDate.find_first_of(DATE)!=outBoundDate.npos)
			throw InvalidInputException::getExcept(fileName, lineNum);

		//create delivery information and add to port.
		dateOfDelivery.setDate(outBoundDate);
		Delivery outBoundDelivery{dateOfDelivery,0};
		outBoundPort.addOutDelivery(outBoundDelivery);

		portsMap.emplace(dateOfDelivery,new Port{outBoundPort});
		portName=outBoundportName;
		return dateOfDelivery;
	}

	/* query functions */

	/* print to screen all out bound ports and the time to get to them */
	void Clerk::outboundQuery(string port){
		/* check  if port exist */
		unordered_map<string,Edges>::iterator it = timeEdgesMap.find(port);
		if(it==timeEdgesMap.end()){
			cerr << port << ": does not exist in the database." << endl;
			return;
		}

		/* get all the outgoing edges from the port */
		Edges E = it->second;

		/* print all the outgping ports */
		if(E.size() < 1)
			cout << port << ": no outbound ports" << endl;
		else
			printPort(E);
	}

	/* print all the ports entering to the port */
	void Clerk::inboundQuery(string port){
		bool hasInbound=false;
		// getting the map iterator. checking all the vertices in the map
		unordered_map<string,Edges>::iterator mapIter = timeEdgesMap.begin();
		unordered_map<string,Edges>::iterator mapIterEnd = timeEdgesMap.end();
		for (; mapIter!= mapIterEnd; ++mapIter) {

			// get all the edges that belong to a certain vertex
			Edges E = mapIter->second;

			// checking all the edges in the vertex
			Edges::iterator edgesIter = E.begin();
			Edges::iterator edgesIterEnd = E.end();
			for (edgesIter = 0; edgesIter < edgesIterEnd; ++edgesIter) {
				Edge* e = edgesIter->get();
				// if edge is pointing to the entered vertex
				if(e->getDestination()==port){
					hasInbound=true;
					cout << mapIter->first << ", " << e->getWeight() << endl;
				}
			}
		}

		if(!hasInbound)
			cout << port << ": no inbound ports" << endl;
	}


	void Clerk::balance(string port,string date){
		unordered_map<string,Port>::iterator it = portsMap.find(port);
		if(it == portsMap.end()){
			cerr << port << " port does not exist in the database" << endl;
			return;
		}
		Date d(date);
		cout << it->second.calculateAmountOfContainers(d) << endl;

	}

	void printPort(Edges& E){
		for_each(E.begin(),E.end(),\
				[](shared_ptr<Edge> e){\
			cout << e->getDestination() << ", " << e->getWeight() << endl;\
		});

	}

	void printGraph(string type,unordered_map<string,Edges>& map){
		unordered_map<string,Edges>::iterator mapIter = map.begin();
		unordered_map<string,Edges>::iterator mapIterEnd = map.end();
		for (; mapIter!= mapIterEnd; ++mapIter) {
			// get all the edges that belong to a certain vertex
			Edges E = mapIter->second;
			cout << mapIter->first << ": " << endl;
			printPort(E);
		}
	}

	void Clerk::print(){
		printGraph("time",timeEdgesMap);
		printGraph("cargo",cargoEdgesMap);
	}


