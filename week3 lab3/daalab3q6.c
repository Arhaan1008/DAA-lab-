#include <stdio.h>

void selectionSort(int A[], int n)
{
    int i, j, minIndex, temp;
    int comparisons = 0;

    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;

        /* Find the smallest element in A[i...n-1] */
        for (j = i + 1; j < n; j++)
        {
            comparisons++;

            if (A[j] < A[minIndex])
                minIndex = j;
        }

        /* Exchange A[i] and A[minIndex] */
        if (minIndex != i)
        {
            temp = A[i];
            A[i] = A[minIndex];
            A[minIndex] = temp;
        }
    }

    printf("\nNumber of comparisons = %d\n", comparisons);
}

void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("\nOriginal array:\n");
    printArray(A, n);

    selectionSort(A, n);

    printf("\nSorted array:\n");
    printArray(A, n);

    return 0;
}