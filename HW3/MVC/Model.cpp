/*
 * Model.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Model.h"
#include <iostream>

using namespace std;
Model::Model() {
	// TODO Auto-generated constructor stub

}



void Model::addPort(string port_name, double x, double y, int maxFuel, int fph){
    cout<<"Model::addPort()"<<endl;
}


void Model::go()
{
    cout<<"Model::go()"<<endl;
}

void Model::status()const
{
    cout<<"Model::status()"<<endl;
}

bool Model::create(string name, Ship::Type type, int x, int y, int resistence, int force)
{
    cout<<"Model::create()"<<endl;
    return true;
}


shared_ptr<Port> Model::getPort(string portName)
{
    cout<<"Model::getPort"<<endl;
    return shared_ptr<Port>{};
}
