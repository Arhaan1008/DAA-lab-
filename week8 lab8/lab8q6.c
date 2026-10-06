#include <stdio.h>
#include <string.h>

#define MAX 100

int min3(int a, int b, int c)
{
    int min = a;

    if (b < min)
        min = b;

    if (c < min)
        min = c;

    return min;
}

void printTraceback(char A[], char B[], int dp[MAX][MAX], int m, int n)
{
    char operations[2 * MAX];
    int count = 0;

    int i = m;
    int j = n;

    // Traceback from dp[m][n] to dp[0][0]
    while (i > 0 || j > 0)
    {
        // Characters are equal
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1] &&
            dp[i][j] == dp[i - 1][j - 1])
        {
            operations[count++] = 'M';   // Match
            i--;
            j--;
        }

        // Substitution
        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1)
        {
            operations[count++] = 'S';
            i--;
            j--;
        }

        // Deletion
        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1)
        {
            operations[count++] = 'D';
            i--;
        }

        // Insertion
        else
        {
            operations[count++] = 'I';
            j--;
        }
    }

    printf("\nTraceback operations:\n");

    // Print operations in correct order
    for (int k = count - 1; k >= 0; k--)
    {
        if (operations[k] == 'M')
            printf("Match\n");

        else if (operations[k] == 'S')
            printf("Substitute '%c' -> '%c'\n",
                   A[0], B[0]);

        else if (operations[k] == 'D')
            printf("Delete\n");

        else if (operations[k] == 'I')
            printf("Insert\n");
    }
}

int main()
{
    char A[MAX], B[MAX];
    int dp[MAX][MAX];

    printf("Enter first string: ");
    scanf("%99s", A);

    printf("Enter second string: ");
    scanf("%99s", B);

    int m = strlen(A);
    int n = strlen(B);

    // Base cases
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    // Fill DP table
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min3(
                    dp[i - 1][j],       // Deletion
                    dp[i][j - 1],       // Insertion
                    dp[i - 1][j - 1]    // Substitution
                );
            }
        }
    }

    printf("\nMinimum Edit Distance = %d\n", dp[m][n]);

    printTraceback(A, B, dp, m, n);

    return 0;
}