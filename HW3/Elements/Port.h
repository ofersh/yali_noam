/*
 * Port.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef ELEMENTS_PORT_H_
#define ELEMENTS_PORT_H_

#include "MarineElement.h"
#include <queue>
#include <deque>
#include <memory>
#include <vector>

using std::vector;
class Freighter;
class Civil_ship;

using std::weak_ptr;
using std::shared_ptr;
using std::queue;

class Port: public Marine_Element {
    
private:
    double containers;
    
    queue<Civil_ship*> fuel_queue;  //think about it, maybe ask from model ship by name?
    static vector<weak_ptr<Port>> ports_list;
    
    Port(string name,Point pos, double fuel);

public:
    shared_ptr<Port> create_port(string name,Point pos, double fuel);
	~Port();
    
    void unload_ship (unsigned int amount);
    void load_ship (Freighter& fr);
    void fuel_request (Civil_ship* ship);
    
    weak_ptr<Port> portAt(int x, int y)const;
    
    void go();

    //mostly for cruise ship.
    static vector<weak_ptr<Port>> get_port_list(){return ports_list;};
};

#endif /* PORT_H_ */
