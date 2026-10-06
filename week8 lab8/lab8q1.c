#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int minCoinChange(int coins[], int n, int V)
{
    int *dp = (int *)malloc((V + 1) * sizeof(int));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    // Base case
    dp[0] = 0;

    // Initialize all other values
    for (int i = 1; i <= V; i++)
        dp[i] = V + 1;

    // Build the DP table
    for (int amount = 1; amount <= V; amount++)
    {
        for (int j = 0; j < n; j++)
        {
            if (coins[j] <= amount)
            {
                dp[amount] = min(dp[amount],
                                 dp[amount - coins[j]] + 1);
            }
        }
    }

    int result;

    if (dp[V] > V)
        result = -1;
    else
        result = dp[V];

    free(dp);

    return result;
}

int main()
{
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = (int *)malloc(n * sizeof(int));

    if (coins == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter coin denominations:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    if (V < 0)
    {
        printf("Target amount must be non-negative.\n");
        free(coins);
        return 1;
    }

    int result = minCoinChange(coins, n, V);

    if (result == -1)
        printf("Minimum coins = -1 (Amount cannot be formed)\n");
    else
        printf("Minimum number of coins = %d\n", result);

    free(coins);

    return 0;
}