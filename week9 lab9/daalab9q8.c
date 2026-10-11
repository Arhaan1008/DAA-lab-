
#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

typedef struct {
    int start;
    int end;
} Meeting;

Meeting meetings[MAX];
int heap[MAX];
int heapSize = 0;

int compareMeetings(const void *a, const void *b) {
    const Meeting *x = (const Meeting *)a;
    const Meeting *y = (const Meeting *)b;

    if (x->start < y->start) return -1;
    if (x->start > y->start) return 1;
    if (x->end < y->end) return -1;
    if (x->end > y->end) return 1;
    return 0;
}

void insert(int value) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] > value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

int extractMin(void) {
    int minimum = heap[1];
    int last = heap[heapSize--];
    int i = 1, child;

    while (2 * i <= heapSize) {
        child = 2 * i;

        if (child + 1 <= heapSize &&
            heap[child + 1] < heap[child]) {
            child++;
        }

        if (last <= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return minimum;
}

int main(void) {
    int n, i, maxRooms = 0;

    printf("Enter the number of meetings: ");

    if (scanf("%d", &n) != 1 || n < 0 || n >= MAX) {
        printf("Invalid number of meetings.\n");
        return 1;
    }

    printf("Enter start and end times of each meeting:\n");

    for (i = 0; i < n; i++) {
        if (scanf("%d %d",
                  &meetings[i].start,
                  &meetings[i].end) != 2 ||
            meetings[i].start >= meetings[i].end) {
            printf("Invalid meeting interval.\n");
            return 1;
        }
    }

    if (n == 0) {
        printf("Minimum number of rooms = 0\n");
        return 0;
    }

    qsort(meetings, n, sizeof(Meeting), compareMeetings);

    for (i = 0; i < n; i++) {
        while (heapSize > 0 &&
               heap[1] <= meetings[i].start) {
            extractMin();
        }

        insert(meetings[i].end);

        if (heapSize > maxRooms)
            maxRooms = heapSize;
    }

    printf("Minimum number of rooms = %d\n", maxRooms);

    return 0;
}
