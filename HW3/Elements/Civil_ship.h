//
//  Civil_ship.hpp
//  hw3
//
//  Created by Noam Stolero on 01/07/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef ELEMENTS_Civil_ship_hpp
#define ELEMENTS_Civil_ship_hpp

#include "Ship.h"
#include <stdio.h>

class Civil_Ships_Commands;
class Port;
class Cruiser;

class Civil_ship :public Ship {

private:
    //docking range of ship.
    constexpr static const double DOCKING_RANGE=0.1;

    double fuel_consumption;
    bool fuelling;
    weak_ptr<Port> destination;
    
public:
    Civil_ship(Type t, string name, Point pos, double fuel, double lpm,double maxV);
    virtual bool under_attack(Cruiser * attacking)=0;
    virtual ~Civil_ship()=default;
    
    
    bool dock(weak_ptr<Port> port); // try dock at given port.
    void setDestination(weak_ptr<Port> port);   //set destination to port.
    bool refuel();  //try to refuel.
    void set_Waiting_for_fuel(bool b); //for fuel flag.
    bool isFuelling()const{return fuelling;};
    weak_ptr<Port> get_destination()const{return destination;};
    virtual void advance();
    
    double getRequiredFuelAmount()const;    // for fuelling purpose.
    void fuel(double fuel);     //fuelling command.


    void enqueue(Civil_Ships_Commands *csc ); //enqueue new command.
    void pritorityCommand(Civil_Ships_Commands *csc ); //push command first.
    
    


};

#endif /* Civil_ship_hpp */
