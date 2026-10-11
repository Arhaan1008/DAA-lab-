
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long distance;
    long long fuel;
} Station;

Station stations[100005];
long long heap[100005];
int heapSize = 0;

int compareStations(const void *a, const void *b) {
    const Station *x = (const Station *)a;
    const Station *y = (const Station *)b;

    if (x->distance < y->distance) return -1;
    if (x->distance > y->distance) return 1;
    return 0;
}

void push(long long fuel) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] < fuel) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = fuel;
}

long long pop(void) {
    long long result = heap[1];
    long long last = heap[heapSize--];
    int i = 1, child;

    while (2 * i <= heapSize) {
        child = 2 * i;

        if (child + 1 <= heapSize &&
            heap[child + 1] > heap[child]) {
            child++;
        }

        if (last >= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return result;
}

int minimumStops(int n, long long D, long long F) {
    long long reach = F;
    int stops = 0;
    int i;

    if (F >= D)
        return 0;

    for (i = 0; i < n; i++) {
  
        while (reach < stations[i].distance) {
            if (heapSize == 0)
                return -1;

            reach += pop();
            stops++;
        }

        push(stations[i].fuel);
    }

    while (reach < D) {
        if (heapSize == 0)
            return -1;

        reach += pop();
        stops++;
    }

    return stops;
}

int main(void) {
    int n, i;
    long long D, F;

    printf("Enter target distance, initial fuel, "
           "and number of stations: ");

    if (scanf("%lld %lld %d", &D, &F, &n) != 3 ||
        D < 0 || F < 0 || n < 0 || n > 100000) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter distance and fuel for each station:\n");

    for (i = 0; i < n; i++) {
        if (scanf("%lld %lld",
                  &stations[i].distance,
                  &stations[i].fuel) != 2 ||
            stations[i].distance < 0 ||
            stations[i].distance > D ||
            stations[i].fuel < 0) {
            printf("Invalid station data.\n");
            return 1;
        }
    }

    qsort(stations, n, sizeof(Station), compareStations);

    int answer = minimumStops(n, D, F);

    if (answer == -1)
        printf("Target cannot be reached.\n");
    else
        printf("Minimum refuelling stops = %d\n", answer);

    return 0;
}
