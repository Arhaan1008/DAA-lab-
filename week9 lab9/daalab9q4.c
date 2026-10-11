
#include <stdio.h>

#define MAX 100005

long long heap[MAX];
int heapSize = 0;

void insert(long long value) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] > value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

long long extractMin(void) {
    long long minimum = heap[1];
    long long last = heap[heapSize--];
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
    int n, i;
    long long length, x, y, merged, totalCost = 0;

    printf("Enter the number of sticks: ");

    if (scanf("%d", &n) != 1 ||
        n < 1 || n >= MAX) {
        printf("Invalid number of sticks.\n");
        return 1;
    }

    printf("Enter the lengths of the sticks:\n");

    for (i = 0; i < n; i++) {
        if (scanf("%lld", &length) != 1 || length < 0) {
            printf("Invalid stick length.\n");
            return 1;
        }

        insert(length);
    }

    while (heapSize > 1) {
        x = extractMin();
        y = extractMin();

        merged = x + y;
        totalCost += merged;

        insert(merged);
    }

    printf("Minimum total connection cost = %lld\n",
           totalCost);

    return 0;
}
