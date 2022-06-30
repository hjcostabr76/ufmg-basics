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


void setPartition(int array[], const int low, const int high, int &partition) {
    
	// Set pivot in the median of 03 fashion
	const int first = array[low];
	const int median = array[(high - low) / 2 + low];
	const int last = array[high - 1];
    
	int pivot = 0;
	if ((median > first && median < last) || (median > last && median < first))
		pivot = median;
    else if ((last > first && last < median) || (last > median && last < first))
		pivot = last;
	else
		pivot = first;

	// Sort
	int i = low - 1;
	int j = high;

	while (true) {
        do  { j--; } while (array[j] > pivot);
        do  { i++; } while (array[i] < pivot);
        if  (i < j) swap(&array[i], &array[j]);
        else break;
    }

	partition = j + 1;
}


void sort(int array[], int start, int end) {
	if (end - start >= 2) {
		int pivot = 0;
		setPartition(array, start, end, pivot);
		sort(array, start, pivot);
		sort(array, pivot, end);
	}
}

void quickSort(int array[], const int low, const int high) {
	size = high - low;
	cout << endl << "before:" << endl;
	printArray(array);
	sort(array, low, high);
	cout << endl << "after:" << endl;
	printArray(array);
}