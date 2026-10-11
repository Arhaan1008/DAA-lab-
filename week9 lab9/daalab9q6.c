
#include <stdio.h>
#include <string.h>

#define MAX_LEN 10005
#define ALPHABET 256

typedef struct {
    unsigned char ch;
    int freq;
} Node;

typedef struct {
    unsigned char ch;
    int freq;
    int readyAt;
} Waiting;

Node heap[ALPHABET + 5];
Waiting waiting[MAX_LEN];

int heapSize = 0;

int higherPriority(Node a, Node b) {
    if (a.freq != b.freq)
        return a.freq > b.freq;

    return a.ch < b.ch;
}

void push(Node value) {
    int i = ++heapSize;

    while (i > 1 &&
           higherPriority(value, heap[i / 2])) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

Node pop(void) {
    Node result = heap[1];
    Node last = heap[heapSize--];
    int i = 1, child;

    while (2 * i <= heapSize) {
        child = 2 * i;

        if (child + 1 <= heapSize &&
            higherPriority(heap[child + 1], heap[child])) {
            child++;
        }

        if (higherPriority(last, heap[child]))
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return result;
}

int main(void) {
    char s[MAX_LEN], result[MAX_LEN];
    int count[ALPHABET] = {0};
    int n, k, i;
    int front = 0, rear = 0, out = 0;

    printf("Enter the string: ");

    if (scanf("%10004s", s) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter K: ");

    if (scanf("%d", &k) != 1 || k < 0) {
        printf("Invalid K value.\n");
        return 1;
    }

    n = (int)strlen(s);

    if (k <= 1) {
        printf("Reorganised string = %s\n", s);
        return 0;
    }

    for (i = 0; i < n; i++)
        count[(unsigned char)s[i]]++;

    for (i = 0; i < ALPHABET; i++) {
        if (count[i] > 0) {
            Node item;
            item.ch = (unsigned char)i;
            item.freq = count[i];
            push(item);
        }
    }

    for (i = 0; i < n; i++) {
      
        while (front < rear && waiting[front].readyAt <= i) {
            Node item;
            item.ch = waiting[front].ch;
            item.freq = waiting[front].freq;
            push(item);
            front++;
        }

        if (heapSize == 0) {
            printf("Reorganised string = \"\"\n");
            return 0;
        }

        Node current = pop();
        result[out++] = (char)current.ch;
        current.freq--;

        if (current.freq > 0) {
            waiting[rear].ch = current.ch;
            waiting[rear].freq = current.freq;
            waiting[rear].readyAt = i + k;
            rear++;
        }
    }

    result[out] = '\0';

    printf("Reorganised string = %s\n", result);

    return 0;
}
