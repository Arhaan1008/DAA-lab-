#include <stdio.h>
#include <stdlib.h>

int longestIncreasingSubsequence(int A[], int n)
{
    int *dp = (int *)malloc(n * sizeof(int));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    // Every element itself is an LIS of length 1
    for (int i = 0; i < n; i++)
        dp[i] = 1;

    // Calculate LIS ending at every index
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i] && dp[i] < dp[j] + 1)
                dp[i] = dp[j] + 1;
        }
    }

    // Find maximum LIS length
    int maxLength = dp[0];

    for (int i = 1; i < n; i++)
    {
        if (dp[i] > maxLength)
            maxLength = dp[i];
    }

    free(dp);

    return maxLength;
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

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    int result = longestIncreasingSubsequence(A, n);

    printf("Length of Longest Increasing Subsequence = %d\n", result);

    free(A);

    return 0;
}