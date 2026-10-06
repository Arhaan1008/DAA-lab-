#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void printTree(int root[][100], int i, int j)
{
    if (i > j)
    {
        if (i == j + 1)
            printf("D%d", j);
        return;
    }

    int r = root[i][j];

    printf("K%d", r);

    printf("  ");

    if (i <= r - 1)
    {
        printf("Left: ");
        printTree(root, i, r - 1);
    }
    else
    {
        printf("Left: D%d", r - 1);
    }

    printf("  ");

    if (r + 1 <= j)
    {
        printf("Right: ");
        printTree(root, r + 1, j);
    }
    else
    {
        printf("Right: D%d", r);
    }
}

int main()
{
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    if (n <= 0 || n >= 100)
    {
        printf("Invalid number of keys.\n");
        return 0;
    }

    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));

    double e[100][100];
    double w[100][100];
    int root[100][100];

    if (p == NULL || q == NULL)
    {
        printf("Memory allocation failed.\n");
        free(p);
        free(q);
        return 0;
    }

    printf("Enter successful search probabilities p1...p%d:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter unsuccessful search probabilities q0...q%d:\n", n);

    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    /*
       Initialization:
       e[i][i-1] represents an empty subtree.
    */
    for (int i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    /*
       Bottom-up Dynamic Programming
    */
    for (int length = 1; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            e[i][j] = DBL_MAX;

            w[i][j] = w[i][j - 1] + p[j] + q[j];

            /*
               Try every key as the root.
            */
            for (int r = i; r <= j; r++)
            {
                double cost = e[i][r - 1]
                            + e[r + 1][j]
                            + w[i][j];

                if (cost < e[i][j])
                {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost = %.4lf\n",
           e[1][n]);

    printf("\nRoot of the Optimal BST = K%d\n",
           root[1][n]);

    printf("\nRoot Table:\n");

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            printf("root[%d][%d] = K%d\n",
                   i, j, root[i][j]);
        }
    }

    printf("\nOptimal BST structure:\n");
    printTree(root, 1, n);
    printf("\n");

    free(p);
    free(q);

    return 0;
}