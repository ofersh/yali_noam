/*
 * Model.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef MVC_MODEL_H_
#define MVC_MODEL_H_

#include <vector>
#include "../Elements/Ship.h"
#include "../Elements/Port.h"
#include "../Elements/Shipyard.h"
#include <memory>

class View;

using std::vector;
using std::shared_ptr;

class Model {
    
private:
    
    Model()=default;
    vector<shared_ptr<Marine_Element>> elements_list;
    weak_ptr<View> view;

    
public:
	
    //Meyer's singelton.
    static Model & getModel(){
        static Model model;
        return model;
    };
    
    const vector<shared_ptr<Marine_Element>>& get_element_list()const{return elements_list;};
    
    virtual ~Model()=default;

    void addPort(string port_name,double x,double y,int maxFuel,int fph);
    void go();  // one hour shift.
    void status()const; // invoke status on all elements.
    void addCommand(string ship,Ships_commands* shipCmd);
    
    // Ship creation.
    void create(string name, Ship::Type type, double x, double y, int arg1,int arg2);

    // getters from model
    weak_ptr<Port> getPort(string portName);

    weak_ptr<Ship> getShip(string shipName);

    Ship::Type getShipType(string shipName);

    void setView(shared_ptr<View> v);
};

#endif /* MODEL_H_ */
