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
int active[MAX];

int head[MAX], to[2 * MAX], nextEdge[2 * MAX];
int edgeCount = 0;

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
        int l = 2 * i;
        int r = l + 1;
        int largest = i;

        if (l <= heapSize &&
            heap[l].sum > heap[largest].sum)
            largest = l;

        if (r <= heapSize &&
            heap[r].sum > heap[largest].sum)
            largest = r;

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

void addEdge(int u, int v)
{
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount++;

    to[edgeCount] = u;
    nextEdge[edgeCount] = head[v];
    head[v] = edgeCount++;
}

void insertComponent(int root)
{
    Item x;

    x.sum = weight[root];
    x.root = root;
    x.version = version[root];

    push(x);
}

void unite(int u, int v)
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

    insertComponent(ru);
}

long long getMaximum()
{
    while (heapSize > 0)
    {
        Item x = heap[1];

        if (parent[x.root] == x.root &&
            active[x.root] &&
            version[x.root] == x.version &&
            weight[x.root] == x.sum)
        {
            return x.sum;
        }

        pop();
    }

    return 0;
}

int main()
{
    int V, E;

    printf("Enter vertices and edges: ");
    scanf("%d %d", &V, &E);

    if (V <= 0 || V > MAX || E < 0 || E > MAX)
    {
        printf("Invalid input.\n");
        return 1;
    }

    heap = malloc((2 * V + 5) * sizeof(Item));

    if (heap == NULL)
        return 1;

    for (int i = 0; i < V; i++)
    {
        parent[i] = -1;
        sz[i] = 0;
        version[i] = 0;
        active[i] = 0;
        head[i] = -1;
    }

    printf("Enter vertex weights:\n");

    for (int i = 0; i < V; i++)
        scanf("%lld", &weight[i]);

    printf("Enter edges (0-based vertices):\n");

    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            printf("Invalid edge.\n");
            free(heap);
            return 1;
        }

        addEdge(u, v);
    }

    int P[MAX];
    long long answer[MAX + 1];

    printf("Enter deletion order (0-based):\n");

    for (int i = 0; i < V; i++)
        scanf("%d", &P[i]);

    // Empty graph: answer after V deletions
    answer[V] = 0;

    // Process deletions in reverse
    for (int i = V - 1; i >= 0; i--)
    {
        // Record answer after i+1 forward deletions
        answer[i + 1] = getMaximum();

        int u = P[i];

        if (u < 0 || u >= V || active[u])
        {
            printf("Invalid deletion permutation.\n");
            free(heap);
            return 1;
        }

        // Activate vertex
        active[u] = 1;
        parent[u] = u;
        sz[u] = 1;
        version[u]++;

        insertComponent(u);

        // Merge with active neighbors
        for (int e = head[u]; e != -1; e = nextEdge[e])
        {
            int v = to[e];

            if (active[v])
                unite(u, v);
        }
    }

    printf("\nMaximum component weights after deletions:\n");

    for (int i = 1; i <= V; i++)
        printf("After deleting %d vertices: %lld\n", i, answer[i]);

    free(heap);

    return 0;
}