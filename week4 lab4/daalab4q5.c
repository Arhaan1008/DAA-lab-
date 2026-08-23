#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start;
    int end;
} Interval;

/* Compare intervals by starting point */
int compareIntervals(const void *a, const void *b)
{
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;

    return i1->start - i2->start;
}

/* Merge overlapping intervals */
int mergeIntervals(Interval intervals[], int n,
                    Interval result[])
{
    if (n == 0)
        return 0;

    /* Sort by starting point */
    qsort(intervals, n, sizeof(Interval),
          compareIntervals);

    int resultCount = 0;

    int currentStart = intervals[0].start;
    int currentEnd = intervals[0].end;

    for (int i = 1; i < n; i++)
    {
        /*
         * Intervals overlap if the next interval
         * starts before or exactly when the current
         * interval ends.
         */
        if (intervals[i].start <= currentEnd)
        {
            if (intervals[i].end > currentEnd)
                currentEnd = intervals[i].end;
        }
        else
        {
            /* Save the completed interval */
            result[resultCount].start = currentStart;
            result[resultCount].end = currentEnd;
            resultCount++;

            /* Start a new interval */
            currentStart = intervals[i].start;
            currentEnd = intervals[i].end;
        }
    }

    /* Save the final interval */
    result[resultCount].start = currentStart;
    result[resultCount].end = currentEnd;
    resultCount++;

    return resultCount;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval *intervals =
        malloc(n * sizeof(Interval));

    Interval *result =
        malloc(n * sizeof(Interval));

    printf("Enter the intervals (start end):\n");

    for (int i = 0; i < n; i++)
    {
        printf("Interval %d: ", i + 1);
        scanf("%d %d",
              &intervals[i].start,
              &intervals[i].end);
    }

    int resultCount =
        mergeIntervals(intervals, n, result);

    printf("\nMerged intervals:\n");

    printf("{");

    for (int i = 0; i < resultCount; i++)
    {
        printf("(%d,%d)",
               result[i].start,
               result[i].end);

        if (i < resultCount - 1)
            printf(", ");
    }

    printf("}\n");

    free(intervals);
    free(result);

    return 0;
}