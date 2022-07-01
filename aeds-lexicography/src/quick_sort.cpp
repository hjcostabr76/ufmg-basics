#include <iostream>

using namespace std;

int size = 0;
void printArray(int array[]) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int getMedianOfMPivot(int array[], const int m, const int low, const int high, const bool dbg) {

	const int padding = (high - low) / (m - 1);
	// printf("\n m: '%d'; high: '%d'; low: '%d'; padding: '%d';", m, high, low, padding);
	// if (!padding)
	// 	return high;

	int *edgePoints = (int *)malloc(m * sizeof(int));
	int aux = 0;
	for (int i = low; i < high - 1; i += padding) {
		if (dbg) printf("\n aux: '%d'; ", aux);
		edgePoints[aux++] = i;
	}
	edgePoints[aux] = high - 1;


	if (dbg) {
		for (int i = 0; i < m; i++)
			printf("\n edgePoints[%d] = '%d' --> '%d'", i, edgePoints[i], array[edgePoints[i]]);
	}

	int *diffs = (int *)malloc(m * sizeof(int));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i != j)
				diffs[i] += array[edgePoints[i]] - array[edgePoints[j]];
		}
	}

	if (dbg) {
		for (int i = 0; i < m; i++)
			printf("\nDIFFs[%d]: '%d'", i, diffs[i]);
	}

	int argMin = 0;
	int min = abs(diffs[0]);
	for (int i = 1; i < m; i++) {
		const int aux = abs(diffs[i]);
		if (aux < min) {
			min = aux;
			argMin = i;
		}
	}

	const int idxPivot = edgePoints[argMin];
	const int pivot = array[idxPivot];

	free(edgePoints);
	free(diffs);
	return pivot;
}

void setPartition(int array[], const int low, const int high, int &partition, const int m) {
    
	int i = low - 1;
	int j = high;
	int pivot = getMedianOfMPivot(array, m, low, high, false);

	while (true) {
        do  { j--; } while (array[j] > pivot);
        do  { i++; } while (array[i] < pivot);
        if  (i < j) swap(&array[i], &array[j]);
        else break;
    }

	partition = j + 1;
}

void runQuickSort(int array[], const int start, const int end, const int m) {
	if (end - start >= 2) {
		int pivot = 0;
		setPartition(array, start, end, pivot, m);
		runQuickSort(array, start, pivot, m);
		runQuickSort(array, pivot, end, m);
	}
}

void runSelectionSort(int array[], int n) {
    
	int i = 0;
	int j = 0;
	int idxMin = 0;
  
	// Move boundary of unsorted sub array
    for (; i < n - 1; i++)  {
        
		// Find smaller in this sub array
		idxMin = i; 
        for (j = i + 1; j < n; j++) {
			if (array[j] < array[idxMin]) 
				idxMin = j;
		}
		swap(&array[idxMin], &array[i]); 
    } 
} 

void selectionSort(int array[], int n) {
	size = n;
	cout << endl << "before:" << endl;
	printArray(array);
	runSelectionSort(array, n);
	cout << endl << "after:" << endl;
	printArray(array);
}

void quickSort(int array[], const int low, const int high, const int m) {
	size = high - low;
	cout << endl << "before:" << endl;
	printArray(array);
	runQuickSort(array, low, high, m);
	cout << endl << "after:" << endl;
	printArray(array);
}
