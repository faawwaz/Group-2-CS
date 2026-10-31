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
    int hasilExit;
    char input[20];
    char tambahan;


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

        if (fgets(input, sizeof(input), stdin) == NULL) {
            pilihan = 6;
        } else if (sscanf(input, "%d %c", &pilihan, &tambahan) != 1) {
            printf("Input tidak valid! Masukkan angka.\n");
            continue;
        }

        switch (pilihan) {
            case 1:
                tambahBuku(&data);
                break;

            case 2:
                viewHistory(&data);
                break;

            case 3:
                viewBuku(&data);
                break;

            case 4:
                hapusHistory(&data);
                break;

            case 5:
                hapusBuku(&data);
                break;

            case 6:
                hasilExit = menuExit(&data, FILE_BUKU, FILE_HISTORY);

                if (hasilExit == 1) {
                    selesai = 1;
                }
                break;

            case 7:
                inputTransaksi(&data);
                break;

            case 8:
                sortingBuku(&data);
                break;

            default:
                printf("Pilihan tidak tersedia! Pilih menu 1-8.\n");
                break;
        }

    } while (selesai == 0);

    return 0;
}
