#include <stdio.h>

long long minimum_moves(long long n)
{
    return n * (n + 1) / 6;
}

int main(void)
{
    long long n;

    printf("Enter number of rows: ");
    scanf("%lld", &n);

    if (n < 1) {
        printf("Number of rows must be positive.\n");
        return 1;
    }

    long long coins = n * (n + 1) / 2;
    long long moves = minimum_moves(n);

    printf("Number of coins   : %lld\n", coins);
    printf("Minimum moves     : %lld\n", moves);

    return 0;
}