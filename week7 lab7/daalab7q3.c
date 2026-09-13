#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long ull;

int main(void)
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Invalid number of disks.\n");
        return 1;
    }

    /*
     * dp[i] = minimum number of moves for i disks
     * split[i] = optimal number of disks moved first
     */
    ull *dp = malloc((n + 1) * sizeof(ull));
    int *split = malloc((n + 1) * sizeof(int));

    if (dp == NULL || split == NULL) {
        printf("Memory allocation failed.\n");
        free(dp);
        free(split);
        return 1;
    }

    dp[0] = 0;
    split[0] = 0;

    if (n >= 1) {
        dp[1] = 1;
        split[1] = 0;
    }

    for (int disks = 2; disks <= n; disks++) {

        dp[disks] = ULLONG_MAX;
        split[disks] = 0;

        /*
         * k disks are moved using four pegs.
         * The remaining disks are moved using three pegs.
         */
        for (int k = 1; k < disks; k++) {

            int remaining = disks - k;

            /*
             * 2^(remaining) - 1
             * is the ordinary 3-peg Hanoi cost.
             */
            ull hanoi = (1ULL << remaining) - 1;

            ull moves = 2 * dp[k] + hanoi;

            if (moves < dp[disks]) {
                dp[disks] = moves;
                split[disks] = k;
            }
        }
    }

    printf("\nMinimum moves for %d disks = %llu\n",
           n, dp[n]);

    printf("Optimal split k = %d\n", split[n]);

    printf("\nDP table:\n");
    printf("Disks\tMoves\tOptimal k\n");

    for (int i = 0; i <= n; i++) {
        printf("%d\t%llu\t%d\n",
               i, dp[i], split[i]);
    }

    free(dp);
    free(split);

    return 0;
}