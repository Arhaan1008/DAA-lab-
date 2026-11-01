#include <stdio.h>
#include <stdlib.h>

#define MAXV 100000
#define MAXE 200000

int head[MAXV];
int to[2 * MAXE];
int nextEdge[2 * MAXE];
int edgeCount = 0;

int dist[MAXV];
int owner[MAXV];

int queue[MAXV];

void addEdge(int u, int v)
{
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount++;

    to[edgeCount] = u;
    nextEdge[edgeCount] = head[v];
    head[v] = edgeCount++;
}

void multiSourceBFS(int V, int hubs[], int K, int R)
{
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++)
    {
        dist[i] = -1;
        owner[i] = -1;
    }

    // Insert hubs in increasing index order
    for (int i = 0; i < K; i++)
    {
        int h = hubs[i];

        if (dist[h] == -1)
        {
            dist[h] = 0;
            owner[h] = i + 1;
            queue[rear++] = h;
        }
    }

    while (front < rear)
    {
        int u = queue[front++];

        // Do not expand beyond the radius
        if (dist[u] == R)
            continue;

        for (int e = head[u]; e != -1; e = nextEdge[e])
        {
            int v = to[e];

            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];

                queue[rear++] = v;
            }
        }
    }
}

int main()
{
    int V, E, K, R;

    printf("Enter vertices and edges: ");
    scanf("%d %d", &V, &E);

    if (V <= 0 || V > MAXV || E < 0 || E > MAXE)
    {
        printf("Invalid graph size.\n");
        return 1;
    }

    for (int i = 0; i < V; i++)
        head[i] = -1;

    printf("Enter undirected edges (u v):\n");

    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            printf("Invalid edge.\n");
            return 1;
        }

        addEdge(u, v);
    }

    printf("Enter number of hubs: ");
    scanf("%d", &K);

    if (K < 0 || K > V)
    {
        printf("Invalid number of hubs.\n");
        return 1;
    }

    int *hubs = malloc(K * sizeof(int));

    if (K > 0 && hubs == NULL)
        return 1;

    printf("Enter hub vertices in increasing priority order:\n");

    for (int i = 0; i < K; i++)
    {
        scanf("%d", &hubs[i]);

        if (hubs[i] < 0 || hubs[i] >= V)
        {
            printf("Invalid hub.\n");
            free(hubs);
            return 1;
        }

        for (int j = 0; j < i; j++)
        {
            if (hubs[i] == hubs[j])
            {
                printf("Duplicate hub.\n");
                free(hubs);
                return 1;
            }
        }
    }

    printf("Enter radius R: ");
    scanf("%d", &R);

    if (R < 0)
    {
        printf("Invalid radius.\n");
        free(hubs);
        return 1;
    }

    multiSourceBFS(V, hubs, K, R);

    printf("\nVertex\tOwner\tDistance\n");

    for (int i = 0; i < V; i++)
    {
        printf("%d\t%d\t", i, owner[i]);

        if (dist[i] == -1)
            printf("Unreachable\n");
        else if (dist[i] > R)
            printf("Beyond radius\n");
        else
            printf("%d\n", dist[i]);
    }

    free(hubs);

    return 0;
}