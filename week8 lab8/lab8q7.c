#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid rod length.\n");
        return 0;
    }

    // Price array: price[i] = price of a piece of length i
    int *price = (int *)malloc((n + 1) * sizeof(int));

    // dp[i] = maximum revenue for rod of length i
    int *dp = (int *)malloc((n + 1) * sizeof(int));

    // firstCut[i] = first piece length selected for rod length i
    int *firstCut = (int *)malloc((n + 1) * sizeof(int));

    if (price == NULL || dp == NULL || firstCut == NULL)
    {
        printf("Memory allocation failed.\n");
        free(price);
        free(dp);
        free(firstCut);
        return 0;
    }

    price[0] = 0;

    printf("Enter prices for pieces of length 1 to %d:\n", n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &price[i]);

        if (price[i] < 0)
        {
            printf("Price cannot be negative.\n");
            free(price);
            free(dp);
            free(firstCut);
            return 0;
        }
    }

    // Base case
    dp[0] = 0;
    firstCut[0] = 0;

    // Bottom-up Dynamic Programming
    for (int i = 1; i <= n; i++)
    {
        dp[i] = -1;
        firstCut[i] = 0;

        // Try every possible first piece
        for (int j = 1; j <= i; j++)
        {
            int currentRevenue = price[j] + dp[i - j];

            if (currentRevenue > dp[i])
            {
                dp[i] = currentRevenue;
                firstCut[i] = j;
            }
        }
    }

    // Maximum revenue
    printf("\nMaximum Revenue = %d\n", dp[n]);

    // Reconstruction
    printf("Optimal decomposition: ");

    int remaining = n;

    while (remaining > 0)
    {
        int piece = firstCut[remaining];

        printf("%d", piece);

        remaining -= piece;

        if (remaining > 0)
            printf(" + ");
    }

    printf("\n");

    // Display DP table
    printf("\nDP Table:\n");
    printf("Length\tMaximum Revenue\tFirst Piece\n");

    for (int i = 0; i <= n; i++)
    {
        printf("%d\t%d\t\t%d\n",
               i, dp[i], firstCut[i]);
    }

    free(price);
    free(dp);
    free(firstCut);

    return 0;
}