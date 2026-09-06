#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define EPSILON 1e-9

/* =========================================================
   Utility Functions
   ========================================================= */

double **allocateMatrix(int n)
{
    double **A = (double **)malloc(n * sizeof(double *));

    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        A[i] = (double *)malloc(n * sizeof(double));

        if (A[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    return A;
}

void freeMatrix(double **A, int n)
{
    for (int i = 0; i < n; i++)
        free(A[i]);

    free(A);
}

void inputMatrix(double **A, int n)
{
    printf("Enter %d x %d matrix:\n", n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &A[i][j]);
        }
    }
}

void printMatrix(double **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%10.3lf ", A[i][j]);
        }

        printf("\n");
    }
}

/* =========================================================
   (i) Matrix Addition

   C = A + B

   Time Complexity: O(n^2)
   Space Complexity: O(n^2) for result
   ========================================================= */

void matrixAddition(double **A, double **B,
                    double **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

/* =========================================================
   (ii) Matrix Multiplication

   C = A * B

   Time Complexity: O(n^3)
   Space Complexity: O(n^2)

   C[i][j] = sum(A[i][k] * B[k][j])
   ========================================================= */

void matrixMultiplication(double **A, double **B,
                          double **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* =========================================================
   (iii) Check Whether Matrix is Zero Matrix

   Time Complexity: O(n^2)
   Space Complexity: O(1)
   ========================================================= */

int isZeroMatrix(double **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fabs(A[i][j]) > EPSILON)
                return 0;
        }
    }

    return 1;
}

/* =========================================================
   (iv) Check Whether Matrix is Symmetric

   A matrix is symmetric if:

       A[i][j] = A[j][i]

   We only need to examine one triangular half.

   Time Complexity: O(n^2)
   Space Complexity: O(1)
   ========================================================= */

int isSymmetric(double **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(A[i][j] - A[j][i]) > EPSILON)
                return 0;
        }
    }

    return 1;
}

/* =========================================================
   (v) Determinant Using Gaussian Elimination

   Time Complexity: O(n^3)
   Space Complexity: O(1) extra apart from matrix

   The matrix is modified during the calculation.
   ========================================================= */

double determinant(double **A, int n)
{
    double det = 1.0;

    for (int i = 0; i < n; i++)
    {
        /* Find pivot */
        int pivot = i;

        for (int j = i + 1; j < n; j++)
        {
            if (fabs(A[j][i]) > fabs(A[pivot][i]))
                pivot = j;
        }

        /* Singular matrix */
        if (fabs(A[pivot][i]) < EPSILON)
            return 0.0;

        /* Swap rows if necessary */
        if (pivot != i)
        {
            double *temp = A[i];
            A[i] = A[pivot];
            A[pivot] = temp;

            det = -det;
        }

        det *= A[i][i];

        /* Eliminate entries below pivot */
        for (int j = i + 1; j < n; j++)
        {
            double factor = A[j][i] / A[i][i];

            for (int k = i + 1; k < n; k++)
            {
                A[j][k] -= factor * A[i][k];
            }
        }
    }

    return det;
}

/* =========================================================
   (vi) In-place Matrix Transpose

   Swap A[i][j] and A[j][i].

   Time Complexity: O(n^2)
   Extra Space: O(1)
   ========================================================= */

