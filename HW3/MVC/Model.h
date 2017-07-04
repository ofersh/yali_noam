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
#include <memory>


using std::vector;
using std::shared_ptr;

class Model {
    
private:
    
    Model();
    vector<shared_ptr<Marine_Element>> elements_list;
    
    
public:
	
    //Meyer's singelton.
    static Model & getModel(){
        static Model model;
        return model;
    };
    
    virtual ~Model()=default;

    void addPort(string port_name,double x,double y,int maxFuel,int fph);
    void go();  // one hour shift.
    void status()const; // invoke status on all elements.
    
    // Ship creation.
    bool create(string name, Ship::Type type, int x, int y, int resistence=0, int force=0);

    // getters from model
    weak_ptr<Port> getPort(string portName);

    weak_ptr<Ship> getShip(string shipName);

    Ship::Type getShipType(string shipName);

};

#endif /* MODEL_H_ */
