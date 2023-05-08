#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	int *left, *right;
	int leftSize, rightSize;
	int m;
	int i, j, k;
	
	extraMemoryAllocated += (sizeof(int) * 6) + (sizeof(int *) * 2) + (sizeof(int *)) + (sizeof(int) * 2);
	if (l >= r) {
		return;
	}
	
	m = (l + r) / 2;

	mergeSort(pData, l, m);
	mergeSort(pData, m + 1, r);
	
	leftSize = m - l + 1;
	rightSize = r - m;

	left = (int *) malloc(sizeof(int) * leftSize);
	right = (int *) malloc(sizeof(int) * rightSize);
	
	extraMemoryAllocated += (sizeof(int) * leftSize) + (sizeof(int) * rightSize);
	
	i = 0;
	j = 0;
	
	while (i < leftSize) {
		left[i] = pData[l + i];
		i++;
	}
	
	while (j < rightSize) {
		right[j] = pData[m + 1 + j];
		j++;
	}
	
	i = 0;
	j = 0;
	k = l;
	
	while (i < leftSize && j < rightSize) {
		if (left[i] <= right[j]) {
			pData[k] = left[i];
			i++;
		}
		else {
			pData[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < leftSize) {
		pData[k] = left[i];
		i++;
		k++;
	}
	while (j < rightSize) {
		pData[k] = right[j];
		j++;
		k++;
	}
	
	free(left);
	free(right);
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, temp;
	extraMemoryAllocated += sizeof(int) * 4 + sizeof(int *);
	for (i = 1; i < n; i++) {
		//j = i - 1;
		temp = pData[i];
		for (j = i - 1; j >= 0; j--) {
			if (pData[j] > temp) {
				pData[j + 1] = pData[j];
			}
			else {
				break;
			}
		}
		pData[j + 1] = temp;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	// bubble sort: the largest numbers "bubble" up to the top,
	// and then we keep swapping until eventually, we swapped everything
	// so that its sorted! (unfortunately has a pretty bad runtime)
	int i, j, temp;
	extraMemoryAllocated += sizeof(int) * 4 + sizeof(int *);
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (pData[j] > pData[j + 1]) { // check element and whats in front of it, and if the previous is larger than the next,
				temp = pData[j + 1]; // store the next element into temporary variable
				pData[j + 1] = pData[j]; 
				pData[j] = temp;
			}
			
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i, j, temp;
	int min = 0; // min is an index
	extraMemoryAllocated += sizeof(int) * 5 + sizeof(int *);
	for (i = 0; i < n; i++) {
		min = i; /// make sure to reset min to the index of i, so that we properly can compare minimums
		for (j = i; j < n; j++) { // we need to start at the index of i everytime for j since we know that as we keep finding the min, the start will be sorted
			if (pData[j] < pData[min]) { // if we find something thats less than what we thought was the min...
				min = j; // then we have a new min
			}
		}
		temp = pData[i]; // use temp variable to swap
		pData[i] = pData[min]; // at the end, we can definitively say we found the first pass of min, so the index at i has its min
		pData[min] = temp; // finish swapping and put value into old min index
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		int i = 0;
		int tempNum;
		
		fscanf(inFile,"%d\n",&dataSz); // first line is how many numbers is in the file
		printf("dataSz = %d\n", dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz); // malloc a space in mem an integer array with the size of dataSz
		
		// Implement parse data block
		for (i = 0; i < dataSz; i++) {
			fscanf(inFile, " %d", &tempNum); // scan number in from file into a temporary integer variable
			(*ppData)[i] = tempNum; // first, dereference ppData itself to access the underlying array behind it, then access the i-th element in the array and = to tempNum
			//printf("ppData[%d] = %d\n", i, (*ppData)[i]); // debug printf statement(s)
			//fflush(stdout);
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}