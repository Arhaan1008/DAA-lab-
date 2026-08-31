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

/* Partition */
int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

/* Quick Sort */
void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
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

    fp = fopen("quicksort_input.txt", "w");

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
    fp = fopen("quicksort_input.txt", "r");

    if (fp == NULL)
    {
        printf("\nUnable to open file.\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    /* Sort */
    quickSort(a, 0, n - 1);

    printf("\n\nSorted elements using Quick Sort:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    free(a);

    return 0;
}