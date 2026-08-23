#include <stdio.h>
#include <stdlib.h>

#define START 1
#define END   -1

typedef struct
{
    int point;
    int type;
} Event;

/*
 * Sort events by coordinate.
 *
 * If two events have the same coordinate,
 * START must come before END because endpoints
 * are included in intervals.
 */
int compareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    /* START (+1) before END (-1) */
    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event *events =
        malloc(2 * n * sizeof(Event));

    printf("Enter left and right endpoints:\n");

    for (int i = 0; i < n; i++)
    {
        int l, r;

        printf("Interval %d: ", i + 1);
        scanf("%d %d", &l, &r);

        events[2 * i].point = l;
        events[2 * i].type = START;

        events[2 * i + 1].point = r;
        events[2 * i + 1].type = END;
    }

    /* Sort all endpoint events */
    qsort(events, 2 * n, sizeof(Event),
          compareEvents);

    int current = 0;
    int maximum = 0;
    int bestPoint = 0;

    /*
     * Process events in sorted order.
     */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == START)
        {
            current++;

            if (current > maximum)
            {
                maximum = current;
                bestPoint = events[i].point;
            }
        }
        else
        {
            current--;
        }
    }

    printf("\nPoint with maximum overlap = %d\n",
           bestPoint);

    printf("Maximum number of intervals containing the point = %d\n",
           maximum);

    free(events);

    return 0;
}