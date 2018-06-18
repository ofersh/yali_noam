


/* Printing With copy */
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
copy(vector.begin(), vector.end(), ostream_iterator<int>(cout, "\n"));
/* Printing With copy */



/* Read till EOF */
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

void read_till_EOF(vector<int> &v){
    
    int n;
    string line;
    
    while (getline(cin, line)){
        stringstream ss(line);
        ss>>n;
        v.push_back(n);
    }
}
/* Read till EOF */





