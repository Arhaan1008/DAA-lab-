#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

/* Print optimal parenthesization */
void printOptimalParenthesis(int s[MAX][MAX],
                             int i, int j)
{
    if (i == j) {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOptimalParenthesis(s, i, s[i][j]);

    printOptimalParenthesis(s, s[i][j] + 1, j);

    printf(")");
}

int main(void)
{
    int n;
    int p[MAX];

    /*
     * m[i][j] = minimum cost of multiplying
     *           Ai ... Aj
     *
     * s[i][j] = index at which the optimal
     *           split occurs
     */
    long long m[MAX][MAX] = {0};
    int s[MAX][MAX] = {0};

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX) {
        printf("Invalid number of matrices.\n");
        return 1;
    }

    /*
     * There are n+1 dimensions.
     */
    printf("Enter %d dimensions:\n", n + 1);

    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    /*
     * Chain length = 2, 3, ..., n
     */
    for (int length = 2; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            m[i][j] = LLONG_MAX;

            /*
             * Try every possible split.
             */
            for (int k = i; k < j; k++) {

                long long cost =
                    m[i][k]
                    + m[k + 1][j]
                    + (long long)p[i - 1]
                    * p[k]
                    * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %lld\n",
           m[1][n]);

    printf("Optimal parenthesization = ");
    printOptimalParenthesis(s, 1, n);
    printf("\n");

    /*
     * Display DP cost table.
     */
    printf("\nDP Cost Table:\n");

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {

            if (i > j)
                printf("-\t");
            else
                printf("%lld\t", m[i][j]);
        }

        printf("\n");
    }

    /*
     * Display split table.
     */
    printf("\nSplit Table:\n");

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {

            if (i >= j)
                printf("-\t");
            else
                printf("%d\t", s[i][j]);
        }

        printf("\n");
    }

    return 0;
}
