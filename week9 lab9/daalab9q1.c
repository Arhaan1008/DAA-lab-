
#include <stdio.h>
#include <string.h>

#define MAX_STRINGS 105
#define MAX_TOTAL 10005

char s[MAX_STRINGS][MAX_TOTAL];
char merged[MAX_TOTAL];

int overlap(const char *a, const char *b) {
    int lenA = (int)strlen(a);
    int lenB = (int)strlen(b);
    int limit = lenA < lenB ? lenA : lenB;
    int k;

    for (k = limit; k > 0; k--) {
        if (strncmp(a + lenA - k, b, (size_t)k) == 0)
            return k;
    }

    return 0;
}

int removeContained(int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; ) {
            if (strstr(s[i], s[j]) != NULL) {
                /* s[j] is redundant */
                strcpy(s[j], s[n - 1]);
                n--;
            } else if (strstr(s[j], s[i]) != NULL) {
                /* s[i] is redundant */
                strcpy(s[i], s[n - 1]);
                n--;
                i = -1;
                break;
            } else {
                j++;
            }
        }
    }

    return n;
}

int main(void) {
    int n, i, j;
    int bestI, bestJ, bestOverlap;
    int ov, len;

    printf("Enter the number of strings: ");

    if (scanf("%d", &n) != 1 ||
        n < 1 || n >= MAX_STRINGS) {
        printf("Invalid number of strings.\n");
        return 1;
    }

    printf("Enter the strings (no spaces):\n");

    for (i = 0; i < n; i++) {
        if (scanf("%10004s", s[i]) != 1) {
            printf("Invalid string input.\n");
            return 1;
        }
    }

    n = removeContained(n);

    while (n > 1) {
        bestOverlap = -1;
        bestI = 0;
        bestJ = 1;

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i == j)
                    continue;

                ov = overlap(s[i], s[j]);

                if (ov > bestOverlap) {
                    bestOverlap = ov;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        len = (int)strlen(s[bestI]);

        strcpy(merged, s[bestI]);
        strcat(merged, s[bestJ] + bestOverlap);

        strcpy(s[bestI], merged);

        strcpy(s[bestJ], s[n - 1]);
        n--;
    }

    printf("Greedy superstring: %s\n", s[0]);
    printf("Length: %zu\n", strlen(s[0]));

    return 0;
}
