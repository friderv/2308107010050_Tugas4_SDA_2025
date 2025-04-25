#ifndef QUICK_SORT_H
#define QUICK_SORT_H
 
#include <string.h>
// Fungsi untuk mempartisi array integer
int partition_int(int arr[], int low, int high) {
    int pivot = arr[high]; // Pilih elemen terakhir sebagai pivot
    int i = (low - 1); // Indeks elemen yang lebih kecil
     
    for (int j = low; j <= high - 1; j++) {
        // Jika elemen saat ini lebih kecil dari pivot
        if (arr[j] < pivot) {
            i++; // Increment indeks elemen yang lebih kecil
            // Swap arr[i] dan arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] dan arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
     
    return (i + 1);
}
 
// Fungsi rekursif untuk Quick Sort pada array integer
void quick_sort_int_recursive(int arr[], int low, int high) {
    if (low < high) {
        // Partisi array dan dapatkan posisi pivot
        int pi = partition_int(arr, low, high);
         
        // Urutkan elemen-elemen sebelum dan sesudah posisi pivot
        quick_sort_int_recursive(arr, low, pi - 1);
        quick_sort_int_recursive(arr, pi + 1, high);
    }
}
 
// Fungsi wrapper untuk memanggil quick_sort_int_recursive
void quick_sort_int(int arr[], int n) {
    quick_sort_int_recursive(arr, 0, n - 1);
}
 
// Fungsi untuk mempartisi array string
int partition_str(char *arr[], int low, int high) {
    char *pivot = arr[high]; // Pilih elemen terakhir sebagai pivot
    int i = (low - 1); // Indeks elemen yang lebih kecil
     
    for (int j = low; j <= high - 1; j++) {
        // Jika elemen saat ini lebih kecil dari pivot
        if (strcmp(arr[j], pivot) < 0) {
            i++; // Increment indeks elemen yang lebih kecil
            // Swap arr[i] dan arr[j]
            char *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] dan arr[high] (pivot)
    char *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
     
    return (i + 1);
}
 
// Fungsi rekursif untuk Quick Sort pada array string
void quick_sort_str_recursive(char *arr[], int low, int high) {
    if (low < high) {
        // Partisi array dan dapatkan posisi pivot
        int pi = partition_str(arr, low, high);
         
        // Urutkan elemen-elemen sebelum dan sesudah posisi pivot
        quick_sort_str_recursive(arr, low, pi - 1);
        quick_sort_str_recursive(arr, pi + 1, high);
    }
}
 
// Fungsi wrapper untuk memanggil quick_sort_str_recursive
void quick_sort_str(char *arr[], int n) {
    quick_sort_str_recursive(arr, 0, n - 1);
}
 
#endif /* QUICK_SORT_H */