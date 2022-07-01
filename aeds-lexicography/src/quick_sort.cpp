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

void setPartition(int array[], const int low, const int high, int &partition) {
    
	// Set pivot in the median of 03 fashion
	// const int first = array[low];
	// const int median = array[(high - low) / 2 + low];
	// const int last = array[high - 1];
    
	int pivot = 0;
	// if ((median > first && median < last) || (median > last && median < first))
	// 	pivot = median;
    // else if ((last > first && last < median) || (last > median && last < first))
	// 	pivot = last;
	// else{
	// 	pivot = first;
	// }

	int foo = getMedianOfMPivot(array, 3, low, high, false);
	// if (foo != pivot) {
	// 	printf("\nPivot: expected x calculated -> '%d' x '%d'", pivot, foo);
	// 	printf("\n\tlow: '%d', high: '%d' | ", low, high);
	// 	printArray(array);
	// 	foo = getMedianOfMPivot(array, 3, low, high, true);
	// }

	pivot = foo;
	
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