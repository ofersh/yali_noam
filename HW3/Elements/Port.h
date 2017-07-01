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
#include <memory>
#include <map>

using std::map;
class Freighter;
class Ship;

using std::weak_ptr;
using std::queue;



class Port: public Marine_Element {
    

private:
    double containers;
    queue<weak_ptr<Ship>> fuel_queue;
    static map<coordinates,string> port_map; // monitor ports and coordinates.

    
    
public:
    
	Port();
	virtual ~Port();
    
    void unload_ship (Freighter& fr);
    void load_ship (Freighter& fr);
    void fuel_request (Ship& ship);
    string portAt(int x, int y)const;
    
    
    
    
};

#endif /* PORT_H_ */
