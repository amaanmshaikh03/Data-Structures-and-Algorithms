#include <cstdlib>
#include <iostream>
#include <fstream>


using namespace std;




/*Only modify this function*/
void insertionSortModified(int arr[],int size){
   int curr;
   int i, j;
   for(i=1;i<size;i++){
      curr=arr[i];
      for(j=i;j>0 && arr[j-1] > curr;j--){
         arr[j]=arr[j-1];
      }
      arr[j]=curr;
   }
}


/*performs the insertion sort algorithm on array from index
left to index right inclusive.  You don't need to change this function*/
void insertionSortStandard(int arr[], int size){
   int curr;
   int i, j;
   for(i=1;i<size;i++){
      curr=arr[i];
      for(j=i;j>0 && arr[j-1] > curr;j--){
         arr[j]=arr[j-1];
      }
      arr[j]=curr;
   }
}

