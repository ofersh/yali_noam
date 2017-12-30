

#ifndef ELEMENTS_PORT_H_
#define ELEMENTS_PORT_H_

#include "MarineElement.h"
#include <queue>
#include <deque>
#include <vector>

using std::vector;
class Freighter;
class Civil_ship;

using std::shared_ptr;
using std::queue;

class Port: public Marine_Element {
    
private:

    double fuel_generate_rate;  //port fuel genrate rate.
    
    queue<Civil_ship*> fuel_queue;  // hold a queue of ship fuel request
    static vector<weak_ptr<Port>> ports_list;
    
    Port(string name,Point pos, double fuel, double fuel_generate );

public:
    static shared_ptr<Port> create_port(string name,Point pos, double fuel, double fuel_generate);
	
    ~Port()=default;
    
    void load_ship (Freighter& fr);
    void fuel_request (Civil_ship* ship);
    
    weak_ptr<Port> portAt(int x, int y)const;
    
    void go();
    void status()const;
    
    //mostly for cruise ship.
    static vector<weak_ptr<Port>> get_port_list();
};

#endif /* PORT_H_ */
