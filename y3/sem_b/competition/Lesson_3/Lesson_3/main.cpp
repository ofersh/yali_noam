//
//  main.cpp
//  Lesson_3
//
//  Created by Noam Stolero on 19/03/2018.
//  Copyright © 2018 Noam Stolero. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int max_index = 0;


int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int get_val(int matrix[60][60], int l_index, int r_index){
    int val = matrix[l_index][r_index];
    if (val == -1){
        for(int i=0; i<max_index && val!=-1; i++){
            val = matrix[l_index]
        }
    }
    
}

bool get_res(int matrix[60][60], int l_index, int r_index, int* l_value, int* r_value){
    int l, r;
    return false;
}

void update_matrix(int matrix[60][60], int l_index, int r_index, int l_val, int r_val){
    matrix[l_index][r_index] = l_val;
    matrix[r_index][l_index] = r_val;
}

void break_string(string s, vector<string>& names, int matrix[60][60]){
    string sign, r_name, l_name;
    stringstream ss(s);
    ss >> sign;
    if(sign == "!"){
        int l, r;
        int l_index, r_index;
        ss >> l >> l_name >> sign >> r >> r_name;
        vector<string>::iterator it;
        if( (it = find(names.begin(),names.end(),l_name)) != names.end()){
            l_index = it - names.begin();
        }
        else{
            l_index = names.size();
            names.push_back(l_name);
            max_index++;
        }
        
        if( (it = find(names.begin(),names.end(),r_name)) != names.end()){
            r_index = it - names.begin();
        }
        else{
            r_index = names.size();
            names.push_back(r_name);
            max_index++;
        }
        
        cout << l << l_index << sign << r << r_index << endl;
    }
    else{
        int r_index, l_index;
        int l_val, r_val;
        ss >> l_name >> sign >> r_name;
        l_index = find(names.begin(),names.end(),l_name) - names.begin();
        r_index = find(names.begin(),names.end(),r_name) - names.begin();
        if(!get_res(matrix, l_index, r_index, &l_val, &r_val)){
            cout << "? " << l_name << " = ? " << r_name << endl;
        }
        else{
            cout << l_val << " " << l_name << " = " << r_val << " " << r_name << endl;
        }
    }
    
}


void q2(){
    
    string line;
    vector<string> names;
    int matrix[60][60];
    while(true){
        getline(cin, line);
        if(line == ".")
            break;
        break_string(line, names, matrix);
    }
    
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    q2();
    return 0;
}
