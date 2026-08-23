#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    RED,
    BLUE,
    YELLOW
} Color;

typedef struct
{
    int number;
    Color color;
} Item;

/* Convert color to string */
const char *colorName(Color color)
{
    switch (color)
    {
        case RED:
            return "Red";

        case BLUE:
            return "Blue";

        case YELLOW:
            return "Yellow";
    }

    return "Unknown";
}

/*
 * Sort items by color while preserving
 * the number order within each color.
 */
void sortByColor(Item A[], int n)
{
    Item *red = malloc(n * sizeof(Item));
    Item *blue = malloc(n * sizeof(Item));
    Item *yellow = malloc(n * sizeof(Item));

    int r = 0, b = 0, y = 0;

    /* Partition into three arrays */
    for (int i = 0; i < n; i++)
    {
        if (A[i].color == RED)
            red[r++] = A[i];

        else if (A[i].color == BLUE)
            blue[b++] = A[i];

        else
            yellow[y++] = A[i];
    }

    /* Combine: Red -> Blue -> Yellow */
    int k = 0;

    for (int i = 0; i < r; i++)
        A[k++] = red[i];

    for (int i = 0; i < b; i++)
        A[k++] = blue[i];

    for (int i = 0; i < y; i++)
        A[k++] = yellow[i];

    free(red);
    free(blue);
    free(yellow);
}

void printItems(Item A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("(%d, %s)\n",
               A[i].number,
               colorName(A[i].color));
}

int main()
{
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item *A = malloc(n * sizeof(Item));

    printf("\nEnter items in increasing order of number.\n");
    printf("Use 0 = Red, 1 = Blue, 2 = Yellow\n\n");

    for (int i = 0; i < n; i++)
    {
        int color;

        printf("Enter number and color for item %d: ",
               i + 1);

        scanf("%d %d", &A[i].number, &color);

        A[i].color = (Color)color;
    }

    printf("\nOriginal items:\n");
    printItems(A, n);

    sortByColor(A, n);

    printf("\nItems sorted by color:\n");
    printItems(A, n);

    free(A);

    return 0;
}