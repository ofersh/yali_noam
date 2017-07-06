/* Main module, which your project must use as-is. */
#include "MVC/Controller.h"
#include <iostream>
using namespace std;

// The main function creates the Controller object, then invokes run().
int main (int argc,const char* argv[]) {
  // Set output to show two decimal places
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);

    if (argc!=2)
    {
        cerr<<"need pne argument."<<endl;
        exit(1);
    }
	Controller controller(argv[1]);
	controller.run();
	
	return 0;
}
