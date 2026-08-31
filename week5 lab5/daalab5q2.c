#include <stdio.h>
#include <stdlib.h>

/* Partition function */
int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;
    int temp;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;

            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return i + 1;
}

/* Quickselect */
int quickSelect(int a[], int low, int high, int k)
{
    if (low == high)
        return a[low];

    int p = partition(a, low, high);

    if (k == p)
        return a[p];
    else if (k < p)
        return quickSelect(a, low, p - 1, k);
    else
        return quickSelect(a, p + 1, high, k);
}

int main()
{
    int n, k;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter K: ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid value of K.\n");
        free(a);
        return 0;
    }

    /* k-1 because array indexing starts from 0 */
    int result = quickSelect(a, 0, n - 1, k - 1);

    printf("%dth smallest element = %d\n", k, result);

    free(a);

    return 0;
}