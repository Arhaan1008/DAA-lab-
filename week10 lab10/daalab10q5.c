#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

int parent[MAX], sz[MAX];

typedef struct
{
    int root;
    int index;
} Position;

typedef struct
{
    int root;
    int value;
} Value;

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
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
}

// Sort positions by root, then by index
int comparePosition(const void *a, const void *b)
{
    Position *x = (Position *)a;
    Position *y = (Position *)b;

    if (x->root != y->root)
        return (x->root > y->root) -
               (x->root < y->root);

    return (x->index > y->index) -
           (x->index < y->index);
}

// Sort values by root, then by value
int compareValue(const void *a, const void *b)
{
    Value *x = (Value *)a;
    Value *y = (Value *)b;

    if (x->root != y->root)
        return (x->root > y->root) -
               (x->root < y->root);

    return (x->value > y->value) -
           (x->value < y->value);
}

int main()
{
    int n, m;
    int A[MAX];

    Position pos[MAX];
    Value val[MAX];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid size.\n");
        return 1;
    }

    printf("Enter permutation:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    // Initialize DSU
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        sz[i] = 1;
    }

    printf("Enter number of allowed swaps: ");
    scanf("%d", &m);

    printf("Enter swap edges (0-based positions):\n");

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid edge.\n");
            return 1;
        }

        unite(u, v);
    }

    // Create position and value records
    for (int i = 0; i < n; i++)
    {
        int root = find(i);

        pos[i].root = root;
        pos[i].index = i;

        val[i].root = root;
        val[i].value = A[i];
    }

    // Sort positions and values independently
    qsort(pos, n, sizeof(Position), comparePosition);

    qsort(val, n, sizeof(Value), compareValue);

    // Assign sorted values to sorted positions
    for (int i = 0; i < n; i++)
    {
        A[pos[i].index] = val[i].value;
    }

    printf("\nLexicographically smallest permutation:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");

    return 0;
}