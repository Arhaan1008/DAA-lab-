
#include <stdio.h>
#include <limits.h>

#define MAX 105

long long w[MAX], prefix[MAX];
long long dp[MAX][MAX];
int split[MAX][MAX];
void printTree(int i, int j) {
    if (i == j) {
        printf("Leaf(%d, weight=%lld)", i, w[i]);
        return;
    }

    int k = split[i][j];

    printf("(");
    printTree(i, k);
    printf(" , ");
    printTree(k + 1, j);
    printf(")");
}

int main(void) {
    int n, i, j, k, len;

    printf("Enter number of weights (1-%d): ", MAX - 1);

    if (scanf("%d", &n) != 1 || n < 1 || n >= MAX) {
        printf("Invalid number of weights.\n");
        return 1;
    }

    printf("Enter the weights in their given order:\n");

    prefix[0] = 0;

    for (i = 1; i <= n; i++) {
        if (scanf("%lld", &w[i]) != 1 || w[i] <= 0) {
            printf("Weights must be positive integers.\n");
            return 1;
        }

        if (prefix[i - 1] > LLONG_MAX - w[i]) {
            printf("Weight sum is too large.\n");
            return 1;
        }

        prefix[i] = prefix[i - 1] + w[i];
        dp[i][i] = 0;
        split[i][i] = i;
    }

    for (len = 2; len <= n; len++) {
        for (i = 1; i + len - 1 <= n; i++) {
            j = i + len - 1;

            long long sum = prefix[j] - prefix[i - 1];
            long long best = LLONG_MAX;
            int bestK = i;

            for (k = i; k < j; k++) {
                long long left = dp[i][k];
                long long right = dp[k + 1][j];

                if (left <= LLONG_MAX - right &&
                    left + right <= LLONG_MAX - sum) {
                    long long cost = left + right + sum;

                    if (cost < best) {
                        best = cost;
                        bestK = k;
                    }
                }
            }

            dp[i][j] = best;
            split[i][j] = bestK;
        }
    }

    printf("\nMinimum weighted path length = %lld\n", dp[1][n]);

    printf("Optimal alphabetic tree:\n");
    printTree(1, n);
    printf("\n");

    return 0;
}
