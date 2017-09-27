

#include "Port.h"
#include "Freighter.h"
#include <iostream>

using namespace std;

//init ports list.
vector<weak_ptr<Port>> Port::ports_list{};

//CTOR for port.
Port::Port(string name, Point pos, double fuel, double fuel_generate):Marine_Element(name,pos,fuel), fuel_generate_rate(fuel_generate)
{
}


// The  only way to get port is to use this function.
shared_ptr<Port> Port::create_port(string name, Point pos, double fuel, double fuel_generate)
{
    shared_ptr<Port> sp{new Port(name,pos,fuel,fuel_generate)};
    ports_list.push_back(sp);
    return sp;
}


//load given ship with cargo.
void Port::load_ship(Freighter &fr)
{
    unsigned int amount=fr.empty_space();
    fr.add_cargo(amount);
}


//adding ship to fuel request.
void Port::fuel_request( Civil_ship* ship)
{
    fuel_queue.push(ship);
    ship->set_Waiting_for_fuel(true);
}


// fullfill fuel request by FIFO.
void Port::go()
{
    //generate fuel
    Marine_Element::addFuel(fuel_generate_rate);
    
    if(fuel_queue.empty())
        return;
    Civil_ship * ship_to_fuel=fuel_queue.front();
    fuel_queue.pop();
    double amount=ship_to_fuel->getRequiredFuelAmount();
    double availble=Marine_Element::getCurrentFuel();
    if (amount>availble)
        amount=availble;
    ship_to_fuel->fuel(amount);
    ship_to_fuel->set_Waiting_for_fuel(false);
}

//get list of ports.
vector<weak_ptr<Port>> Port::get_port_list()
{
    return ports_list;
}



//print port status.
void Port::status()const
{
    Point mypos=Marine_Element::getPosition();
    
    cout<<"Port "<<Marine_Element::getName()<<" at Position ";
    mypos.print();
    cout.precision(1);
    cout<<", Fuel availble: "<<getCurrentFuel()<<" kl."<<endl;
    
    
}




