/*
 * Tester.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */


#include "Elements/Cruiser.h"
#include "Elements/Freighter.h"
#include <memory.h>

int main()
{
    shared_ptr<Ship> sfr {new Freighter{ "yali" ,Point(2,3),100, 7}};
    shared_ptr<Ship> scr{new Cruiser{"noam",Point(1,2),10,12}};
    
    
    sfr->status();
    scr->status();
    
    shared_ptr<Cruiser> rcr=dynamic_pointer_cast<Cruiser>(scr);
    shared_ptr<Civil_ship> rcs=dynamic_pointer_cast<Civil_ship>(sfr);
    
    rcr->attack(rcs);
    
    rcs->status();
    rcr->status();
    
}
