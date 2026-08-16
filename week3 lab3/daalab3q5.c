#include <stdio.h>
#include <stdlib.h>

/* Allocate n x n matrix */
int **allocateMatrix(int n)
{
    int **A = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
        A[i] = (int *)calloc(n, sizeof(int));

    return A;
}

/* Free matrix */
void freeMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
        free(A[i]);

    free(A);
}

/* Add matrices: C = A + B */
void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

/* Subtract matrices: C = A - B */
void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

/*
 * Divide-and-conquer multiplication
 * for matrices having the special structure:
 *
 *       A1  A2
 * A  =  A2  A1
 *
 *       B1  B2
 * B  =  B2  B1
 */
void specialMultiply(int **A, int **B, int **C, int n)
{
    /* Base case */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    /* Allocate submatrices */
    int **A1 = allocateMatrix(k);
    int **A2 = allocateMatrix(k);
    int **B1 = allocateMatrix(k);
    int **B2 = allocateMatrix(k);

    /*
     * Extract the two distinct blocks.
     *
     * A = [ A1 A2 ]
     *     [ A2 A1 ]
     *
     * B = [ B1 B2 ]
     *     [ B2 B1 ]
     */
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    /*
     * S1 = A1 + A2
     * S2 = A1 - A2
     * S3 = B1 + B2
     * S4 = B1 - B2
     */
    int **S1 = allocateMatrix(k);
    int **S2 = allocateMatrix(k);
    int **S3 = allocateMatrix(k);
    int **S4 = allocateMatrix(k);

    addMatrix(A1, A2, S1, k);
    subtractMatrix(A1, A2, S2, k);

    addMatrix(B1, B2, S3, k);
    subtractMatrix(B1, B2, S4, k);

    /*
     * P = (A1 + A2)(B1 + B2)
     * Q = (A1 - A2)(B1 - B2)
     */
    int **P = allocateMatrix(k);
    int **Q = allocateMatrix(k);

    specialMultiply(S1, S3, P, k);
    specialMultiply(S2, S4, Q, k);

    /*
     * C1 = (P + Q) / 2
     * C2 = (P - Q) / 2
     */
    int **C1 = allocateMatrix(k);
    int **C2 = allocateMatrix(k);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C1[i][j] = (P[i][j] + Q[i][j]) / 2;
            C2[i][j] = (P[i][j] - Q[i][j]) / 2;
        }
    }

    /*
     * Construct:
     *
     *       C1 C2
     * C =   C2 C1
     */
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C1[i][j];
            C[i][j + k] = C2[i][j];

            C[i + k][j] = C2[i][j];
            C[i + k][j + k] = C1[i][j];
        }
    }

    /* Free memory */
    freeMatrix(A1, k);
    freeMatrix(A2, k);
    freeMatrix(B1, k);
    freeMatrix(B2, k);

    freeMatrix(S1, k);
    freeMatrix(S2, k);
    freeMatrix(S3, k);
    freeMatrix(S4, k);

    freeMatrix(P, k);
    freeMatrix(Q, k);

    freeMatrix(C1, k);
    freeMatrix(C2, k);
}

/* Print matrix */
void printMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d\t", A[i][j]);

        printf("\n");
    }
}

int main()
{
    int n;

    printf("Enter n (power of 2): ");
    scanf("%d", &n);

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    printf("\nEnter matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("\nEnter matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    specialMultiply(A, B, C, n);

    printf("\nProduct matrix C = A * B:\n");
    printMatrix(C, n);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}