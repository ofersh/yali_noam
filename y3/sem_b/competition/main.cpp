
#include <iterator>
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

using vect_it = vector<int>::iterator;

void print_post(vect_it begin, vect_it end){

    if ( begin >= end ){
        cout<<*begin<<endl;        
        return;
    } 

    vect_it left_end = end -1  ;
    for (vect_it seeker=begin; seeker!= end ; seeker ++){
        if (*seeker > *begin){
            left_end = seeker -1  ;
        }
    }    
    
    if (left_end != begin + 1){
        print_post(begin+1, left_end);        
    }

    if (left_end != end){
        print_post(left_end, end);
    }
    cout<<*begin<<endl;
}


int main(){
    vector<int> preorder;
    read_till_EOF(preorder);
    cout<<endl<<endl;
    print_post(preorder.begin(), preorder.end());    
}