void transposeInPlace(double **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

/* =========================================================
   (vii) Eigenvalue and Eigenvector

   Power Iteration

   Finds the DOMINANT eigenvalue and corresponding
   eigenvector.

   Each iteration performs matrix-vector multiplication:

       O(n^2)

   Therefore:

       O(k * n^2)

   where k = number of iterations.

   This is NOT a complete algorithm for finding all
   eigenvalues/eigenvectors.

   For the complete dense eigenvalue problem, standard
   QR-based methods are generally O(n^3).
   ========================================================= */

double dotProduct(double *a, double *b, int n)
{
    double result = 0.0;

    for (int i = 0; i < n; i++)
        result += a[i] * b[i];

    return result;
}

double vectorNorm(double *v, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += v[i] * v[i];

    return sqrt(sum);
}

void matrixVectorMultiply(double **A,
                          double *x,
                          double *result,
                          int n)
{
    for (int i = 0; i < n; i++)
    {
        result[i] = 0.0;

        for (int j = 0; j < n; j++)
        {
            result[i] += A[i][j] * x[j];
        }
    }
}

void dominantEigen(double **A, int n,
                   double *eigenvalue,
                   double *eigenvector)
{
    double *x = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));

    /* Initial vector */
    for (int i = 0; i < n; i++)
        x[i] = 1.0;

    int iterations = 1000;

    for (int iter = 0; iter < iterations; iter++)
    {
        /* y = A*x */
        matrixVectorMultiply(A, x, y, n);

        /* Normalize y */
        double norm = vectorNorm(y, n);

        if (norm < EPSILON)
            break;

        for (int i = 0; i < n; i++)
            x[i] = y[i] / norm;
    }

    /* Calculate A*x one final time */
    matrixVectorMultiply(A, x, y, n);

    /* Rayleigh quotient */
    double numerator = dotProduct(x, y, n);
    double denominator = dotProduct(x, x, n);

    *eigenvalue = numerator / denominator;

    for (int i = 0; i < n; i++)
        eigenvector[i] = x[i];

    free(x);
    free(y);
}

/* =========================================================
   Main Function
   ========================================================= */

int main()
{
    int n;

    printf("Enter order of square matrices (n): ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid matrix size.\n");
        return 1;
    }

    /* Allocate matrices */
    double **A = allocateMatrix(n);
    double **B = allocateMatrix(n);
    double **C = allocateMatrix(n);

    /* -----------------------------------------------------
       Input Matrix A
       ----------------------------------------------------- */

    printf("\nMatrix A\n");
    inputMatrix(A, n);

    /* -----------------------------------------------------
       Input Matrix B
       ----------------------------------------------------- */

    printf("\nMatrix B\n");
    inputMatrix(B, n);

    /* =====================================================
       (i) Matrix Addition
       ===================================================== */

    matrixAddition(A, B, C, n);

    printf("\n(i) Matrix Addition (A + B):\n");
    printMatrix(C, n);

    /* =====================================================
       (ii) Matrix Multiplication
       ===================================================== */

    matrixMultiplication(A, B, C, n);

    printf("\n(ii) Matrix Multiplication (A * B):\n");
    printMatrix(C, n);

    /* =====================================================
       (iii) Zero Matrix
       ===================================================== */

    if (isZeroMatrix(A, n))
        printf("\n(iii) Matrix A is a ZERO matrix.\n");
    else
        printf("\n(iii) Matrix A is NOT a zero matrix.\n");

    /* =====================================================
       (iv) Symmetric Matrix
       ===================================================== */

    if (isSymmetric(A, n))
        printf("\n(iv) Matrix A is SYMMETRIC.\n");
    else
        printf("\n(iv) Matrix A is NOT symmetric.\n");

    /* =====================================================
       (v) Determinant
       
       Create a copy because determinant() modifies matrix.
       ===================================================== */

    double **D = allocateMatrix(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = A[i][j];
        }
    }

    double det = determinant(D, n);

    printf("\n(v) Determinant of Matrix A = %.4lf\n", det);

    freeMatrix(D, n);

    /* =====================================================
       (vi) In-place Transpose
       ===================================================== */

    transposeInPlace(A, n);

    printf("\n(vi) Matrix A after in-place transpose:\n");
    printMatrix(A, n);

    /* =====================================================
       (vii) Eigenvalue and Eigenvector
       ===================================================== */

    /* Use B because A has already been transposed */
    double *eigenvector =
        (double *)malloc(n * sizeof(double));

    double eigenvalue;

    dominantEigen(B, n,
                  &eigenvalue,
                  eigenvector);

    printf("\n(vii) Dominant Eigenvalue of Matrix B = %.6lf\n",
           eigenvalue);

    printf("Corresponding Eigenvector:\n");

    for (int i = 0; i < n; i++)
        printf("%.6lf\n", eigenvector[i]);

    free(eigenvector);

    /* =====================================================
       Free Memory
       ===================================================== */

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}