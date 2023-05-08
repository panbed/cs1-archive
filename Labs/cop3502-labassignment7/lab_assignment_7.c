#include <stdio.h>

// bubblesort implementation
void bubbleSort(int *numbers, int size)
{
	int i, j, temp, swaps;
	for (i = 0; i < size - 1; i++) {
        swaps = 0;
        printf("Iteration value: %d\t", i);
		for (j = 0; j < size - i - 1; j++) {
			if (numbers[j] > numbers[j + 1]) {
                //printf("swapping...\n");
				temp = numbers[j + 1];
				numbers[j + 1] = numbers[j]; 
				numbers[j] = temp;
                swaps++;
                //printArray(numbers, size);
			}
		}
        printf("Total swaps needed: %d\n", swaps);
	}
}

void printArray(int *numbers, int size) {
    printf("[");
    for (int i = 0; i < 9; i++) {
        (i != size - 1 ? printf(" %d |", numbers[i]) : printf(" %d ]\n", numbers[i]));
    }
    printf("\n");
}

int main(void) {
    int numberArray[9] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    printf("Unsorted Array: \n");
    printArray(numberArray, 9);

    bubbleSort(numberArray, 9);

    printf("\nSorted Array: \n");
    printArray(numberArray, 9);
}