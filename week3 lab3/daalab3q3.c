#include <stdio.h>

typedef struct
{
    int min;
    int max;
} MinMax;

int comparisons = 0;

MinMax findMinMax(int arr[], int low, int high)
{
    MinMax result;
    MinMax left;
    MinMax right;

    /* Case 1: Only one element */
    if (low == high)
    {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    /* Case 2: Two elements */
    if (high == low + 1)
    {
        comparisons++;

        if (arr[low] < arr[high])
        {
            result.min = arr[low];
            result.max = arr[high];
        }
        else
        {
            result.min = arr[high];
            result.max = arr[low];
        }

        return result;
    }

    /* Divide */
    int mid = low + (high - low) / 2;

    /* Conquer */
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    /* Combine: minimum */
    comparisons++;
    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    /* Combine: maximum */
    comparisons++;
    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    return result;
}

int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    MinMax result = findMinMax(arr, 0, n - 1);

    printf("\nMinimum element = %d\n", result.min);
    printf("Maximum element = %d\n", result.max);
    printf("Number of comparisons = %d\n", comparisons);

    printf("3n/2 = %.0f\n", 1.5 * n);

    if (comparisons <= 1.5 * n)
        printf("Comparison bound satisfied: comparisons <= 3n/2\n");
    else
        printf("Comparison bound exceeded.\n");

    return 0;
}