#include <stdio.h>
#include <math.h>

int main() {
    int data[20], hamming[30];
    int m, r = 0;
    int i, j;

    printf("Enter number of data bits: ");
    scanf("%d", &m);

    // Calculate number of parity bits
    while (pow(2, r) < (m + r + 1))
        r++;

    printf("Enter %d data bits:\n", m);

    // Read data bits
    for (i = 0; i < m; i++)
        scanf("%d", &data[i]);

    // Insert data bits (reverse order) and reserve parity positions
    j = m - 1;
    for (i = 1; i <= m + r; i++) {
        if ((i & (i - 1)) == 0) {
            hamming[i] = 0;      // Parity bit
        } else {
            hamming[i] = data[j--];
        }
    }

    // Calculate parity bits (Even Parity)
    for (i = 0; i < r; i++) {
        int pos = 1 << i;
        int parity = 0;

        for (j = 1; j <= m + r; j++) {
            if (j & pos)
                parity ^= hamming[j];
        }

        hamming[pos] = parity;
    }

    // Display generated Hamming code
    printf("\nGenerated Hamming Code: ");
    for (i = m + r; i >= 1; i--)
        printf("%d", hamming[i]);
    printf("\n");

    // Receive Hamming code
    printf("\nEnter received Hamming code:\n");

    // Read in the same order as displayed
    for (i = m + r; i >= 1; i--)
        scanf("%d", &hamming[i]);

    // Detect error
    int errorPos = 0;

    for (i = 0; i < r; i++) {
        int pos = 1 << i;
        int parity = 0;

        for (j = 1; j <= m + r; j++) {
            if (j & pos)
                parity ^= hamming[j];
        }

        if (parity)
            errorPos += pos;
    }

    if (errorPos == 0) {
        printf("\nNo error detected.\n");
    } else {
        printf("\nError detected at bit position %d (from right)\n", errorPos);

        // Correct the error
        hamming[errorPos] ^= 1;

        printf("Corrected Hamming Code: ");
        for (i = m + r; i >= 1; i--)
            printf("%d", hamming[i]);
        printf("\n");
    }

    return 0;
}