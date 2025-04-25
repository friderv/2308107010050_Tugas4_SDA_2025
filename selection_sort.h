#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <string.h>
// Implementasi Selection Sort untuk array integer
void selection_sort_int(int arr[], int n) {
    int i, j, min_idx;
    
    for (i = 0; i < n - 1; i++) {
        // Cari elemen minimum dalam array yang belum diurutkan
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
         
        // Tukar elemen minimum dengan elemen pertama
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}
 
// Implementasi Selection Sort untuk array string
void selection_sort_str(char *arr[], int n) {
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {
        // Cari elemen minimum dalam array yang belum diurutkan
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0)
                min_idx = j;
        }
         
        // Tukar elemen minimum dengan elemen pertama
        if (min_idx != i) {
            char *temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}
 
#endif /* SELECTION_SORT_H */