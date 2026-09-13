#include <stdio.h>
#include <stdint.h>

uint64_t moves = 0;
int valid = 1;

int legal(uint64_t state, int s)
{
    if (s == 1)
        return 1;

    uint64_t right_mask = (1ULL << (s - 1)) - 1;

    int immediate_right =
        (state >> (s - 2)) & 1ULL;

    int farther_right =
        state & ((1ULL << (s - 2)) - 1);

    return immediate_right && farther_right == 0;
}
void toggle(uint64_t *state, int s, int n)
{
    if (!legal(*state, s)) {
        printf("ERROR: illegal move: switch %d\n", s);
        valid = 0;
        return;
    }

    *state ^= (1ULL << (s - 1));
    moves++;

    printf("Move %llu: switch %d\n",
           (unsigned long long)moves, s);
}

    if (k == 0)
        return;

    gray(k - 1, state, n);
    toggle(state, k, n);
    gray(k - 1, state, n);
}
void solve(int n, uint64_t *state)
{
    if (n == 0)
        return;

    if (n == 1) {
        toggle(state, 1, n);
        return;
    }

    solve(n - 2, state);

    toggle(state, n, n);

    gray(n - 1, state, n);
}

int main(void)
{
    int n;
    uint64_t state;

    printf("Enter number of switches (1-63): ");
    scanf("%d", &n);

    if (n < 1 || n > 63) {
        printf("Invalid input.\n");
        return 1;
    }
    state = (1ULL << n) - 1;

    printf("\nInitial state: ");
    for (int i = n - 1; i >= 0; i--)
        printf("%llu", (state >> i) & 1ULL);

    printf("\n\n");

    solve(n, &state);

    printf("\nFinal state:   ");
    for (int i = n - 1; i >= 0; i--)
        printf("%llu", (state >> i) & 1ULL);

    printf("\n");
    printf("Moves made: %llu\n",
           (unsigned long long)moves);

    if (state == 0 && valid)
        printf("VALID: all switches are OFF.\n");
    else
        printf("INVALID solution.\n");

    return 0;
}