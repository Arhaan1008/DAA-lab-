#include <stdio.h>

#define MAX 10000

int parent[MAX], size[MAX];

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

int unite(int x, int y)
{
    int rx = find(x);
    int ry = find(y);

    if (rx == ry)
        return 0;

    if (size[rx] < size[ry])
    {
        int temp = rx;
        rx = ry;
        ry = temp;
    }

    parent[ry] = rx;
    size[rx] += size[ry];

    return 1;
}

int main()
{
    int R, C, k;
    int islands = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("Enter rows and columns: ");
    scanf("%d %d", &R, &C);

    if (R <= 0 || C <= 0 || R * C > MAX)
    {
        printf("Invalid grid size.\n");
        return 1;
    }

    int total = R * C;

    for (int i = 0; i < total; i++)
    {
        parent[i] = -1;
        size[i] = 0;
    }

    printf("Enter number of land additions: ");
    scanf("%d", &k);

    printf("Enter land positions (row column, 0-based):\n");

    for (int i = 0; i < k; i++)
    {
        int r, c;
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= R || c < 0 || c >= C)
        {
            printf("Invalid position. Islands = %d\n", islands);
            continue;
        }

        int id = r * C + c;

        // Already land
        if (parent[id] != -1)
        {
            printf("Islands = %d\n", islands);
            continue;
        }

        // Create a new island
        parent[id] = id;
        size[id] = 1;
        islands++;

        // Check four directions
        for (int d = 0; d < 4; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < R &&
                nc >= 0 && nc < C)
            {
                int nid = nr * C + nc;

                if (parent[nid] != -1)
                {
                    if (unite(id, nid))
                        islands--;
                }
            }
        }

        printf("Islands = %d\n", islands);
    }

    return 0;
}