#include <iostream>
using namespace std;
int main() 
{ 
    // P0, P1, P2, P3 are the Process names
    int processes, i, j, k, y = 0;
    processes = 4; 

     int alloc[4] = {   1,      //P0 
                        1,      //P1 
                        2,      //P2 
                        4   };  //P3 

    int max[4] = {      6,      //P0 
                        5,      //P1 
                        4,      //P2 
                        7   };  //P3
  
    int avail = 2;// Available Resources 

    int f[processes], ans[processes], ind = 0; 
    
    //vector f that will help to know if it was possible to distribute the resources. 
    //It is filled with zeros and if at the end of the redistribution process
    //it still has zero inside is because it was not possible to do the redistribution.
    for (k = 0; k < processes; k++) { 
        f[k] = 0; 
    }

    int need[processes];
     
    for (j = 0; j < processes; j++)
        need[j] = max[j] - alloc[j]; // vector with the values that the processes need to reach the maximum
        									
    for (k = 0; k < processes; k++){
      for (i = 0; i < processes; i++) { 
        if (f[i] == 0) { 
          int flag = 0;       
          //If the amount of resources required by the process
          //is greater than the amount of resources available, redistribution will not be possible.       
          if (need[i] > avail){ 
              flag = 1; 
          }
   
          if (flag == 0){
              //Here is stored redistribution order to be made so that all processes can use the available resources.               
              ans[ind++] = i;
              //Here the resources will be released, because after using the resources this same process will release them.        
              for (y = 0; y < processes; y++) 
                  avail += alloc[y]; 
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

} 