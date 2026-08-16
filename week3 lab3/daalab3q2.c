#include <stdio.h>

#define GOOD_WEIGHT 10

/* Simulates the balance scale.
   Returns:
       -1 : left side is lighter
        0 : both sides are equal
        1 : right side is lighter
*/
int weigh(int a[], int left, int right, int size)
{
    int sumLeft = 0, sumRight = 0;

    for (int i = 0; i < size; i++)
    {
        sumLeft += a[left + i];
        sumRight += a[right + i];
    }

    if (sumLeft < sumRight)
        return -1;
    else if (sumLeft > sumRight)
        return 1;
    else
        return 0;
}

/* Divide-and-conquer search */
int findDefective(int a[], int low, int high)
{
    int n = high - low + 1;

    /* One candidate remains */
    if (n == 1)
    {
        if (a[low] < GOOD_WEIGHT)
            return low;
        else
            return -1;
    }

    /* Two coins */
    if (n == 2)
    {
        if (a[low] < a[high])
            return low;

        if (a[high] < a[low])
            return high;

        return -1;
    }

    int mid = low + n / 2 - 1;
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    int result;

    /*
       If the groups have equal size, compare them.
    */
    if (leftSize == rightSize)
    {
        int balance = weigh(a, low, mid + 1, leftSize);

        if (balance < 0)
            return findDefective(a, low, mid);

        else if (balance > 0)
            return findDefective(a, mid + 1, high);

        else
            return -1;
    }

    /*
       For odd n, leave one coin aside.
       Compare equal-sized groups.
    */
    else
    {
        int groupSize = n / 2;

        int balance = weigh(a, low, low + groupSize,
                           groupSize);

        if (balance < 0)
            result = findDefective(a, low, low + groupSize - 1);

        else if (balance > 0)
            result = findDefective(a, low + groupSize,
                                   low + 2 * groupSize - 1);

        else
        {
            /*
             * Both groups are equal.
             * The extra coin could be defective.
             */
            int extra = low + 2 * groupSize;

            if (a[extra] < GOOD_WEIGHT)
                result = extra;
            else
                result = -1;
        }

        return result;
    }
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter weights of %d coins:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    int defective = findDefective(coins, 0, n - 1);

    if (defective == -1)
        printf("No defective coin found.\n");
    else
        printf("Defective coin is coin %d (weight = %d).\n",
               defective + 1, coins[defective]);

    return 0;
}