//
//  main_108.cpp
//  competition
//
//  Created by Noam Stolero on 18/06/2018.
//  Copyright © 2018 Noam Stolero. All rights reserved.
//


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <math.h>

using namespace std;

void read_lines(vector<string> &lines){
    string line;
    while (true){
        getline(cin, line);
        if (line == "0 0")
            return;
        lines.push_back(line);
    }
}

int main(){
    
    while (true){
        int k, n;
        cin>>n>>k;
        if (n==0 && k==0)
            break;
        vector<int> numbers(k);
        set<int> diffs;
        for (int i=0; i<k; i++){
            cin>>numbers[i];
        }
        for(int i=0; i<k; i++){
            for(int j=i; j<k; j++){
                diffs.insert(abs(numbers[i] - numbers[j]));
            }
        }
        
        if (diffs.size() == n+1)
            cout<<'Y'<<endl;
        else
            cout<<'N'<<endl;
    }
}




