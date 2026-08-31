#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Swap two elements */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Heapify */
void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    /* Check left child */
    if (left < n && a[left] > a[largest])
        largest = left;

    /* Check right child */
    if (right < n && a[right] > a[largest])
        largest = right;

    /* If largest is not root */
    if (largest != i)
    {
        swap(&a[i], &a[largest]);

        heapify(a, n, largest);
    }
}

/* Heap Sort */
void heapSort(int a[], int n)
{
    /* Build Max Heap */
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    /* Extract elements from heap */
    for (int i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);

        heapify(a, i, 0);
    }
}

int main()
{
    FILE *fp;
    int n;

    printf("Enter number of random elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    /* Generate random numbers */
    srand(time(NULL));

    fp = fopen("heapsort_input.txt", "w");

    if (fp == NULL)
    {
        printf("Unable to create file.\n");
        free(a);
        return 1;
    }

    printf("\nRandom elements:\n");

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
        fprintf(fp, "%d ", a[i]);
        printf("%d ", a[i]);
    }

    fclose(fp);

    /* Read elements from file */
    fp = fopen("heapsort_input.txt", "r");

    if (fp == NULL)
    {
        printf("\nUnable to open file.\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    /* Heap Sort */
    heapSort(a, n);

    printf("\n\nSorted elements using Heap Sort:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    free(a);

    return 0;
}