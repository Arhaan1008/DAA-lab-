#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXV 10000
#define MAXE 100000
#define INF LLONG_MAX

typedef struct {
    int to;
    int weight;
    int next;
} Edge;

typedef struct {
    int vertex;
    int parity;
} State;

Edge edges[2 * MAXE];
int head[MAXV];
int edgeCount = 0;

State deque[4 * MAXE + 10];
int front = 0, rear = 0;
int capacity = 4 * MAXE + 10;

long long dist[MAXV][2];

void addEdge(int u, int v, int w)
{
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void pushFront(State s)
{
    front = (front - 1 + capacity) % capacity;
    deque[front] = s;
}

void pushBack(State s)
{
    deque[rear] = s;
    rear = (rear + 1) % capacity;
}

State popFront()
{
    State s = deque[front];
    front = (front + 1) % capacity;
    return s;
}

int isEmpty()
{
    return front == rear;
}

void zeroOneBFS(int V, int source)
{
    for (int i = 0; i < V; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    dist[source][0] = 0;

    front = rear = 0;

    State start = {source, 0};
    pushFront(start);

    while (!isEmpty())
    {
        State cur = popFront();

        int u = cur.vertex;
        int parity = cur.parity;

        for (int e = head[u]; e != -1; e = edges[e].next)
        {
            int v = edges[e].to;
            int w = edges[e].weight;

            int newParity = parity ^ w;

            long long newDist = dist[u][parity] + w;

            if (newDist < dist[v][newParity])
            {
                dist[v][newParity] = newDist;

                State next = {v, newParity};

                if (w == 0)
                    pushFront(next);
                else
                    pushBack(next);
            }
        }
    }
}

int main()
{
    int V, E, source;
    long long C;

    printf("Enter vertices and edges: ");
    scanf("%d %d", &V, &E);

    if (V <= 0 || V > MAXV || E < 0 || E > MAXE)
    {
        printf("Invalid graph size.\n");
        return 1;
    }

    for (int i = 0; i < V; i++)
        head[i] = -1;

    printf("Enter directed edges (u v weight):\n");

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        if (u < 0 || u >= V || v < 0 || v >= V ||
            (w != 0 && w != 1))
        {
            printf("Invalid edge.\n");
            return 1;
        }

        addEdge(u, v, w);
    }

    printf("Enter source and penalty C: ");
    scanf("%d %lld", &source, &C);

    if (source < 0 || source >= V || C < 0)
    {
        printf("Invalid source or penalty.\n");
        return 1;
    }

    zeroOneBFS(V, source);

    printf("\nMinimum effective costs:\n");

    for (int i = 0; i < V; i++)
    {
        if (dist[i][0] == INF && dist[i][1] == INF)
        {
            printf("Vertex %d: Unreachable\n", i);
        }
        else
        {
            long long evenCost = dist[i][0];
            long long oddCost =
                (dist[i][1] == INF || C > INF - dist[i][1])
                ? INF : dist[i][1] + C;

            long long answer =
                evenCost < oddCost ? evenCost : oddCost;

            printf("Vertex %d: %lld\n", i, answer);
        }
    }

    return 0;
}