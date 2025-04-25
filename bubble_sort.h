#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H
 
#include <string.h>
// Implementasi Bubble Sort untuk array integer
void bubble_sort_int(int arr[], int n) {
    int i, j;
    int swapped;
     
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elemen
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        // Jika tidak ada pertukaran pada pass ini, array sudah terurut
        if (swapped == 0)
            break;
    }
}
 
// Implementasi Bubble Sort untuk array string
void bubble_sort_str(char *arr[], int n) {
    int i, j;
    int swapped;
     
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                // Swap elemen
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}
 
#endif /* BUBBLE_SORT_H */