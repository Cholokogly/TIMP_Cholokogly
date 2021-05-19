#include <stdio.h>
#include <stdlib.h>

void print(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
}

void writeInFile(int *a, FILE *file, int n) {
    if (file != NULL) {
        for (int i = 0; i < n; i++) {
            fprintf(file, "%d ", a[i]);
        }

        fprintf(file, "\n");
    }
}

void quickSort(int *a, int low, int high, int n, FILE *file) {

    int pivot = a[(low + high) / 2], i = low, j = high;

    writeInFile(a, file, n);

    while (i <= j) {
        while (a[i] < pivot) {
            ++i;
        }

        while(a[j] > pivot) {
            --j;
        }

        if (i <= j) {
            int temp = a[i];

            a[i] = a[j];
            a[j] = temp;

            ++i;
            --j;
        }
    }

    if (high > i) {
        quickSort(a, i, high, n, file);
    }

    if (low < j) {
        quickSort(a, low, j, n, file);
    }
}

void heap(int *a, int len, int i, int n, FILE *file) {
    int left = 2 * i + 1, right = 2 * i + 2, largest = i;

    if (left < len && a[left] > a[largest]) {
        largest = left;
    }

    if (right < len && a[right] > a[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = a[i];

        a[i] = a[largest];
        a[largest] = temp;

        writeInFile(a, file, n);

        heap(a, len, largest, n, file);
    }
}

void heapSort(int *a, int n, FILE *file) {
    if (n <= 1) {
        return;
    }

    int len = n;

    for (int i = len / 2 - 1; i >= 0; i--) {
        heap(a, len, i, n, file);
    }

    for (int i = len - 1; i >= 0; i--) {
        int temp = a[i];

        a[i] = a[0];
        a[0] = temp;

        writeInFile(a, file, n);

        heap(a, i, 0, n, file);
    }
}

int main()
{
    FILE *quickSortFile = fopen("quicksort.log", "w");
    FILE *heapSortFile = fopen("heapsort.log", "w");

    int n;

    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    int *b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        b[i] = a[i];
    }

    quickSort(a, 0, n - 1, n, quickSortFile);
    writeInFile(a, quickSortFile, n);

    print(a, n);

    writeInFile(b, heapSortFile, n);
    heapSort(b, n, heapSortFile);

    return 0;
}
