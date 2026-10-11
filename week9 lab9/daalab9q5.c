
#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

int main(void) {
    int n, i;
    int rating[MAX];
    int candy[MAX];
    long long total = 0;

    printf("Enter the number of children: ");

    if (scanf("%d", &n) != 1 || n < 1 || n >= MAX) {
        printf("Invalid number of children.\n");
        return 1;
    }

    printf("Enter the ratings of the children:\n");

    for (i = 0; i < n; i++) {
        if (scanf("%d", &rating[i]) != 1) {
            printf("Invalid rating.\n");
            return 1;
        }
        candy[i] = 1;
    }

    for (i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1]) {
            candy[i] = candy[i - 1] + 1;
        }
    }

    for (i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] &&
            candy[i] <= candy[i + 1]) {
            candy[i] = candy[i + 1] + 1;
        }
    }

    for (i = 0; i < n; i++) {
        total += candy[i];
    }

    printf("Candies given to each child:\n");

    for (i = 0; i < n; i++) {
        printf("%d ", candy[i]);
    }

    printf("\nMinimum total candies = %lld\n", total);

    return 0;
}
