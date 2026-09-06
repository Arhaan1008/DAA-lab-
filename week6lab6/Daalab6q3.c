#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

/* =========================================================
   Complex Number Structure
   ========================================================= */

typedef struct
{
    double real;
    double imag;
} Complex;


/* =========================================================
   Complex Number Operations
   ========================================================= */

Complex add(Complex a, Complex b)
{
    Complex result;

    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;

    return result;
}

Complex subtract(Complex a, Complex b)
{
    Complex result;

    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;

    return result;
}

Complex multiply(Complex a, Complex b)
{
    Complex result;

    result.real = a.real * b.real -
                  a.imag * b.imag;

    result.imag = a.real * b.imag +
                  a.imag * b.real;

    return result;
}


/* =========================================================
   Recursive FFT

   If invert = 0:
       Computes FFT

   If invert = 1:
       Computes Inverse FFT

   Recurrence:

       T(n) = 2T(n/2) + O(n)

   Therefore:

       T(n) = O(n log n)
   ========================================================= */

void fft(Complex *a, int n, int invert)
{
    if (n == 1)
        return;

    /* -----------------------------------------------------
       Divide the array into even and odd elements
       ----------------------------------------------------- */

    Complex *even =
        (Complex *)malloc((n / 2) * sizeof(Complex));

    Complex *odd =
        (Complex *)malloc((n / 2) * sizeof(Complex));

    for (int i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    /* -----------------------------------------------------
       Recursive calls
       ----------------------------------------------------- */

    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    /* -----------------------------------------------------
       Combine step
       ----------------------------------------------------- */

    double angle = 2.0 * PI / n;

    if (invert)
        angle = -angle;

    Complex w;
    w.real = 1.0;
    w.imag = 0.0;

    Complex wn;
    wn.real = cos(angle);
    wn.imag = sin(angle);

    for (int k = 0; k < n / 2; k++)
    {
        Complex t = multiply(w, odd[k]);

        a[k] = add(even[k], t);
        a[k + n / 2] = subtract(even[k], t);

        w = multiply(w, wn);
    }

    free(even);
    free(odd);

    /* -----------------------------------------------------
       Divide by n for inverse FFT
       ----------------------------------------------------- */

    if (invert)
    {
        for (int i = 0; i < n; i++)
        {
            a[i].real /= 2.0;
            a[i].imag /= 2.0;
        }
    }
}


/* =========================================================
   Convolution using FFT

   A length = m
   B length = n

   Result length = m + n - 1

   Time Complexity = O(N log N)

   Since m <= n:

       N = O(n)

   Therefore:

       O(n log n)
   ========================================================= */

void convolution(double A[], int m,
                 double B[], int n,
                 double C[])
{
    int requiredSize = m + n - 1;

    /* -----------------------------------------------------
       Find the smallest power of 2 >= m + n - 1
       ----------------------------------------------------- */

    int N = 1;

    while (N < requiredSize)
        N *= 2;

    /* -----------------------------------------------------
       Allocate complex arrays
       ----------------------------------------------------- */

    Complex *FA =
        (Complex *)calloc(N, sizeof(Complex));

    Complex *FB =
        (Complex *)calloc(N, sizeof(Complex));

    /* -----------------------------------------------------
       Copy input vectors and zero-pad
       ----------------------------------------------------- */

    for (int i = 0; i < m; i++)
        FA[i].real = A[i];

    for (int i = 0; i < n; i++)
        FB[i].real = B[i];

    /* -----------------------------------------------------
       FFT of A and B
       ----------------------------------------------------- */

    fft(FA, N, 0);
    fft(FB, N, 0);

    /* -----------------------------------------------------
       Point-wise multiplication
       ----------------------------------------------------- */

    for (int i = 0; i < N; i++)
        FA[i] = multiply(FA[i], FB[i]);

    /* -----------------------------------------------------
       Inverse FFT
       ----------------------------------------------------- */

    fft(FA, N, 1);

    /* -----------------------------------------------------
       Extract real part of result
       ----------------------------------------------------- */

    for (int i = 0; i < requiredSize; i++)
        C[i] = FA[i].real;

    free(FA);
    free(FB);
}


/* =========================================================
   Naive Convolution

   This is included only to validate the FFT result.

   Time Complexity:

       O(mn)

   Since m <= n:

       O(n^2)
   ========================================================= */

void naiveConvolution(double A[], int m,
                      double B[], int n,
                      double C[])
{
    int size = m + n - 1;

    for (int i = 0; i < size; i++)
        C[i] = 0.0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i + j] += A[i] * B[j];
        }
    }
}


/* =========================================================
   Print Vector
   ========================================================= */

void printVector(double C[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%.4lf ", C[i]);
    }

    printf("\n");
}


/* =========================================================
   Main Function
   ========================================================= */

int main()
{
    int m, n;

    printf("Enter size of vector A (m): ");
    scanf("%d", &m);

    printf("Enter size of vector B (n): ");
    scanf("%d", &n);

    /* -----------------------------------------------------
       Requirement: n >= m
       ----------------------------------------------------- */

    if (m <= 0 || n <= 0)
    {
        printf("Vector sizes must be positive.\n");
        return 1;
    }

    if (n < m)
    {
        printf("Error: n must be greater than or equal to m.\n");
        return 1;
    }

    /* -----------------------------------------------------
       Allocate vectors
       ----------------------------------------------------- */

    double *A =
        (double *)malloc(m * sizeof(double));

    double *B =
        (double *)malloc(n * sizeof(double));

    int resultSize = m + n - 1;

    double *C =
        (double *)malloc(resultSize * sizeof(double));

    double *Ccheck =
        (double *)malloc(resultSize * sizeof(double));

    if (A == NULL || B == NULL ||
        C == NULL || Ccheck == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* -----------------------------------------------------
       Input vector A
       ----------------------------------------------------- */

    printf("\nEnter %d elements of A:\n", m);

    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    /* -----------------------------------------------------
       Input vector B
       ----------------------------------------------------- */

    printf("\nEnter %d elements of B:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    /* -----------------------------------------------------
       Display input
       ----------------------------------------------------- */

    printf("\nA = ");
    printVector(A, m);

    printf("B = ");
    printVector(B, n);

    /* -----------------------------------------------------
       FFT Convolution
       ----------------------------------------------------- */

    convolution(A, m, B, n, C);

    printf("\nConvolution using FFT:\n");
    printVector(C, resultSize);

    /* -----------------------------------------------------
       Naive convolution for validation
       ----------------------------------------------------- */

    naiveConvolution(A, m, B, n, Ccheck);

    printf("\nConvolution using direct method:\n");
    printVector(Ccheck, resultSize);

    /* -----------------------------------------------------
       Compare both results
       ----------------------------------------------------- */

    int correct = 1;

    for (int i = 0; i < resultSize; i++)
    {
        if (fabs(C[i] - Ccheck[i]) > 1e-6)
        {
            correct = 0;
            break;
        }
    }

    if (correct)
        printf("\nValidation: FFT result is CORRECT.\n");
    else
        printf("\nValidation: Results DO NOT MATCH.\n");

    /* -----------------------------------------------------
       Free memory
       ----------------------------------------------------- */

    free(A);
    free(B);
    free(C);
    free(Ccheck);

    return 0;
}