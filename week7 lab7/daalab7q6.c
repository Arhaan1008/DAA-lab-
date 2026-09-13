#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int year;
    int type;      
} Event;

int compare_events(const void *a, const void *b)
{
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;

    if (e1->year != e2->year)
        return e1->year - e2->year;

    return e1->type - e2->type;
}

int main(void)
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of scientists.\n");
        return 1;
    }

    Event *events = malloc(2 * n * sizeof(Event));

    if (events == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    char name[100];
    int birth, death;

    for (int i = 0; i < n; i++) {

        scanf("%99s %d %d",
              name, &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = +1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(Event), compare_events);

    int alive = 0;
    int maximum = 0;
    int bestYear = 0;

    printf("\nSorted events:\n");

    for (int i = 0; i < 2 * n; i++) {

        if (events[i].type == -1) {
            alive--;
            printf("%d  death   alive = %d\n",
                   events[i].year, alive);
        }
        else {
            alive++;
            printf("%d  birth   alive = %d\n",
                   events[i].year, alive);
        }

        if (alive > maximum) {
            maximum = alive;
            bestYear = events[i].year;
        }
    }

    printf("\nMaximum scientists alive = %d\n",
           maximum);

    printf("Best year = %d\n",
           bestYear);

    free(events);

    return 0;
}