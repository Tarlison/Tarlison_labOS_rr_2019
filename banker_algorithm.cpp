// Banker's Algorithm 
#include <stdio.h>
#include <iostream>
using namespace std;
int main() 
{ 
    // P0, P1, P2, P3, P4 are the Process names
  
    int processes, resources, i, j, k; 
    processes = 5; // Number of processes 
    resources = 4; // Number of resources 
    int alloc[5][4] = { { 3, 0, 1, 1},   //P0     
                        { 0, 1, 0, 0},   //P1 
                        { 1, 1, 1, 0},   //P2 
                        { 1, 1, 0, 1},   //P3 
                        { 0, 0, 0, 0} }; //P4 
  
    int max[5][4] = { { 1, 1, 0, 0},   //P0 
                      { 0, 1, 1, 2},   //P1 
                      { 3, 1, 0, 0},   //P2 
                      { 0, 0, 1, 0},   //P3 
                      { 2, 1, 1, 0} }; //P4 
  
    int avail[4] = { 1, 0, 2, 0 }; // Available Resources 
  
    int f[processes], ans[processes], ind = 0; 
    for (k = 0; k < processes; k++) { 
        f[k] = 0; 
    } 
    int need[processes][resources]; 
    for (i = 0; i < processes; i++) { 
        for (j = 0; j < resources; j++) 
            need[i][j] = max[i][j] - alloc[i][j]; 
    } 
    int y = 0; 
    for (k = 0; k < 5; k++) { 
        for (i = 0; i < processes; i++) { 
            if (f[i] == 0) { 
  
                int flag = 0; 
                for (j = 0; j < resources; j++) { 
                    if (need[i][j] > avail[j]) 
                        flag = 1; 
                    break; 
                } 
  
                if (flag == 0) { 
                    ans[ind++] = i; 
                    for (y = 0; y < resources; y++) 
                        avail[y] += alloc[i][y]; 
                    f[i] = 1; 
                } 
            } 
        } 
    } 
  
    cout << "Following is the SAFE Sequence" << endl; 
    for (i = 0; i < processes - 1; i++) 
        cout << "P" << ans[i] << " -> "; 
    cout << "P" << ans[i] << endl;
  
    return (0); 
  
    // This code is contributed by Deep Baldha (CandyZack) 
} 