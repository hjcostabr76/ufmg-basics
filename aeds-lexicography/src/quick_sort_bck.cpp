// Quick sort in C++

#include <iostream>
using namespace std;

// function to swap_bck elements
void swap_bck(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to print the array
void printArray_bck(int array[], int size) {
  // cout << 
  for (int i = 0; i < 7; i++)
    cout << array[i] << " ";
  cout << endl;
}

// function to rearrange array (find the partition_bck point)
int partition_bck(int array[], const int low, const int high) {
	
  // select the rightmost element as pivot
  int pivot = array[high];
  printf("[part: 0] pivot: array[%d]: %d / low: array[%d]: %d\n", high, pivot, low, array[low]);
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      
      // if element smaller than pivot is found
      // swap_bck it with the greater element pointed by i
      i++;
      
      // swap_bck element at i with element at j
      swap_bck(&array[i], &array[j]);
      printf("[part: 1] (i:%d/j:%d) ", i, j);
      printArray_bck(array, high - low + 1);
    }
  }
  
  // swap_bck pivot with the greater element at i
  swap_bck(&array[i + 1], &array[high]);
  printf("[part: 2] (i:_/j:_) ");
  printArray_bck(array, high - low + 1);
  // cout << endl;
  
  // return the partition_bck point
  return (i + 1);
}

void quickSort_bck(int array[], const int low, const int high) {
  if (low < high) {
	  
	// find the pivot element such that
	// elements smaller than pivot are on left of pivot
	// elements greater than pivot are on righ of pivot

  printArray_bck(array, high - low + 1);
	int pivot = partition_bck(array, low, high);
  printArray_bck(array, high - low + 1);
  printf("pivot: '%d'\n", pivot);
  cout << endl;

  // printf("\npivot: array[%d]: %d", pivot, array[pivot]);

	// recursive call on the left of pivot
  printf("left...\n");
	quickSort_bck(array, low, pivot - 1);

  printf("right...\n");
	// recursive call on the right of pivot
	quickSort_bck(array, pivot + 1, high);
  printf("end...'\n");
  printArray_bck(array, high - low + 1);
  }
}
