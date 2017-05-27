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

using std::cerr;
using std::endl;
using std::string;
using std::istringstream;
using std::stoi;



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
    
    //read line by line each port in the journey.
    string inBoundPortName, inBoundDateStr, outBoundDateStr, cargo, line,\
            srcPort=rootPort;

    Date inBoundDate,OutBoundDate{rootOutBoundDate};
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
        //update Time graph.
        timeEdgesMap.emplace(srcPort, new EdgeTime{inBoundDate-OutBoundDate,inBoundPortName});
        cargoEdgesMap.emplace(rootPort,new EdgeCargo{cargoAmount,inBoundPortName});
        OutBoundDate.setDate(outBoundDateStr);
        
        
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



