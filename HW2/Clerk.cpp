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
#include "EdgeTime.h"
#include "EdgeCargo.h"
#include <algorithm>

using std::cout;
using std::ofstream;
using std::cerr;
using std::endl;
using std::string;
using std::istringstream;
using std::stoi;
using std::for_each;
using std::shared_ptr;
using std::find;

static const string ALPHA{"abcdefghijklmnopqrstuvwxyz\
    ABCDEFGHIJKLMNOPQRSTUVWXYZ "},\
    DATE{"0123456789:/ "},\
    NUMBERS{"0123456789"};


void Clerk::load(string fileName){
    
    ifstream inputFile{fileName};
    if (inputFile.fail())
        throw OpenFileException::getExcept(fileName, 0);

    string rootPortName,line, lastPortName;
    getline(inputFile, line);
    Date RootOutBoundDate=handleFirstLine(line, fileName, rootPortName);
    trans_info.outBoundDate=RootOutBoundDate;
    //read line by line each port in the journey.
    lastPortName=rootPortName;

    int lineNum=2;
    getline(inputFile, line);
    do{
        //read transaction data.
        trans_info.setInfo(line,fileName,lineNum);
        
        //update Time and cargo graph.
        addEdges(rootPortName, lastPortName);
        
        //set current port leaving date
        trans_info.outBoundDate.setDate(trans_info.outBoundDateStr);
        
        //update\add port.
        updateRecvPort();
    
        //update root outbound deliveries.
        updateRootPort(rootPortName, RootOutBoundDate);
        

        lineNum++;
    }while(getline(inputFile, line));
    
}



Date Clerk::handleFirstLine(string & firstLine, string fileName,string &portName){
    /* new addition */

	std::stringstream ss(firstLine);



	/*************/

    string line, outBoundportName, outBoundDate;
    Date dateOfDelivery;
    int lineNum=1;
    
    //handle first line
    getline(ss,outBoundportName , ',');
    if (outBoundportName.find_first_not_of(ALPHA)!=outBoundportName.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    Port outBoundPort{outBoundportName}; //create outbound port.
    //read outbound date.
    getline(ss,outBoundDate , ',');
    if (outBoundDate.find_first_not_of(DATE)!=outBoundDate.npos)
    	throw InvalidInputException::getExcept(fileName, lineNum);
    //create delivery information and add to port.
    dateOfDelivery.setDate(outBoundDate);
    Delivery outBoundDelivery{dateOfDelivery,0};
    outBoundPort.addOutDelivery(outBoundDelivery);
    // need to check if exist. if exist just need to add the outbound
    portsMap.emplace(outBoundportName,Port{outBoundPort});
    portName=outBoundportName;
    return dateOfDelivery;
}

void Clerk::Transaction_Info::setInfo(string line, string fileName, int lineNum){
    
    istringstream iss{line};
    
    getline(iss,inBoundPortName,',');
    if (inBoundPortName.find_first_not_of(ALPHA)!=line.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    getline(iss, inBoundDateStr, ',');
    if (inBoundDateStr.find_first_not_of(DATE)!=line.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    getline(iss, cargoStr, ',');
    if (cargoStr.find_first_not_of(NUMBERS)!=line.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    getline(iss, outBoundDateStr, ',');
    if (outBoundDateStr.find_first_not_of(DATE)!=line.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    
    inBoundDate.setDate(inBoundDateStr);
    cargoAmount=stoi(cargoStr);

    
}

void Clerk::addEdges(string rootPort, string lastPort){

    //adding date edge from last port to current.
    unordered_map<string,Edges>::iterator it;
    

    //create a new TimeEdge. from lastPort to currentPort (held in trans_info).
    shared_ptr<Edge> newTimeEdge{new EdgeTime{(trans_info.inBoundDate)-(trans_info.outBoundDate)
        ,trans_info.inBoundPortName}};
    
    //first find if Port exist in map exist
    it=timeEdgesMap.find(lastPort);
    if (it!=timeEdgesMap.end()){
        //if port exist check in Edges Vector for Edge. if does update, else push back.
        Edges::iterator exist=find(it->second.begin(), it->second.end(), newTimeEdge);
        if (exist!=it->second.end())
            (*exist)->updateEdge(*newTimeEdge);
        else
            it->second.push_back(newTimeEdge);
    }else{
        //create a new <Port,Edges> pair and add edge.
        Edges v;
        v.push_back(newTimeEdge);
        timeEdgesMap.emplace(lastPort,v);
    }
    shared_ptr<Edge> timeEdge{newTimeEdge};
    
    
    shared_ptr<Edge> cargoEdge{new EdgeCargo{trans_info.cargoAmount,trans_info.inBoundPortName}};
    
    it=cargoEdgesMap.find(rootPort);
    if(it!=timeEdgesMap.end()){
        //TODO: check if edge does exist, if yes invoke update edge.
        (it->second).push_back(cargoEdge);
    }else{
        Edges v;
        v.push_back(cargoEdge);
        timeEdgesMap.emplace(lastPort,v);
    }

    
    
    
    
    
    
    //adding cargoEdge from root to current.
}


void Clerk::updateRecvPort(){
    
    Delivery inboundDelivery{trans_info.inBoundDate,trans_info.cargoAmount};

    unordered_map<string, Port>::iterator it;
    it=portsMap.find(trans_info.inBoundPortName);
    if (it!=portsMap.end())
        it->second.addInDelivery(inboundDelivery);
    
    Port current{trans_info.inBoundPortName};
    current.addInDelivery(inboundDelivery);
    portsMap.emplace(trans_info.inBoundPortName,current);
}


void Clerk::updateRootPort(string rootPortName, Date rootOutBound){
    
    Delivery rootOutDelivery{rootOutBound,trans_info.cargoAmount};
    unordered_map<string, Port>::iterator it=portsMap.find(rootPortName);
    (it->second).addOutDelivery(rootOutDelivery);
    
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
			printPort(cout,E);
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
			for (; edgesIter != edgesIterEnd; ++edgesIter) {
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
		Date d;
        if (!d.setDate(date)){
            cerr<<"Invalid Date"<<endl;
            return;
        }
        cout << it->second.calculateAmountOfContainers(d) << endl;

	}


//TODO output to file.
void Clerk::printPort(ostream& out,Edges& E){
		for_each(E.begin(),E.end(),\
				[](shared_ptr<Edge> e){\
			out << e->getDestination() << ", " << e->getWeight() << endl;\
		});

	}

void Clerk::printGraph(ostream& out,string type,unordered_map<string,Edges>& map){
		unordered_map<string,Edges>::iterator mapIter = map.begin();
		unordered_map<string,Edges>::iterator mapIterEnd = map.end();
		for (; mapIter!= mapIterEnd; ++mapIter) {
			// get all the edges that belong to a certain vertex
			Edges E = mapIter->second;
			out << mapIter->first << ": " << endl;
			printPort(out,E);
		}
	}

	void Clerk::print(){
		ofstream output(outputFile);
		if(!output.is_open()){
			cerr << "ERROR opening/reading the specified file." << endl;
			return;
		}
		printGraph(output,"time",timeEdgesMap);
		printGraph(output,"cargo",cargoEdgesMap);
	}


