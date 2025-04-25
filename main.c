/*
 * main.c - Program utama untuk implementasi dan analisis algoritma sorting
 * 
 * Program ini melakukan pengujian dan analisis performa dari berbagai algoritma sorting
 * menggunakan data angka dan kata yang dihasilkan secara acak.
 * Termasuk pengukuran waktu eksekusi dan penggunaan memori dengan Windows API.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <sys/time.h>
 #include <windows.h>
 #include <psapi.h>
 
 // Include semua header algoritma sorting
 #include "bubble_sort.h"
 #include "selection_sort.h"
 #include "insertion_sort.h"
 #include "merge_sort.h"
 #include "quick_sort.h"
 #include "shell_sort.h"
 
 // Ukuran data untuk pengujian
 int data_sizes[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
 int num_data_sizes = 8;
 
 // Struktur untuk menyimpan informasi memori
 typedef struct {
     SIZE_T workingSetSize;       // Memori fisik yang digunakan saat ini (RAM)
     SIZE_T peakWorkingSetSize;   // Memori fisik puncak yang digunakan (RAM)
     SIZE_T pagefileUsage;        // Penggunaan memori virtual
     SIZE_T peakPagefileUsage;    // Penggunaan memori virtual puncak
 } MemoryInfo;
 
 // Fungsi untuk mendapatkan informasi memori saat ini
 MemoryInfo getMemoryInfo() {
     PROCESS_MEMORY_COUNTERS_EX pmc;
     MemoryInfo info = {0};
     
     if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
         info.workingSetSize = pmc.WorkingSetSize;
         info.peakWorkingSetSize = pmc.PeakWorkingSetSize;
         info.pagefileUsage = pmc.PrivateUsage;
         info.peakPagefileUsage = pmc.PeakPagefileUsage;
     }
     
     return info;
 }
 
 // Fungsi untuk menampilkan penggunaan memori dalam KB
 void printMemoryUsage(MemoryInfo before, MemoryInfo after) {
     printf("Penggunaan Memori:\n");
     printf("  Memori Fisik (RAM)      : %zu KB -> %zu KB\n", 
            before.workingSetSize / 1024, after.workingSetSize / 1024);
     
     printf("  Memori Fisik Puncak     : %zu KB\n", after.peakWorkingSetSize / 1024);
     
     printf("  Memori Virtual          : %zu KB -> %zu KB\n",
            before.pagefileUsage / 1024, after.pagefileUsage / 1024);
     
     printf("  Memori Virtual Puncak   : %zu KB\n", after.peakPagefileUsage / 1024);
 }
 
 // Fungsi untuk menghasilkan array angka acak
 void generate_random_numbers(const char *filename, int count, int max_value) {
     FILE *fp = fopen(filename, "w");
     if (!fp) {
         perror("File tidak dapat dibuka");
         return;
     }
     
     srand(time(NULL)); // Inisialisasi seed
     
     for (int i = 0; i < count; i++) {
         int num = rand() % max_value;
         fprintf(fp, "%d\n", num);
     }
     
     fclose(fp);
     printf("File %s dengan %d angka acak berhasil dibuat.\n", filename, count);
 }
 
 // Fungsi untuk menghasilkan kata acak
 void random_word(char *word, int length) {
     static const char charset[] = "abcdefghijklmnopqrstuvwxyz";
     
     for (int i = 0; i < length; i++) {
         int key = rand() % (int)(sizeof(charset) - 1);
         word[i] = charset[key];
     }
     word[length] = '\0';
 }
 
 // Fungsi untuk menghasilkan array kata acak
 void generate_random_words(const char *filename, int count, int max_word_length) {
     FILE *fp = fopen(filename, "w");
     if (!fp) {
         perror("File tidak dapat dibuka");
         return;
     }
     
     srand(time(NULL)); // Inisialisasi seed
     
     char word[100];
     for (int i = 0; i < count; i++) {
         int length = (rand() % (max_word_length - 3)) + 3; // panjang kata minimal 3
         random_word(word, length);
         fprintf(fp, "%s\n", word);
     }
     
     fclose(fp);
     printf("File %s dengan %d kata acak berhasil dibuat.\n", filename, count);
 }
 
 // Fungsi untuk memuat array angka dari file
 int* load_numbers(const char *filename, int count) {
     FILE *fp = fopen(filename, "r");
     if (!fp) {
         perror("File tidak dapat dibuka");
         return NULL;
     }
     
     int *arr = (int*)malloc(count * sizeof(int));
     if (!arr) {
         perror("Alokasi memori gagal");
         fclose(fp);
         return NULL;
     }
     
     for (int i = 0; i < count; i++) {
         if (fscanf(fp, "%d", &arr[i]) != 1) {
             printf("Error membaca data dari file\n");
             free(arr);
             fclose(fp);
             return NULL;
         }
     }
     
     fclose(fp);
     return arr;
 }
 
 // Fungsi untuk memuat array kata dari file
 char** load_words(const char *filename, int count) {
     FILE *fp = fopen(filename, "r");
     if (!fp) {
         perror("File tidak dapat dibuka");
         return NULL;
     }
     
     char **arr = (char**)malloc(count * sizeof(char*));
     if (!arr) {
         perror("Alokasi memori gagal");
         fclose(fp);
         return NULL;
     }
     
     char buffer[100];
     for (int i = 0; i < count; i++) {
         if (fscanf(fp, "%99s", buffer) != 1) {
             printf("Error membaca data dari file\n");
             // Bebaskan memori yang sudah dialokasikan
             for (int j = 0; j < i; j++) {
                 free(arr[j]);
             }
             free(arr);
             fclose(fp);
             return NULL;
         }
         
         arr[i] = strdup(buffer);
         if (!arr[i]) {
             perror("Alokasi memori gagal");
             // Bebaskan memori yang sudah dialokasikan
             for (int j = 0; j < i; j++) {
                 free(arr[j]);
             }
             free(arr);
             fclose(fp);
             return NULL;
         }
     }
     
     fclose(fp);
     return arr;
 }
 
 // Fungsi untuk mengukur waktu eksekusi dan penggunaan memori algoritma sorting (integer)
 void benchmark_sort_int(void (*sort_func)(int[], int), const char *sort_name, int size) {
     printf("Menguji %s dengan %d angka...\n", sort_name, size);
     
     // Muat data dari file
     int *arr = load_numbers("data_angka.txt", size);
     if (!arr) {
         printf("Gagal memuat data\n");
         return;
     }
     
     // Alokasi memori untuk salinan array (untuk dijaga tetap tidak terurut)
     int *arr_copy = (int*)malloc(size * sizeof(int));
     if (!arr_copy) {
         perror("Alokasi memori gagal");
         free(arr);
         return;
     }
     
     // Salin array
     memcpy(arr_copy, arr, size * sizeof(int));
     
     // Ukur memori sebelum sorting
     MemoryInfo memBefore = getMemoryInfo();
     
     // Ukur waktu eksekusi
     struct timeval start, end;
     gettimeofday(&start, NULL);
     
     // Panggil fungsi sorting
     sort_func(arr_copy, size);
     
     gettimeofday(&end, NULL);
     
     // Ukur memori setelah sorting
     MemoryInfo memAfter = getMemoryInfo();
     
     // Hitung waktu eksekusi dalam milidetik
     long seconds = end.tv_sec - start.tv_sec;
     long microseconds = end.tv_usec - start.tv_usec;
     long elapsed = seconds * 1000 + microseconds / 1000; // milidetik
     
     // Validasi hasil sorting
     int is_sorted = 1;
     for (int i = 1; i < size; i++) {
         if (arr_copy[i] < arr_copy[i-1]) {
             is_sorted = 0;
             break;
         }
     }
     
     if (is_sorted) {
         printf("%s dengan %d angka: %ld ms (terurut dengan benar)\n", sort_name, size, elapsed);
         
         // Tampilkan informasi penggunaan memori
         printMemoryUsage(memBefore, memAfter);
         
         // Simpan hasil ke file
         FILE *fp_results = fopen("sorting_results.txt", "a");
         if (fp_results) {
             fprintf(fp_results, "%s,Angka,%d,%ld,%zu,%zu,%zu,%zu\n", 
                    sort_name, size, elapsed, 
                    memAfter.workingSetSize / 1024,     // Current RAM in KB
                    memAfter.peakWorkingSetSize / 1024,  // Peak RAM in KB
                    memAfter.pagefileUsage / 1024,       // Current Virtual Memory in KB
                    memAfter.peakPagefileUsage / 1024);  // Peak Virtual Memory in KB
             fclose(fp_results);
         } else {
             perror("File hasil tidak dapat dibuka");
         }
     } else {
         printf("%s dengan %d angka: GAGAL (hasil tidak terurut)\n", sort_name, size);
     }
     
     // Bebaskan memori
     free(arr);
     free(arr_copy);
 }
 
 // Fungsi untuk mengukur waktu eksekusi dan penggunaan memori algoritma sorting (string)
 void benchmark_sort_str(void (*sort_func)(char*[], int), const char *sort_name, int size) {
     printf("Menguji %s dengan %d kata...\n", sort_name, size);
     
     // Muat data dari file
     char **arr = load_words("data_kata.txt", size);
     if (!arr) {
         printf("Gagal memuat data\n");
         return;
     }
     
     // Alokasi memori untuk salinan array (untuk dijaga tetap tidak terurut)
     char **arr_copy = (char**)malloc(size * sizeof(char*));
     if (!arr_copy) {
         perror("Alokasi memori gagal");
         // Bebaskan memori dari arr
         for (int i = 0; i < size; i++) {
             free(arr[i]);
         }
         free(arr);
         return;
     }
     
     // Salin array
     for (int i = 0; i < size; i++) {
         arr_copy[i] = strdup(arr[i]);
         if (!arr_copy[i]) {
             perror("Alokasi memori gagal");
             // Bebaskan memori yang sudah dialokasikan
             for (int j = 0; j < i; j++) {
                 free(arr_copy[j]);
             }
             for (int j = 0; j < size; j++) {
                 free(arr[j]);
             }
             free(arr_copy);
             free(arr);
             return;
         }
     }
     
     // Ukur memori sebelum sorting
     MemoryInfo memBefore = getMemoryInfo();
     
     // Ukur waktu eksekusi
     struct timeval start, end;
     gettimeofday(&start, NULL);
     
     // Panggil fungsi sorting
     sort_func(arr_copy, size);
     
     gettimeofday(&end, NULL);
     
     // Ukur memori setelah sorting
     MemoryInfo memAfter = getMemoryInfo();
     
     // Hitung waktu eksekusi dalam milidetik
     long seconds = end.tv_sec - start.tv_sec;
     long microseconds = end.tv_usec - start.tv_usec;
     long elapsed = seconds * 1000 + microseconds / 1000; // milidetik
     
     // Validasi hasil sorting
     int is_sorted = 1;
     for (int i = 1; i < size; i++) {
         if (strcmp(arr_copy[i], arr_copy[i-1]) < 0) {
             is_sorted = 0;
             break;
         }
     }
     
     if (is_sorted) {
         printf("%s dengan %d kata: %ld ms (terurut dengan benar)\n", sort_name, size, elapsed);
         
         // Tampilkan informasi penggunaan memori
         printMemoryUsage(memBefore, memAfter);
         
         // Simpan hasil ke file
         FILE *fp_results = fopen("sorting_results.txt", "a");
         if (fp_results) {
             fprintf(fp_results, "%s,Kata,%d,%ld,%zu,%zu,%zu,%zu\n", 
                    sort_name, size, elapsed, 
                    memAfter.workingSetSize / 1024,     // Current RAM in KB
                    memAfter.peakWorkingSetSize / 1024,  // Peak RAM in KB
                    memAfter.pagefileUsage / 1024,       // Current Virtual Memory in KB
                    memAfter.peakPagefileUsage / 1024);  // Peak Virtual Memory in KB
             fclose(fp_results);
         } else {
             perror("File hasil tidak dapat dibuka");
         }
     } else {
         printf("%s dengan %d kata: GAGAL (hasil tidak terurut)\n", sort_name, size);
     }
     
     // Bebaskan memori
     for (int i = 0; i < size; i++) {
         free(arr[i]);
         free(arr_copy[i]);
     }
     free(arr);
     free(arr_copy);
 }
 
 // Fungsi untuk menguji semua algoritma sorting dengan berbagai ukuran data
 void run_benchmarks() {
     // Siapkan file hasil dengan kolom tambahan untuk memori
     FILE *fp_results = fopen("sorting_results.txt", "w");
     if (fp_results) {
         fprintf(fp_results, "Algoritma,Tipe Data,Ukuran Data,Waktu (ms),RAM (KB),Peak RAM (KB),Virtual Memory (KB),Peak Virtual Memory (KB)\n");
         fclose(fp_results);
     } else {
         perror("File hasil tidak dapat dibuka");
         return;
     }
     
     // Uji semua algoritma dengan berbagai ukuran data
     for (int i = 0; i < num_data_sizes; i++) {
         int size = data_sizes[i];
         
         printf("\n===== MENGUJI UKURAN DATA: %d =====\n\n", size);
         
         // Jalankan bubble sort dan selection sort hanya untuk ukuran hingga 100000
         if (size <= 100000) {
             benchmark_sort_int(bubble_sort_int, "Bubble Sort", size);
             benchmark_sort_int(selection_sort_int, "Selection Sort", size);
             benchmark_sort_str(bubble_sort_str, "Bubble Sort", size);
             benchmark_sort_str(selection_sort_str, "Selection Sort", size);
         } else {
             printf("Melewati Bubble Sort dan Selection Sort untuk ukuran data %d (>100000)\n", size);
         }
         
         // Jalankan insertion sort hanya untuk ukuran hingga 250000
         if (size <= 250000) {
             benchmark_sort_int(insertion_sort_int, "Insertion Sort", size);
             benchmark_sort_str(insertion_sort_str, "Insertion Sort", size);
         } else {
             printf("Melewati Insertion Sort untuk ukuran data %d (>250000)\n", size);
         }
         
         // Algoritma lain tetap dijalankan untuk semua ukuran
         benchmark_sort_int(merge_sort_int, "Merge Sort", size);
         benchmark_sort_int(quick_sort_int, "Quick Sort", size);
         benchmark_sort_int(shell_sort_int, "Shell Sort", size);
         
         benchmark_sort_str(merge_sort_str, "Merge Sort", size);
         benchmark_sort_str(quick_sort_str, "Quick Sort", size);
         benchmark_sort_str(shell_sort_str, "Shell Sort", size);
     }
 }
 
 int main() {
     printf("Program Analisis Algoritma Sorting\n");
     printf("==================================\n\n");
     
     int create_data;
     printf("Buat data uji baru? (1 = Ya, 0 = Tidak): ");
     scanf("%d", &create_data);
     
     if (create_data) {
         // Buat data uji
         printf("\nMembuat data uji...\n");
         generate_random_numbers("data_angka.txt", 2000000, 2000000);
         generate_random_words("data_kata.txt", 2000000, 20);
     } else {
         printf("\nMenggunakan data uji yang sudah ada.\n");
     }
     
     // Jalankan benchmark
     printf("\nMemulai benchmark...\n");
     run_benchmarks();
     
     printf("\nBenchmark selesai! Hasil disimpan dalam file sorting_results.txt\n");
     
     return 0;
 }