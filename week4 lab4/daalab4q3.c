#include <stdio.h>
#include <stdlib.h>

/* ---------- Merge Sort ---------- */

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* ---------- Binary Search ---------- */

int binarySearch(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/*
 * Check whether target index is already selected.
 * Since S is a set, all values are distinct.
 */
int isSelected(int selected[], int count, int targetIndex)
{
    for (int i = 0; i < count; i++)
    {
        if (selected[i] == targetIndex)
            return 1;
    }

    return 0;
}

/*
 * Generate combinations of k-1 elements.
 */
int findKSum(int S[], int n, int k, int T,
             int start, int depth, long long sum,
             int selected[])
{
    /*
     * We have selected k-1 elements.
     * Search for the required kth element.
     */
    if (depth == k - 1)
    {
        long long required = (long long)T - sum;

        int index = binarySearch(S, n, (int)required);

        if (index != -1 &&
            !isSelected(selected, k - 1, index))
        {
            printf("\nElements found:\n");

            for (int i = 0; i < k - 1; i++)
                printf("%d ", S[selected[i]]);

            printf("%d", S[index]);

            printf("\nSum = %d\n", T);

            return 1;
        }

        return 0;
    }

    /*
     * Generate combinations in increasing index order.
     */
    for (int i = start; i < n; i++)
    {
        selected[depth] = i;

        if (findKSum(S, n, k, T,
                     i + 1, depth + 1,
                     sum + S[i], selected))
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int n, k, T;

    printf("Enter number of elements n: ");
    scanf("%d", &n);

    int *S = malloc(n * sizeof(int));

    printf("Enter %d distinct integers:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &S[i]);

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    if (k < 2 || k > n)
    {
        printf("Invalid value of k.\n");
        free(S);
        return 0;
    }

    /* Sort S */
    mergeSort(S, 0, n - 1);

    printf("\nSorted set:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", S[i]);

    printf("\n");

    int *selected = malloc((k - 1) * sizeof(int));

    int found = findKSum(S, n, k, T,
                         0, 0, 0, selected);

    if (!found)
    {
        printf("\nNo %d elements add up to %d.\n", k, T);
    }

    free(selected);
    free(S);

    return 0;
}