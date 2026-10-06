#include <stdio.h>
#include <stdlib.h>

int maxSumIncreasingSubsequence(int A[], int n)
{
    int *dp = (int *)malloc(n * sizeof(int));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    // Each element alone forms an increasing subsequence
    for (int i = 0; i < n; i++)
        dp[i] = A[i];

    // Calculate maximum sum ending at each index
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i])
            {
                if (dp[i] < dp[j] + A[i])
                    dp[i] = dp[j] + A[i];
            }
        }
    }

    // Find the maximum sum
    int maxSum = dp[0];

    for (int i = 1; i < n; i++)
    {
        if (dp[i] > maxSum)
            maxSum = dp[i];
    }

    free(dp);

    return maxSum;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid array size.\n");
        return 0;
    }

    int *A = (int *)malloc(n * sizeof(int));

    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("Enter %d positive integers:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);

        if (A[i] <= 0)
        {
            printf("Elements must be positive.\n");
            free(A);
            return 0;
        }
    }

    int result = maxSumIncreasingSubsequence(A, n);

    printf("Maximum Sum Increasing Subsequence = %d\n", result);

    free(A);

    return 0;
}