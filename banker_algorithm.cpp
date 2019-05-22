// Banker's Algorithm 
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
  
    int max[5][4] = { { 4, 1, 1, 1},   //P0 
                      { 0, 2, 1, 2},   //P1 
                      { 4, 2, 1, 0},   //P2 
                      { 1, 1, 1, 1},   //P3 
                      { 2, 1, 1, 0} }; //P4 
  
    int avail[4] = { 0, 0, 0, 0 }; // Available Resources 
  
    int f[processes], ans[processes], ind = 0; 

    //vector f that will help to know if it was possible to distribute the resources. 
    //It is filled with zeros and if at the end of the redistribution process
    //it still has zero inside is because it was not possible to do the redistribution.
    for (k = 0; k < processes; k++) { 
        f[k] = 0; 
    }

    //what processes need to reach the maximum is precisely the difference between
    //the vector that defines the maximum values of resources that the processes can use
    //and the vector of resources that they already have allocated. 
    int need[processes][resources]; // vector with the values that the processes need to reach the maximum
    for (i = 0; i < processes; i++) { 
        for (j = 0; j < resources; j++) 
            need[i][j] = max[i][j] - alloc[i][j]; 
        }										 

    int y = 0; 
    for (k = 0; k < resources; k++) { 
        for (i = 0; i < processes; i++) { 
        	if (f[i] == 0) { 
                int flag = 0; 
                for (j = 0; j < resources; j++) {
                	//If the amount of resources required by the process
                	//is greater than the amount of resources available, redistribution will not be possible.
                    if (need[i][j] > avail[j]){ 
                    	flag = 1; 				
                    	break; 
                    }
                } 
  
                if (flag == 0) { 
                	//Here is stored redistribution order to be made so that all processes can use the available resources.
                    ans[ind++] = i;
                    //Here the resources will be released, because after using the resources this same process will release them.
                    for (y = 0; y < resources; y++) 
                        avail[y] += alloc[i][y]; 
                    f[i] = 1; 
                    		 
                } 
            } 
        } 
    }

  	int auxp = 1;
  	for (int i = 0; i < processes; i++){
  		if(f[i] == 0){
  			cout << "Redistribution was not possible" << endl;
  			auxp = 0;
  			break;
  		}
  		if(auxp == 1){
			cout << "The safe redistribution sequence is:" << endl; 
			for (i = 0; i < processes - 1; i++) 
				cout << "P" << ans[i] << " -> "; 
			cout << "P" << ans[i] << endl;

  		}
  	}

    return 0; 

    // This code is contributed by Deep Baldha (CandyZack)
    // base reference: https://www.geeksforgeeks.org/operating-system-bankers-algorithm/
} 