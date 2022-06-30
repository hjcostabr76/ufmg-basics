#include <iostream>

using namespace std;

int size = 0;
void printArray(int array[]) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}

// void swap(int &a, int &b) {
// 	int t = a;
// 	a = b;
// 	b = t;
// }

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

/** Rearrange & set partition point (next pivot). */
void partition(int array[], const int low, const int high, int* partitionPoint) {

	if (array == NULL || partitionPoint == NULL)
		return;
	
	int j = low;
	int i = low - 1; // Point to greater element
  	int pivot = array[high]; // Rightmost element

	for (j = low; j < high; j++) {
		int &current = array[j];
		if (current <= pivot) {
			int &greatest = array[++i];
			swap(greatest, current);
		}
	}

	*partitionPoint = (i + 1);
	swap(array[*partitionPoint], array[high]);
}

void sort(int array[], const int low, const int high) {
	if (low < high) {
		int pivot = 0; // Set pivot (who's smaller goes left / who's greater goes right)
		printf("\npivot: '%d'\n", pivot);
		partition(array, low, high, &pivot);
		sort(array, low, pivot - 1);	// Rearrange before pivot
		sort(array, pivot + 1, high);	// Rearrange after pivot
	}
}

void quickSort(int array[], const int low, const int high) {
	size = high - low + 1;
	cout << endl << "before:" << endl;
	printArray(array);
	sort(array, low, high);
	cout << endl << "after:" << endl;
	printArray(array);
}
