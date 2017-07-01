/*
 * Port.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef PORT_H_
#define PORT_H_

#include "MarineElement.h"
#include <queue>
#include <deque>
#include <memory>
#include <vector>

using std::vector;
class Freighter;
class Ship;

using std::weak_ptr;
using std::shared_ptr;
using std::queue;

class Port: public Marine_Element {
    
private:
    double containers;
    
    queue<Ship*> fuel_queue;
    static vector<weak_ptr<Port>> ports_list;
    
    Port(string name, int x, int y, double fuel);

public:
    shared_ptr<Port> create_port(string name, int x, int y, double fuel);
	~Port();
    
    void unload_ship (unsigned int amount);
    void load_ship (Freighter& fr);
    void fuel_request (Ship* ship);
    
    weak_ptr<Port> portAt(int x, int y)const;
    
    void go();

    //mostly for cruise ship.
    vector<weak_ptr<Port>> get_port_list(){return ports_list;};
};

#endif /* PORT_H_ */
