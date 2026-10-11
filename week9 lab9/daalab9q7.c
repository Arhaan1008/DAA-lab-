
#include <stdio.h>
#include <limits.h>

#define MAX 100005

long long heap[MAX];
int heapSize = 0;
void insert(long long value) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] < value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}
long long extractMax(void) {
    long long maximum = heap[1];
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

    return maximum;
}

int main(void) {
    int n, i;
    long long x, currentMin = LLONG_MAX;
    long long bestDeviation, currentDeviation;

    printf("Enter the number of elements: ");

    if (scanf("%d", &n) != 1 || n < 1 || n >= MAX) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter positive array elements:\n");

    for (i = 0; i < n; i++) {
        if (scanf("%lld", &x) != 1 || x <= 0 ||
            (x % 2 != 0 && x > LLONG_MAX / 2)) {
            printf("Invalid element.\n");
            return 1;
        }

        if (x % 2 != 0)
            x *= 2;

        insert(x);

        if (x < currentMin)
            currentMin = x;
    }
    if (n == 1) {
        printf("Minimum deviation = 0\n");
        return 0;
    }

    bestDeviation = heap[1] - currentMin;

    while (1) {
        long long maximum = extractMax();

        currentDeviation = maximum - currentMin;

        if (currentDeviation < bestDeviation)
            bestDeviation = currentDeviation;

        if (maximum % 2 != 0)
            break;

        long long reduced = maximum / 2;

        if (reduced < currentMin)
            currentMin = reduced;

        insert(reduced);

        currentDeviation = heap[1] - currentMin;

        if (currentDeviation < bestDeviation)
            bestDeviation = currentDeviation;
    }

    printf("Minimum deviation = %lld\n", bestDeviation);

    return 0;
}
