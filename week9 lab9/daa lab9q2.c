
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define MAX_CODE 512

typedef struct {
    char symbol;
    long long freq;
    int left, right;
    char minSymbol;
} Node;

typedef struct {
    char symbol;
    int length;
    char code[MAX_CODE];
} Code;

Node tree[2 * MAX];
int heap[2 * MAX];
int heapSize = 0;
int nodeCount = 0;

int smaller(int a, int b) {
    if (tree[a].freq != tree[b].freq)
        return tree[a].freq < tree[b].freq;

    return tree[a].minSymbol < tree[b].minSymbol;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapPush(int x) {
    int i = heapSize++;
    heap[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (!smaller(heap[i], heap[p]))
            break;

        swap(&heap[i], &heap[p]);
        i = p;
    }
}

int heapPop(void) {
    int result = heap[0];
    heapSize--;

    if (heapSize > 0) {
        heap[0] = heap[heapSize];

        int i = 0;

        while (1) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int s = i;

            if (l < heapSize &&
                smaller(heap[l], heap[s]))
                s = l;

            if (r < heapSize &&
                smaller(heap[r], heap[s]))
                s = r;

            if (s == i)
                break;

            swap(&heap[i], &heap[s]);
            i = s;
        }
    }

    return result;
}

void getLengths(int node, int depth,
                Code codes[], int *count) {
    if (tree[node].left == -1 &&
        tree[node].right == -1) {
        codes[*count].symbol = tree[node].symbol;

        codes[*count].length = (depth == 0) ? 1 : depth;
        (*count)++;
        return;
    }

    getLengths(tree[node].left, depth + 1,
               codes, count);
    getLengths(tree[node].right, depth + 1,
               codes, count);
}

int compareCodes(const void *a, const void *b) {
    const Code *x = (const Code *)a;
    const Code *y = (const Code *)b;

    if (x->length != y->length)
        return x->length - y->length;

    return (unsigned char)x->symbol -
           (unsigned char)y->symbol;
}

int incrementCode(char code[]) {
    int i = (int)strlen(code) - 1;

    while (i >= 0 && code[i] == '1') {
        code[i] = '0';
        i--;
    }

    if (i < 0)
        return 0;

    code[i] = '1';
    return 1;
}

int main(void) {
    int n;
    long long totalFreq = 0;
    long long weightedLength = 0;

    printf("Enter number of symbols (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    int seen[256] = {0};

    for (int i = 0; i < n; i++) {
        char ch;
        long long f;

        printf("Enter symbol and frequency: ");

        if (scanf(" %c %lld", &ch, &f) != 2 ||
            f <= 0 || seen[(unsigned char)ch]) {
            printf("Invalid or duplicate symbol/frequency.\n");
            return 1;
        }

        seen[(unsigned char)ch] = 1;

        tree[nodeCount].symbol = ch;
        tree[nodeCount].freq = f;
        tree[nodeCount].left = -1;
        tree[nodeCount].right = -1;
        tree[nodeCount].minSymbol = ch;

        totalFreq += f;
        heapPush(nodeCount);
        nodeCount++;
    }

    while (heapSize > 1) {
        int a = heapPop();
        int b = heapPop();

        tree[nodeCount].symbol = '\0';
        tree[nodeCount].freq =
            tree[a].freq + tree[b].freq;
        tree[nodeCount].left = a;
        tree[nodeCount].right = b;

        tree[nodeCount].minSymbol =
            tree[a].minSymbol < tree[b].minSymbol
            ? tree[a].minSymbol : tree[b].minSymbol;

        heapPush(nodeCount);
        nodeCount++;
    }

    int root = heapPop();

    Code codes[MAX];
    int count = 0;

    getLengths(root, 0, codes, &count);

    qsort(codes, count, sizeof(Code), compareCodes);

    int firstLen = codes[0].length;

    if (firstLen >= MAX_CODE) {
        printf("Code length exceeds supported limit.\n");
        return 1;
    }

    memset(codes[0].code, '0', firstLen);
    codes[0].code[firstLen] = '\0';

    for (int i = 1; i < count; i++) {
        strcpy(codes[i].code, codes[i - 1].code);

        if (!incrementCode(codes[i].code)) {
            printf("Canonical code overflow.\n");
            return 1;
        }

        int oldLen = codes[i - 1].length;
        int newLen = codes[i].length;

        if (newLen < oldLen ||
            newLen >= MAX_CODE) {
            printf("Invalid code lengths.\n");
            return 1;
        }

        int currentLen = (int)strlen(codes[i].code);

        while (currentLen < newLen)
            codes[i].code[currentLen++] = '0';

        codes[i].code[currentLen] = '\0';
    }

    printf("\nCanonical Huffman Codebook\n");
    printf("Symbol\tFrequency\tLength\tCode\n");

    for (int i = 0; i < count; i++) {
        long long f = 0;

        for (int j = 0; j < nodeCount; j++) {
            if (tree[j].left == -1 &&
                tree[j].right == -1 &&
                tree[j].symbol == codes[i].symbol) {
                f = tree[j].freq;
                break;
            }
        }

        printf("%c\t%lld\t\t%d\t%s\n",
               codes[i].symbol, f,
               codes[i].length, codes[i].code);

        weightedLength += f * codes[i].length;
    }

    printf("\nExpected code length = %.4f bits/symbol\n",
           (double)weightedLength / totalFreq);

    return 0;
}
