#ifndef SHELL_SORT_H
#define SHELL_SORT_H
 
#include <string.h>
// Implementasi Shell Sort untuk array integer
void shell_sort_int(int arr[], int n) {
    // Mulai dengan gap besar, lalu kurangi
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Lakukan insertion sort untuk elemen-elemen pada gap tertentu
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
             
            // Pindahkan elemen-elemen yang > temp dan berjarak gap dari satu sama lain
            // ke posisi gap step ke depan dari posisi mereka saat ini
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
             
            // Tempatkan temp (elemen asli arr[i]) ke posisi yang benar
            arr[j] = temp;
        }
    }
}
 
// Implementasi Shell Sort untuk array string
void shell_sort_str(char *arr[], int n) {
    // Mulai dengan gap besar, lalu kurangi
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Lakukan insertion sort untuk elemen-elemen pada gap tertentu
        for (int i = gap; i < n; i++) {
            char *temp = arr[i];
            int j;
             
            // Pindahkan elemen-elemen yang > temp dan berjarak gap dari satu sama lain
            // ke posisi gap step ke depan dari posisi mereka saat ini
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
             
            // Tempatkan temp (elemen asli arr[i]) ke posisi yang benar
            arr[j] = temp;
        }
    }
}
 
#endif /* SHELL_SORT_H */