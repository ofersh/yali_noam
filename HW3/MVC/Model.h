/*
 * Model.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include "../Elements/MarineElement.h"
#include <memory>
#include "Model.h"

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
    
    virtual ~Model();

    
    void go();  // one hour shift.
    void status()const; // invoke status on all elements.
    
    // Ship creation.
    bool create(string name, Ship::Type type, int x, int y, int resistence=0, int force=0);

    // getters from model
    shared_ptr<Port> getPort(string portName);

    shared_ptr<Ship> getShip(string shipName);

    Ship::Type getShipType(string shipName);

};

#endif /* MODEL_H_ */
