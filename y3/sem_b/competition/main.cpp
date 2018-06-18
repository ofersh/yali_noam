//
//  main.cpp
//  competition
//
//  Created by Noam Stolero on 14/05/2018.
//  Copyright © 2018 Noam Stolero. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>


using namespace std;



void read_lines(vector<string> &lines){
    string line = "";
    do{
        getline(cin, line);
         lines.push_back(line);
        //do something with the line..
    }while(line != "quit");
    
    
}

int main(){
    vector<string> lines;
    int n;
    cin >> n;
    read_lines(lines);
    
    for(string line : lines){
        reverse(line.begin(), line.end());
    }
}

