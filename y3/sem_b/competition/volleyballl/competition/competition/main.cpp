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

using namespace std;

enum STATS{C, H, K, E, B, D};
using playersMap = map<int, vector<int>>;

const int SIZE = 6;



void readStats(playersMap & spMap){
    char stat;
    cin>>stat;
    switch (stat) {
        case 'C':
            int pNumber;
            int n;
            cin >> n;
            for (int i=0; i<n; i++) {
                cin >> pNumber;
                spMap.find(<#const _K2 &__k#>)
                
            }
            break;
            
        default:
            break;
    }
    
}

int main(int argc, const char * argv[]) {
    playersMap players_stats;
    
    
    
    
    return 0;
}
