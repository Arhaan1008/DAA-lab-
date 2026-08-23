#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int time;
    int type;       // +1 = entry, -1 = exit
} Event;

/* Compare two events by time */
int compareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    return e1->time - e2->time;
}

int main()
{
    int n;

    printf("Enter number of persons: ");
    scanf("%d", &n);

    Event *events = malloc(2 * n * sizeof(Event));

    printf("\nEnter entry and exit time for each person:\n");

    for (int i = 0; i < n; i++)
    {
        int entry, exit;

        printf("Person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        events[2 * i].time = entry;
        events[2 * i].type = +1;

        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    /* Sort all events according to time */
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int current = 0;
    int maximum = 0;
    int maxTime = -1;

    /* Scan the sorted events */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == +1)
        {
            current++;

            if (current > maximum)
            {
                maximum = current;
                maxTime = events[i].time;
            }
        }
        else
        {
            current--;
        }
    }

    printf("\nMaximum number of people present = %d\n",
           maximum);

    printf("Time when maximum was first reached = %d\n",
           maxTime);

    free(events);

    return 0;
}