#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* =========================================================
   Utility Function: Print Array
   ========================================================= */
void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");
}

/* =========================================================
   (i) Find Maximum Element
   Time Complexity: O(n)
   Space Complexity: O(1)
   ========================================================= */
int findMaximum(int A[], int n)
{
    int max = A[0];

    for (int i = 1; i < n; i++)
    {
        if (A[i] > max)
            max = A[i];
    }

    return max;
}

/* =========================================================
   (ii) Find First and Second Largest Elements
   Time Complexity: O(n)
   Space Complexity: O(1)
   ========================================================= */
void findFirstSecondLargest(int A[], int n,
                            int *largest,
                            int *secondLargest)
{
    if (A[0] > A[1])
    {
        *largest = A[0];
        *secondLargest = A[1];
    }
    else
    {
        *largest = A[1];
        *secondLargest = A[0];
    }

    for (int i = 2; i < n; i++)
    {
        if (A[i] > *largest)
        {
            *secondLargest = *largest;
            *largest = A[i];
        }
        else if (A[i] > *secondLargest && A[i] != *largest)
        {
            *secondLargest = A[i];
        }
    }
}

/* =========================================================
   (iii) Find Mean
   Time Complexity: O(n)
   Space Complexity: O(1)
   ========================================================= */
double findMean(int A[], int n)
{
    long long sum = 0;

    for (int i = 0; i < n; i++)
        sum += A[i];

    return (double)sum / n;
}

/* =========================================================
   Merge Sort
   Used for finding Median
   Time Complexity: O(n log n)
   ========================================================= */

void merge(int A[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = A[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }

    while (i < n1)
        A[k++] = L[i++];

    while (j < n2)
        A[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int A[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);

        merge(A, left, mid, right);
    }
}

/* =========================================================
   (iv) Find Median
   Time Complexity: O(n log n)
   Space Complexity: O(n) due to Merge Sort
   ========================================================= */
double findMedian(int A[], int n)
{
    mergeSort(A, 0, n - 1);

    if (n % 2 != 0)
    {
        return A[n / 2];
    }
    else
    {
        return ((double)A[n / 2 - 1] +
                A[n / 2]) / 2.0;
    }
}

/* =========================================================
   (v) Find Standard Deviation
   Time Complexity: O(n)
   Space Complexity: O(1)
   ========================================================= */
double findStandardDeviation(int A[], int n)
{
    double mean = findMean(A, n);
    double sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        double difference = A[i] - mean;
        sum += difference * difference;
    }

    return sqrt(sum / n);
}

/* =========================================================
   (vi) Find Mode
   Simple array-only method
   Time Complexity: O(n^2)
   Space Complexity: O(1)
   ========================================================= */
int findMode(int A[], int n)
{
    int mode = A[0];
    int maxCount = 0;

    for (int i = 0; i < n; i++)
    {
        int count = 0;

        for (int j = 0; j < n; j++)
        {
            if (A[i] == A[j])
                count++;
        }

        if (count > maxCount)
        {
            maxCount = count;
            mode = A[i];
        }
    }

    return mode;
}

/* =========================================================
   (vii) Remove All Duplicates
   Removes duplicate values in-place.
   Time Complexity: O(n^2)
   Space Complexity: O(1)
   ========================================================= */
int removeDuplicates(int A[], int n)
{
    int newSize = 0;

    for (int i = 0; i < n; i++)
    {
        int duplicate = 0;

        for (int j = 0; j < newSize; j++)
        {
            if (A[i] == A[j])
            {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
        {
            A[newSize] = A[i];
            newSize++;
        }
    }

    return newSize;
}

/* =========================================================
   (viii) Reverse Array
   Time Complexity: O(n)
   Space Complexity: O(1)
   ========================================================= */
void reverseArray(int A[], int n)
{
    int left = 0;
    int right = n - 1;

    while (left < right)
    {
        int temp = A[left];
        A[left] = A[right];
        A[right] = temp;

        left++;
        right--;
    }
}

/* =========================================================
   (ix) Partition Array with Respect to Pivot

   Required arrangement:

   Elements >= pivot | Elements < pivot

   Time Complexity: O(n)
   Space Complexity: O(1)
   ========================================================= */
void partitionArray(int A[], int n, int pivot)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        while (left <= right && A[left] >= pivot)
            left++;

        while (left <= right && A[right] < pivot)
            right--;

        if (left < right)
        {
            int temp = A[left];
            A[left] = A[right];
            A[right] = temp;

            left++;
            right--;
        }
    }
}

/* =========================================================
   Main Function
   ========================================================= */
int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("Please enter at least 2 elements.\n");
        return 1;
    }

    int *A = (int *)malloc(n * sizeof(int));

    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* -----------------------------------------------------
       Input Array
       ----------------------------------------------------- */
    printf("Enter %d unsorted integer elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("\nOriginal Array:\n");
    printArray(A, n);

    /* -----------------------------------------------------
       (i) Maximum
       ----------------------------------------------------- */
    printf("\n(i) Maximum Element = %d\n",
           findMaximum(A, n));

    /* -----------------------------------------------------
       (ii) First and Second Largest
       ----------------------------------------------------- */
    int largest, secondLargest;

    findFirstSecondLargest(A, n,
                           &largest,
                           &secondLargest);

    printf("(ii) Largest Element = %d\n", largest);
    printf("     Second Largest Element = %d\n",
           secondLargest);

    /* -----------------------------------------------------
       (iii) Mean
       ----------------------------------------------------- */
    printf("\n(iii) Mean = %.2lf\n",
           findMean(A, n));

    /* -----------------------------------------------------
       (iv) Median
       Make a copy because median sorts the array.
       ----------------------------------------------------- */
    int *B = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        B[i] = A[i];

    double median = findMedian(B, n);

    printf("\n(iv) Median = %.2lf\n", median);

    printf("     Sorted Array:\n");
    printArray(B, n);

    free(B);

    /* -----------------------------------------------------
       (v) Standard Deviation
       ----------------------------------------------------- */
    printf("\n(v) Standard Deviation = %.4lf\n",
           findStandardDeviation(A, n));

    /* -----------------------------------------------------
       (vi) Mode
       ----------------------------------------------------- */
    printf("\n(vi) Mode = %d\n",
           findMode(A, n));

    /* -----------------------------------------------------
       (vii) Remove Duplicates
       ----------------------------------------------------- */
    int *C = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        C[i] = A[i];

    int newSize = removeDuplicates(C, n);

    printf("\n(vii) Array after removing duplicates:\n");
    printArray(C, newSize);

    free(C);

    /* -----------------------------------------------------
       (viii) Reverse Array
       ----------------------------------------------------- */
    int *D = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        D[i] = A[i];

    reverseArray(D, n);

    printf("\n(viii) Reversed Array:\n");
    printArray(D, n);

    free(D);

    /* -----------------------------------------------------
       (ix) Partition
       Use the middle element as the pivot.
       ----------------------------------------------------- */
    int *E = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        E[i] = A[i];

    int pivot = A[n / 2];

    partitionArray(E, n, pivot);

    printf("\n(ix) Pivot = %d\n", pivot);

    printf("Partitioned Array:\n");
    printArray(E, n);

    free(E);

    /* -----------------------------------------------------
       Free Original Array
       ----------------------------------------------------- */
    free(A);

    return 0;
}