#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int eggDropDP(int eggs, int floors)
{
    int **dp;

    /* Allocate DP table */
    dp = (int **)malloc((eggs + 1) * sizeof(int *));
    for (int e = 0; e <= eggs; e++)
        dp[e] = (int *)malloc((floors + 1) * sizeof(int));

    /* Base cases */
    for (int e = 0; e <= eggs; e++)
        dp[e][0] = 0;

    for (int e = 1; e <= eggs; e++)
        dp[e][1] = 1;

    /* With one egg, test every floor */
    for (int f = 0; f <= floors; f++)
        dp[1][f] = f;

    /* General recurrence */
    for (int e = 2; e <= eggs; e++) {
        for (int f = 2; f <= floors; f++) {

            dp[e][f] = INF;

            for (int x = 1; x <= f; x++) {

                int eggBreaks = dp[e - 1][x - 1];
                int eggSurvives = dp[e][f - x];

                int worst = (eggBreaks > eggSurvives)
                            ? eggBreaks
                            : eggSurvives;

                int drops = 1 + worst;

                if (drops < dp[e][f])
                    dp[e][f] = drops;
            }
        }
    }

    int answer = dp[eggs][floors];

    /* Free memory */
    for (int e = 0; e <= eggs; e++)
        free(dp[e]);
    free(dp);

    return answer;
}

int main(void)
{
    int E, F;

    printf("Enter number of eggs and floors: ");
    scanf("%d %d", &E, &F);

    if (E < 1 || F < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int answer = eggDropDP(E, F);

    printf("Eggs   : %d\n", E);
    printf("Floors : %d\n", F);
    printf("Minimum worst-case drops: %d\n", answer);

    return 0;
}