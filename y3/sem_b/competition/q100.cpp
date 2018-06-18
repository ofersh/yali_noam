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
#include <algorithm>

using namespace std;



void read_lines(vector<string> &lines){
    string line;
    while (true){
        getline(cin, line);
        if (line == "quit")
            return;
        lines.push_back(line);
    }
}


void encrypt(string &s, int n){
    int m = s.size()-1;
    vector<int> skip;
    for( int i=0; i<m+1; i++){
        
        if (s[i] >'Z'){
            char asci = (s[i]-'a');
            char res = (asci + n)%26;
            char newChar = 'a' + res;
            s[i] = newChar;
        }
    }
    
    for( int i=0; i<m+1; i++){
        if (s[i] == ',' ||  s[i] ==  '.'){
            if (find(skip.begin(), skip.end(), i) != skip.end())
                continue;
            swap(s[i], s[m-i] );
            skip.push_back(max(i, m-i));
            
        }
    }

    
}



int main(){
    vector<string> lines;
    int n;
    cin >> n;
    read_lines(lines);
    
    for(string line : lines){
        encrypt(line, n);
        cout<<line<<endl;
    }
}

