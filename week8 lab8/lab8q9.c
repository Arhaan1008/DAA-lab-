#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

/* Structure to store trajectory information */
typedef struct
{
    ull start;
    ull steps;
    ull maximum;
} CollatzInfo;


/*
 * Returns the next number in the Collatz sequence.
 */
ull collatzNext(ull n)
{
    if (n % 2 == 0)
        return n / 2;
    else
        return 3 * n + 1;
}


/*
 * Analyze one Collatz trajectory.
 *
 * Returns:
 *   steps  - number of steps required to reach 1
 *   maximum - maximum value encountered
 */
CollatzInfo analyzeTrajectory(ull n)
{
    CollatzInfo info;

    info.start = n;
    info.steps = 0;
    info.maximum = n;

    while (n != 1)
    {
        n = collatzNext(n);
        info.steps++;

        if (n > info.maximum)
            info.maximum = n;
    }

    return info;
}


/*
 * Print the complete Collatz trajectory.
 */
void printTrajectory(ull n)
{
    printf("\nTrajectory:\n");

    printf("%llu", n);

    while (n != 1)
    {
        n = collatzNext(n);
        printf(" -> %llu", n);
    }

    printf("\n");
}


/*
 * Analyze all starting values in [a,b].
 */
void analyzeInterval(ull a, ull b)
{
    ull longestStart = a;
    ull longestSteps = 0;

    ull largestPeakStart = a;
    ull largestPeak = 0;

    ull totalSteps = 0;

    printf("\n========================================\n");
    printf("Interval Analysis [%llu, %llu]\n", a, b);
    printf("========================================\n");

    printf("\n%-12s %-15s %-15s\n",
           "Start", "Steps", "Maximum");

    printf("------------------------------------------\n");

    for (ull i = a; i <= b; i++)
    {
        CollatzInfo info = analyzeTrajectory(i);

        printf("%-12llu %-15llu %-15llu\n",
               info.start,
               info.steps,
               info.maximum);

        totalSteps += info.steps;

        /* Find longest trajectory */
        if (info.steps > longestSteps)
        {
            longestSteps = info.steps;
            longestStart = i;
        }

        /* Find largest peak */
        if (info.maximum > largestPeak)
        {
            largestPeak = info.maximum;
            largestPeakStart = i;
        }

        /*
         * Prevent overflow when b is the largest
         * unsigned long long value.
         */
        if (i == b)
            break;
    }

    printf("\n------------------------------------------\n");

    printf("Starting value with longest trajectory : %llu\n",
           longestStart);

    printf("Longest trajectory length             : %llu steps\n",
           longestSteps);

    printf("Starting value with largest peak      : %llu\n",
           largestPeakStart);

    printf("Largest value reached                 : %llu\n",
           largestPeak);

    printf("Total steps for interval              : %llu\n",
           totalSteps);
}


/*
 * Display information about a single starting value.
 */
void analyzeSingleValue(ull n)
{
    CollatzInfo info;

    info = analyzeTrajectory(n);

    printf("\n========================================\n");
    printf("Single Value Analysis\n");
    printf("========================================\n");

    printf("Starting value       : %llu\n", info.start);
    printf("Steps to reach 1     : %llu\n", info.steps);
    printf("Maximum value reached: %llu\n", info.maximum);

    printTrajectory(n);
}


/*
 * Main function.
 */
int main()
{
    int choice;

    printf("========================================\n");
    printf("        COLLATZ CONJECTURE ANALYZER\n");
    printf("========================================\n");

    printf("\n1. Analyze a single starting value\n");
    printf("2. Analyze an interval [a,b]\n");
    printf("3. Perform both analyses\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    if (choice == 1)
    {
        ull n;

        printf("\nEnter positive integer n: ");
        scanf("%llu", &n);

        if (n == 0)
        {
            printf("Error: n must be a positive integer.\n");
            return 1;
        }

        analyzeSingleValue(n);
    }

    else if (choice == 2)
    {
        ull a, b;

        printf("\nEnter interval [a,b]: ");
        scanf("%llu %llu", &a, &b);

        if (a == 0 || b == 0 || a > b)
        {
            printf("Invalid interval.\n");
            return 1;
        }

        analyzeInterval(a, b);
    }

    else if (choice == 3)
    {
        ull n, a, b;

        printf("\nEnter starting value n: ");
        scanf("%llu", &n);

        if (n == 0)
        {
            printf("Error: n must be positive.\n");
            return 1;
        }

        analyzeSingleValue(n);

        printf("\nEnter interval [a,b]: ");
        scanf("%llu %llu", &a, &b);

        if (a == 0 || b == 0 || a > b)
        {
            printf("Invalid interval.\n");
            return 1;
        }

        analyzeInterval(a, b);
    }

    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}