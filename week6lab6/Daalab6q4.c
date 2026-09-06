#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =========================================================
   Global statistics
   ========================================================= */

long long reversalCount = 0;
long long reversalCost = 0;

/* =========================================================
   Reverse A[left ... right]

   Cost = right - left + 1

   Time Complexity of one reversal:
       O(length)

   ========================================================= */

void reverseRange(int A[], int left, int right)
{
    if (left >= right)
        return;

    int length = right - left + 1;

    reversalCount++;
    reversalCost += length;

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
   Reverse three consecutive blocks:

       X Y

   into:

       Y X

   using:

       reverse(X)
       reverse(Y)
       reverse(XY)

   If:
       X = [left ... mid]
       Y = [mid+1 ... right]

   then result is:

       Y X

   ========================================================= */

void swapBlocks(int A[], int left, int mid, int right)
{
    reverseRange(A, left, mid);
    reverseRange(A, mid + 1, right);
    reverseRange(A, left, right);
}

/* =========================================================
   Binary Search

   Find first position in A[low ... high] whose value
   is >= key.

   Used during merge.

   Time Complexity:
       O(log n)
   ========================================================= */

int lowerBound(int A[], int low, int high, int key)
{
    int left = low;
    int right = high + 1;

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        if (A[mid] < key)
            left = mid + 1;
        else
            right = mid;
    }

    return left;
}

/* =========================================================
   Reversal-based Merge

   A[left ... mid] and A[mid+1 ... right] are already
   sorted.

   We recursively divide the merge problem and use
   reversals to exchange blocks.

   ========================================================= */

void reversalMerge(int A[], int left, int mid, int right)
{
    /* Base cases */

    if (left > mid || mid + 1 > right)
        return;

    if (A[mid] <= A[mid + 1])
        return;

    if (right - left == 1)
    {
        if (A[left] > A[right])
        {
            reverseRange(A, left, right);
        }

        return;
    }

    /*
       Lengths of the two sorted sequences.
    */

    int n1 = mid - left + 1;
    int n2 = right - mid;

    /*
       If left sequence is larger, split it.
    */

    if (n1 >= n2)
    {
        int firstCut = left + n1 / 2;

        int secondCut =
            lowerBound(A,
                       mid + 1,
                       right,
                       A[firstCut]);

        /*
           We now have:

           [ left ... firstCut-1 ]
           [ firstCut ... mid ]
           [ mid+1 ... secondCut-1 ]
           [ secondCut ... right ]

           We need to exchange:

           A[firstCut ... mid]

           with

           A[mid+1 ... secondCut-1]
        */

        int newMid =
            firstCut +
            (secondCut - (mid + 1)) - 1;

        if (firstCut <= mid &&
            mid + 1 <= secondCut - 1)
        {
            swapBlocks(A,
                       firstCut,
                       mid,
                       secondCut - 1);
        }

        /*
           Recursively merge left part.
        */

        reversalMerge(A,
                      left,
                      firstCut - 1,
                      newMid);

        /*
           Recursively merge right part.
        */

        reversalMerge(A,
                      newMid,
                      secondCut - 1,
                      right);
    }

    /*
       Right sequence is larger.
    */

    else
    {
        int secondCut =
            mid + 1 + n2 / 2;

        int firstCut =
            lowerBound(A,
                       left,
                       mid,
                       A[secondCut]);

        /*
           Exchange:

           A[firstCut ... mid]

           with

           A[mid+1 ... secondCut-1]
        */

        int newMid =
            firstCut +
            (secondCut - (mid + 1)) - 1;

        if (firstCut <= mid &&
            mid + 1 <= secondCut - 1)
        {
            swapBlocks(A,
                       firstCut,
                       mid,
                       secondCut - 1);
        }

        /*
           Recursively merge left part.
        */

        reversalMerge(A,
                      left,
                      firstCut - 1,
                      newMid);

        /*
           Recursively merge right part.
        */

        reversalMerge(A,
                      newMid,
                      secondCut - 1,
                      right);
    }
}

/* =========================================================
   Reversal Merge Sort

   Time complexity:

       T(n) = 2T(n/2) + O(n log n)

       T(n) = O(n log^2 n)

   ========================================================= */

void reversalMergeSort(int A[], int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    /* Sort left half */
    reversalMergeSort(A, left, mid);

    /* Sort right half */
    reversalMergeSort(A, mid + 1, right);

    /* Merge */
    reversalMerge(A, left, mid, right);
}

/* =========================================================
   Check whether array is sorted
   ========================================================= */

int isSorted(int A[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (A[i - 1] > A[i])
            return 0;
    }

    return 1;
}

/* =========================================================
   Print array
   ========================================================= */

void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");
}

/* =========================================================
   Main
   ========================================================= */

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid value of n.\n");
        return 1;
    }

    int *A =
        (int *)malloc(n * sizeof(int));

    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /*
       Input permutation.
    */

    printf("Enter permutation of 1 to %d:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("\nOriginal permutation:\n");
    printArray(A, n);

    /*
       Reset statistics.
    */

    reversalCount = 0;
    reversalCost = 0;

    /*
       Start timing.
    */

    clock_t start = clock();

    /*
       Sort using reversal merge sort.
    */

    reversalMergeSort(A, 0, n - 1);

    /*
       End timing.
    */

    clock_t end = clock();

    double elapsed =
        (double)(end - start) /
        CLOCKS_PER_SEC;

    /*
       Output.
    */

    printf("\nSorted permutation:\n");
    printArray(A, n);

    printf("\nValidation:\n");

    if (isSorted(A, n))
        printf("Array is sorted correctly.\n");
    else
        printf("ERROR: Array is not sorted.\n");

    printf("\nNumber of reversals = %lld\n",
           reversalCount);

    printf("Total reversal cost = %lld\n",
           reversalCost);

    printf("Execution time = %.6f seconds\n",
           elapsed);

    free(A);

    return 0;
}