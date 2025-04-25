#ifndef MERGE_SORT_H
#define MERGE_SORT_H
 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Fungsi untuk menggabungkan dua subarray yang sudah terurut
void merge_int(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
     
    // Buat array sementara di heap
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    
    if (L == NULL || R == NULL) {
        // Penanganan error jika alokasi gagal
        if (L) free(L);
        if (R) free(R);
        printf("Error alokasi memori di merge_int\n");
        return;
    }
     
    // Salin data ke array sementara
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
     
    // Gabungkan kembali array sementara ke arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
     
    // Salin elemen yang tersisa dari L[], jika ada
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
     
    // Salin elemen yang tersisa dari R[], jika ada
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Bebaskan memori array sementara
    free(L);
    free(R);
}
 
// Fungsi rekursif untuk Merge Sort pada array integer
void merge_sort_int_recursive(int arr[], int l, int r) {
    if (l < r) {
        // Cari titik tengah
        int m = l + (r - l) / 2;
         
        // Urutkan bagian pertama dan kedua
        merge_sort_int_recursive(arr, l, m);
        merge_sort_int_recursive(arr, m + 1, r);
         
        // Gabungkan bagian yang sudah diurutkan
        merge_int(arr, l, m, r);
    }
}
 
// Fungsi wrapper untuk memanggil merge_sort_int_recursive
void merge_sort_int(int arr[], int n) {
    merge_sort_int_recursive(arr, 0, n - 1);
}
 
// Fungsi untuk menggabungkan dua subarray string yang sudah terurut
void merge_str(char *arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
     
    // Buat array sementara di heap, bukan di stack
    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));
    
    if (L == NULL || R == NULL) {
        // Penanganan error jika alokasi gagal
        if (L) free(L);
        if (R) free(R);
        printf("Error alokasi memori di merge_str\n");
        return;
    }
     
    // Salin data ke array sementara
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
     
    // Gabungkan kembali array sementara ke arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
     
    // Salin elemen yang tersisa dari L[], jika ada
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
     
    // Salin elemen yang tersisa dari R[], jika ada
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Bebaskan memori array sementara
    free(L);
    free(R);
}
 
// Fungsi rekursif untuk Merge Sort pada array string
void merge_sort_str_recursive(char *arr[], int l, int r) {
    if (l < r) {
        // Cari titik tengah
        int m = l + (r - l) / 2;
         
        // Urutkan bagian pertama dan kedua
        merge_sort_str_recursive(arr, l, m);
        merge_sort_str_recursive(arr, m + 1, r);
         
        // Gabungkan bagian yang sudah diurutkan
        merge_str(arr, l, m, r);
    }
}
 
// Fungsi wrapper untuk memanggil merge_sort_str_recursive
void merge_sort_str(char *arr[], int n) {
    merge_sort_str_recursive(arr, 0, n - 1);
}
 
#endif /* MERGE_SORT_H */