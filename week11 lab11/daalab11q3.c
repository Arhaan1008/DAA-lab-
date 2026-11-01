#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXL 10
#define HASH_SIZE (1 << 20)

char words[MAXN][MAXL + 1];

int hashTable[HASH_SIZE];

int distA[MAXN], distB[MAXN];

int frontA[MAXN], frontB[MAXN];
int nextA[MAXN], nextB[MAXN];

int countA, countB;

/* Hash function */
unsigned int hashFunction(const char *s)
{
    unsigned int h = 2166136261u;

    while (*s)
    {
        h ^= (unsigned char)*s++;
        h *= 16777619u;
    }

    return h & (HASH_SIZE - 1);
}

/* Find a word in the hash table */
int searchWord(const char *s)
{
    unsigned int h = hashFunction(s);

    while (hashTable[h] != -1)
    {
        int id = hashTable[h];

        if (strcmp(words[id], s) == 0)
            return id;

        h = (h + 1) & (HASH_SIZE - 1);
    }

    return -1;
}

/* Insert a word into the hash table */
void insertWord(int id)
{
    unsigned int h = hashFunction(words[id]);

    while (hashTable[h] != -1)
        h = (h + 1) & (HASH_SIZE - 1);

    hashTable[h] = id;
}

/*
   Expand one complete BFS level.
   Returns shortest path length if the searches meet,
   otherwise -1.
*/
int expandFrontier(
    int *frontier,
    int *frontierCount,
    int *nextFrontier,
    int *ownDist,
    int *otherDist,
    int L,
    int totalWords)
{
    int nextCount = 0;

    for (int i = 0; i < *frontierCount; i++)
    {
        int u = frontier[i];

        char temp[MAXL + 1];
        strcpy(temp, words[u]);

        for (int pos = 0; pos < L; pos++)
        {
            char original = temp[pos];

            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                if (ch == original)
                    continue;

                temp[pos] = ch;

                int v = searchWord(temp);

                if (v == -1)
                    continue;

                // Searches have met
                if (otherDist[v] != -1)
                {
                    return ownDist[u] + 1 + otherDist[v];
                }

                if (ownDist[v] == -1)
                {
                    ownDist[v] = ownDist[u] + 1;

                    nextFrontier[nextCount++] = v;
                }
            }

            temp[pos] = original;
        }
    }

    *frontierCount = nextCount;

    for (int i = 0; i < nextCount; i++)
        frontier[i] = nextFrontier[i];

    return -1;
}

int bidirectionalBFS(int start, int target, int L, int totalWords)
{
    if (start == target)
        return 0;

    for (int i = 0; i < totalWords; i++)
    {
        distA[i] = -1;
        distB[i] = -1;
    }

    distA[start] = 0;
    distB[target] = 0;

    frontA[0] = start;
    frontB[0] = target;

    countA = 1;
    countB = 1;

    while (countA > 0 && countB > 0)
    {
        int answer;

        if (countA <= countB)
        {
            answer = expandFrontier(
                frontA, &countA, nextA,
                distA, distB, L, totalWords
            );
        }
        else
        {
            answer = expandFrontier(
                frontB, &countB, nextB,
                distB, distA, L, totalWords
            );
        }

        if (answer != -1)
            return answer;
    }

    return -1;
}

int main()
{
    int N;
    char A[MAXL + 1], B[MAXL + 1];

    for (int i = 0; i < HASH_SIZE; i++)
        hashTable[i] = -1;

    printf("Enter number of dictionary words: ");
    scanf("%d", &N);

    if (N <= 0 || N >= MAXN)
    {
        printf("Invalid dictionary size.\n");
        return 1;
    }

    printf("Enter dictionary words:\n");

    int L = -1;

    for (int i = 0; i < N; i++)
    {
        scanf("%10s", words[i]);

        int len = strlen(words[i]);

        if (L == -1)
            L = len;

        if (len != L || len == 0)
        {
            printf("Invalid word length.\n");
            return 1;
        }

        insertWord(i);
    }

    printf("Enter starting word A: ");
    scanf("%10s", A);

    printf("Enter target word B: ");
    scanf("%10s", B);

    if ((int)strlen(A) != L || (int)strlen(B) != L)
    {
        printf("Starting and target words must have length %d.\n", L);
        return 1;
    }

    // Target must be in dictionary
    int target = searchWord(B);

    if (target == -1)
    {
        printf("Minimum mutations = -1\n");
        return 0;
    }

    // Starting word may or may not be in dictionary
    int start = searchWord(A);

    int totalWords = N;

    if (start == -1)
    {
        start = totalWords;

        strcpy(words[totalWords], A);
        insertWord(totalWords);

        totalWords++;
    }

    if (start == target)
    {
        printf("Minimum mutations = 0\n");
        return 0;
    }

    int result = bidirectionalBFS(
        start, target, L, totalWords
    );

    printf("Minimum mutations = %d\n", result);

    return 0;
}