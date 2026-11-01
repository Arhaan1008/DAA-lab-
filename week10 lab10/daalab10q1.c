#include <stdio.h>

#define MAX 1000

int parent[MAX], size[MAX], parity[MAX];

int find(int x, int *p)
{
    if (parent[x] == x)
    {
        *p = 0;
        return x;
    }

    int oldParent = parent[x];
    int parentParity;

    int root = find(oldParent, &parentParity);

    parity[x] ^= parentParity;
    parent[x] = root;

    *p = parity[x];

    return root;
}

int addEdge(int u, int v)
{
    int pu, pv;

    int ru = find(u, &pu);
    int rv = find(v, &pv);

    // Both vertices are already connected
    if (ru == rv)
    {
        return ((pu ^ pv) == 1);
    }

    // Union by size
    if (size[ru] < size[rv])
    {
        int temp = ru;
        ru = rv;
        rv = temp;
    }

    parent[rv] = ru;

    // The new edge requires opposite colors
    parity[rv] = pu ^ pv ^ 1;

    size[ru] += size[rv];

    return 1;
}

int main()
{
    int V, E, u, v;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    if (V <= 0 || V > MAX || E < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
        size[i] = 1;
        parity[i] = 0;
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

        if (addEdge(u, v))
        {
            printf("Edge (%d,%d) ACCEPTED\n", u, v);
        }
        else
        {
            printf("Edge (%d,%d) REJECTED: Odd cycle\n", u, v);
        }
    }

    return 0;
}