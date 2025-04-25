#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <string.h>
// Implementasi Insertion Sort untuk array integer
void insertion_sort_int(int arr[], int n) {
    int i, key, j;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
         
        /* Pindahkan elemen arr[0..i-1] yang lebih besar dari key
            ke posisi satu indeks di depan posisi mereka saat ini */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 
// Implementasi Insertion Sort untuk array string
void insertion_sort_str(char *arr[], int n) {
    int i, j;
    char *key;
     
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
         
         /* Pindahkan elemen arr[0..i-1] yang lebih besar dari key
            ke posisi satu indeks di depan posisi mereka saat ini */
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 
#endif /* INSERTION_SORT_H */