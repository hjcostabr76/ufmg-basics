#include <iostream>

using namespace std;

int size = 0;
void printArray(int array[]) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}

// function to swap_bck elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int MedianOfThreePartition(int a[],int p, int r) {
    int x=a[p],y=a[(r-p)/2+p],z=a[r-1],i=p-1,j=r;
    if (y>x && y<z || y>z && y<x ) x=y;
    else if (z>x && z<y || z>y && z<x ) x=z;
    while (1) {
        do  {j--;} while (a[j] > x);
        do  {i++;} while (a[i] < x);
        if  (i < j) swap(&a[i],&a[j]);
        else return j+1;
    }
}


void sort(int a[],int start,int end) {
    int q;
    if (end-start<2) return;
    q=MedianOfThreePartition(a,start,end);
    sort(a,start,q);
    sort(a,q,end);
}

void quickSort(int array[], const int low, const int high) {
	size = high - low;
	cout << endl << "before:" << endl;
	printArray(array);
	sort(array, low, high);
	cout << endl << "after:" << endl;
	printArray(array);
}