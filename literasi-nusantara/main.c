/*
 * Informasi Anggota Kelompok:
 * 1. Nama: Alifia Azzahra Prameswary - Task 1
 * 2. Nama: Muhammad Damar Alfharidzy - Task 4
 * 3. Nama: [Nama Anggota 3] - [Tugas]
 */

#include <stdio.h>
#include "app.h"

static DataToko data;

/*
 * Fungsi utama untuk menginisialisasi data,
 * membaca data dari file, dan menampilkan menu.
 */
int main(void) {
    int pilihan = 0;
    int selesai = 0;
    StatusFile status;
    int c;
    int hasilExit;


    // Inisialisasi data toko
    inisialisasiData(&data);

    // Membaca semua data dari file
    status = bacaSemuaData(&data, FILE_BUKU, FILE_HISTORY);

    if (status != FILE_OK && status != FILE_TIDAK_ADA) {
        printf("%s\n", pesanStatusFile(status));
    }

    do {
        printf("\n===== MENU TOKO BUKU =====\n");
        printf("1. Input Data Buku Baru\n");
        printf("2. View History Transaksi Penjualan\n");
        printf("3. View Buku\n");
        printf("4. Delete History\n");
        printf("5. Delete Buku\n");
        printf("6. Exit\n");
        printf("7. Input Transaksi Penjualan\n");
        printf("8. Sort Buku\n");
        printf("==========================\n");
        printf("Pilih menu (1-8): ");
        

        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid! Masukkan angka.\n");

            // Membersihkan sisa input
            while ((c = getchar()) != '\n' && c != EOF) {
                /* Buang karakter */
            }

            continue;
        }

        switch (pilihan) {
            case 1:
                // TODO: ganti dengan nama fungsi teman
                // tambahBuku(&data);
                break;

            case 2:
                // TODO: ganti dengan nama fungsi teman
                // viewHistory(&data);
                break;

            case 3:
                // TODO: ganti dengan nama fungsi teman
                // viewBuku(&data);
                break;

            case 4:
                hapusHistory(&data);
                break;

            case 5:
                // TODO: ganti dengan fungsi delete buku milik teman
                // deleteBuku(&data);
                break;

            case 6:
                hasilExit = menuExit(&data, FILE_BUKU, FILE_HISTORY);

                if (hasilExit == 1) {
                    selesai = 1;
                }
                break;

            case 7:
                // TODO: ganti dengan fungsi input transaksi milik teman
                // inputTransaksi(&data);
                break;

            case 8:
                // TODO: ganti dengan nama fungsi sorting milik teman
                // sortingBuku(&data);
                break;

            default:
                printf("Pilihan tidak tersedia! Pilih menu 1-8.\n");
                break;
        }

    } while (selesai == 0);

    return 0;
}