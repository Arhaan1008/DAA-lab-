#include <stdio.h>

#define MAX_N 1000

void print_possible(int possible[], int n)
{
    printf("{ ");

    for (int i = 1; i <= n; i++) {
        if (possible[i])
            printf("%d ", i);
    }

    printf("}");
}
void apply_shot(int possible[], int n, int shot)
{
    int next[MAX_N + 1] = {0};

    possible[shot] = 0;

    for (int i = 1; i <= n; i++) {
        if (possible[i]) {

            if (i > 1)
                next[i - 1] = 1;

            if (i < n)
                next[i + 1] = 1;
        }
    }

    for (int i = 1; i <= n; i++)
        possible[i] = next[i];
}

int main(void)
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1 || n > MAX_N) {
        printf("Invalid value of n.\n");
        return 1;
    }

    int possible[MAX_N + 1] = {0};

    for (int i = 1; i <= n; i++)
        possible[i] = 1;

    printf("\nInitial possible positions: ");
    print_possible(possible, n);
    printf("\n\n");

    if (n == 2) {

        printf("Shot at 1\n");
        apply_shot(possible, n, 1);

        printf("Possible positions: ");
        print_possible(possible, n);
        printf("\n");

        printf("Shot at 2\n");
        apply_shot(possible, n, 2);

    } else if (n % 2 == 1) {

        for (int pass = 0; pass < 2; pass++) {

            for (int shot = 2; shot <= n - 1; shot++) {

                printf("Shot at %d\n", shot);

                apply_shot(possible, n, shot);

                printf("Possible positions: ");
                print_possible(possible, n);
                printf("\n");

                if (pass == 1 && shot == n - 1)
                    break;
            }
        }

    } else {

        for (int shot = 2; shot <= n - 1; shot++) {

            printf("Shot at %d\n", shot);

            apply_shot(possible, n, shot);

            printf("Possible positions: ");
            print_possible(possible, n);
            printf("\n");
        }

        for (int shot = n - 1; shot >= 2; shot--) {

            printf("Shot at %d\n", shot);

            apply_shot(possible, n, shot);

            printf("Possible positions: ");
            print_possible(possible, n);
            printf("\n");
        }
    }

    int remaining = 0;

    for (int i = 1; i <= n; i++) {
        if (possible[i])
            remaining++;
    }

    printf("\n--------------------------------\n");

    if (remaining == 0)
        printf("VALID: target is guaranteed to be hit.\n");
    else
        printf("INVALID: target may still be alive.\n");

    if (n == 2)
        printf("Number of shots = 2\n");
    else
        printf("Number of shots = %d\n", 2 * n - 4);

    return 0;
}