#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

typedef struct
{
    long long sum;
    int root;
    int version;
} Item;

int parent[MAX], sz[MAX], version[MAX];
long long weight[MAX];

Item *heap;
int heapSize = 0;

void swap(Item *a, Item *b)
{
    Item t = *a;
    *a = *b;
    *b = t;
}

void push(Item x)
{
    int i = ++heapSize;
    heap[i] = x;

    while (i > 1 && heap[i].sum > heap[i / 2].sum)
    {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

Item pop()
{
    Item result = heap[1];
    heap[1] = heap[heapSize--];

    int i = 1;

    while (1)
    {
        int left = 2 * i;
        int right = left + 1;
        int largest = i;

        if (left <= heapSize &&
            heap[left].sum > heap[largest].sum)
            largest = left;

        if (right <= heapSize &&
            heap[right].sum > heap[largest].sum)
            largest = right;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return result;
}

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void insertComponent(int root, int K)
{
    if (sz[root] <= K)
    {
        Item x;

        x.sum = weight[root];
        x.root = root;
        x.version = version[root];

        push(x);
    }
}

void unite(int u, int v, int K)
{
    int ru = find(u);
    int rv = find(v);

    if (ru == rv)
        return;

    if (sz[ru] < sz[rv])
    {
        int temp = ru;
        ru = rv;
        rv = temp;
    }

    parent[rv] = ru;

    sz[ru] += sz[rv];
    weight[ru] += weight[rv];

    version[ru]++;

    insertComponent(ru, K);
}

int getMaximum(int K, long long *answer)
{
    while (heapSize > 0)
    {
        Item x = heap[1];

        if (parent[x.root] == x.root &&
            version[x.root] == x.version &&
            sz[x.root] <= K &&
            weight[x.root] == x.sum)
        {
            *answer = x.sum;
            return 1;
        }

        pop();
    }

    return 0;
}

int main()
{
    int V, E, K;
    int u, v;

    printf("Enter vertices, edges and K: ");
    scanf("%d %d %d", &V, &E, &K);

    if (V <= 0 || V > MAX || E < 0 || K < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    heap = malloc((V + E + 5) * sizeof(Item));

    if (heap == NULL)
        return 1;

    printf("Enter vertex weights:\n");

    for (int i = 0; i < V; i++)
    {
        scanf("%lld", &weight[i]);

        parent[i] = i;
        sz[i] = 1;
        version[i] = 0;

        insertComponent(i, K);
    }

    printf("Enter edges (0-based vertices):\n");

    for (int i = 0; i < E; i++)
    {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            printf("Invalid edge.\n");
            continue;
        }

        unite(u, v, K);

        long long answer;

        printf("After edge (%d,%d): ", u, v);

        if (getMaximum(K, &answer))
            printf("Maximum component weight = %lld\n", answer);
        else
            printf("No eligible component\n");
    }

    free(heap);

    return 0;
}