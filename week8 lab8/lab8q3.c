#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void findLCS(char X[], char Y[])
{
    int m = strlen(X);
    int n = strlen(Y);

    // Allocate DP table
    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i <= m; i++)
    {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));

        if (dp[i] == NULL)
        {
            printf("Memory allocation failed.\n");

            for (int k = 0; k < i; k++)
                free(dp[k]);

            free(dp);
            return;
        }
    }

    // Initialize first row and first column
    for (int i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (int j = 0; j <= n; j++)
        dp[0][j] = 0;

    // Build DP table
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Length of LCS
    int lcsLength = dp[m][n];

    // Allocate memory for LCS
    char *lcs = (char *)malloc((lcsLength + 1) * sizeof(char));

    if (lcs == NULL)
    {
        printf("Memory allocation failed.\n");

        for (int i = 0; i <= m; i++)
            free(dp[i]);

        free(dp);
        return;
    }

    lcs[lcsLength] = '\0';

    // Reconstruct LCS by tracing backwards
    int i = m;
    int j = n;
    int index = lcsLength - 1;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index] = X[i - 1];

            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("\nLength of LCS = %d\n", lcsLength);
    printf("Longest Common Subsequence = %s\n", lcs);

    // Free memory
    free(lcs);

    for (int k = 0; k <= m; k++)
        free(dp[k]);

    free(dp);
}

int main()
{
    char X[1000], Y[1000];

    printf("Enter first sequence: ");
    scanf("%999s", X);

    printf("Enter second sequence: ");
    scanf("%999s", Y);

    findLCS(X, Y);

    return 0;
}