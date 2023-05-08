#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

void heapify(int arr[], int n, int node) {
	int max, left, right, temp;
	max = node;
	left = (2 * node) + 1;
	right = (2 * node) + 2;
	
	if (left < n && arr[left] > arr[max])
		max = left;
	if (right < n && arr[right] > arr[max])
		max = right;
	if (max != node) {
		temp = arr[node];
		arr[node] = arr[max];
		arr[max] = temp;
		heapify(arr, n, max);
	}
}
void heapSort(int arr[], int n) {
	int i, temp;
	
	for (i = n / 2; i >= 0; i--) {
		heapify(arr, n, i);
	}
	
	for (i = n - 1; i >= 0; i--) {
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		heapify(arr, i, 0);
	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
	int *left, *right;
	int leftSize, rightSize;
	int m;
	int i, j, k;
	
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

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	printf("dataSz: %d\n", dataSz);
	
	// fix bug where it would print garbage values since
	// some of the input files are less than 100 values long
	if (dataSz < 100) {
		for (i=0;i<dataSz;++i)
			printf("%d ",pData[i]);
		
		printf("\n\n");
		return;
	}
	
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
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
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