#include <stdio.h>
#include <stdlib.h>

long long countWays(int coins[], int n, int V)
{
    // dp[i] = number of ways to make amount i
    long long *dp = (long long *)calloc(V + 1, sizeof(long long));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    // There is one way to make amount 0:
    // choose no coins.
    dp[0] = 1;

    // Process coins one by one
    for (int i = 0; i < n; i++)
    {
        for (int amount = coins[i]; amount <= V; amount++)
        {
            dp[amount] += dp[amount - coins[i]];
        }
    }

    long long result = dp[V];

    free(dp);

    return result;
}

int main()
{
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of coins must be positive.\n");
        return 1;
    }

    int *coins = (int *)malloc(n * sizeof(int));

    if (coins == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter coin denominations:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);

        if (coins[i] <= 0)
        {
            printf("Coin denomination must be positive.\n");
            free(coins);
            return 1;
        }
    }

    printf("Enter target amount: ");
    scanf("%d", &V);

    if (V < 0)
    {
        printf("Target amount cannot be negative.\n");
        free(coins);
        return 1;
    }

    long long result = countWays(coins, n, V);

    if (result == -1)
        printf("Error in memory allocation.\n");
    else
        printf("Total number of ways = %lld\n", result);

    free(coins);

    return 0;
}