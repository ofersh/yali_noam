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


//return port by name.
weak_ptr<Port> Model::getPort(string portName)
{
    vector<weak_ptr<Port>> portList=Port::get_port_list();
    for (weak_ptr<Port> wp : portList)
    {
        if (!wp.expired())
        {
            if (wp.lock()->getName()==portName)
                return wp;
        }
    }
    return weak_ptr<Port>{};
}


weak_ptr<Ship> Model::getShip(string shipName)
{
    for (shared_ptr<Marine_Element> sme: elements_list)
    {
        if (sme->getName()==shipName)
            if (shared_ptr<Ship> sShip=dynamic_pointer_cast<Ship>(sme))
            {
                return sShip;
            }
    }
    return weak_ptr<Ship>{};
}

