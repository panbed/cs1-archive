#include <stdio.h>
#include <stdlib.h>

int search(int numbers[], int low, int high, int value) 
{
	if (numbers == NULL)
		return -1;
	// create mid variable, which is ((high - low) / 2) + low
	// (we need the "+ low" at the end because if not, then the low will just become 0
	int mid = ((high - low) / 2) + low;
	
	if (low == high) // base case: if low is equal to high, then we didn't find a match, so return -1
		return -1;
	
	// if the middle is equal to value, then we found the search index
	// so return mid, which holds the index of the element
	if (numbers[mid] == value)
		return mid;
	
	// if the value of mid is greater than the search value,
	// then we recall the search function, now with 
	// the highest index being equal to the mid - 1
	else if (numbers[mid] > value)
		return search(numbers, low, mid - 1, value);
	
	// on the other hand, if the value of mid is less than the value,
	// we want to call search again, but this time replace the low with the index of mid
	else if (numbers[mid] < value)
		return search(numbers, mid + 1, high, value);

}

void printArray(int numbers[], int sz)
{
	int i;
	printf("Number array : ");
	for (i = 0;i<sz;++i)
	{
		printf("%d ",numbers[i]);
	}
	printf("\n");
}

int main(void)
{
	int i, numInputs;
	char* str;
	float average;
	int value;
	int index;
	int* numArray = NULL;
	int countOfNums;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &countOfNums);
		numArray = (int *) malloc(countOfNums * sizeof(int));
		average = 0;
		for (i = 0; i < countOfNums; i++)
		{
			fscanf(inFile," %d", &value);
			numArray[i] = value;
			average += numArray[i];
		}

		printArray(numArray, countOfNums);
		value = average / countOfNums;
		index = search(numArray, 0, countOfNums - 1, value);
		if (index >= 0)
		{
			printf("Item %d exists in the number array at index %d!\n",value, index);
		}
		else
		{
			printf("Item %d does not exist in the number array!\n", value);
		}

		free(numArray);
	}

	fclose(inFile);
}