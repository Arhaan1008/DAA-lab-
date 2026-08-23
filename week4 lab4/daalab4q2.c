#include <stdio.h>
#include <stdlib.h>

/* Merge two sorted portions */
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

    int i = 0;
    int j = 0;
    int k = left;

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

/* Merge Sort */
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

/* Binary Search */
int binarySearch(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return 1;

        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

int main()
{
    int n, x;

    printf("Enter size of each set: ");
    scanf("%d", &n);

    int *S1 = malloc(n * sizeof(int));
    int *S2 = malloc(n * sizeof(int));

    printf("Enter elements of S1:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S1[i]);

    printf("Enter elements of S2:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S2[i]);

    printf("Enter target x: ");
    scanf("%d", &x);

    /* Sort S1 */
    mergeSort(S1, 0, n - 1);

    printf("\nSorted S1:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", S1[i]);

    printf("\n");

    /* Search for x - b */
    int found = 0;
    int first = 0, second = 0;

    for (int i = 0; i < n; i++)
    {
        int target = x - S2[i];

        if (binarySearch(S1, n, target))
        {
            found = 1;
            first = target;
            second = S2[i];
            break;
        }
    }

    if (found)
    {
        printf("\nPair found:\n");
        printf("%d + %d = %d\n", first, second, x);
    }
    else
    {
        printf("\nNo pair exists whose sum is %d.\n", x);
    }

    free(S1);
    free(S2);

    return 0;
}