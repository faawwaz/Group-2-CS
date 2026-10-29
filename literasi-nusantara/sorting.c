#include <stdio.h>
#include <string.h>
#include "app.h"

/* Group 2 - Task 5: Fawwaz Damai Saputra. */

/* (bubble sort) membandingkan nama dua buku yang bersebelahan. */
void bubbleSortNama(Buku buku[], int jumlahBuku) {
    int i, j;
    Buku sementara;

    for (i = 0; i < jumlahBuku - 1; i++) {
        for (j = 0; j < jumlahBuku - i - 1; j++) {
            if (strcmp(buku[j].namaBuku, buku[j + 1].namaBuku) > 0) {
                sementara = buku[j];
                buku[j] = buku[j + 1];
                buku[j + 1] = sementara;
            }
        }
    }
}

/* (selection sort) pencarian harga terbesar. */
void selectionSortHarga(Buku buku[], int jumlahBuku) {
    int i, j;
    int indexTerbesar;
    Buku sementara;

    for (i = 0; i < jumlahBuku - 1; i++) {
        indexTerbesar = i;

        for (j = i + 1; j < jumlahBuku; j++) {
            if (buku[j].harga > buku[indexTerbesar].harga) {
                indexTerbesar = j;
            }
        }

        if (indexTerbesar != i) {
            sementara = buku[i];
            buku[i] = buku[indexTerbesar];
            buku[indexTerbesar] = sementara;
        }
    }
}

/* menampilkan semua field buku setelah diurutkan. */
static void tampilkanHasilSorting(const DataToko *data) {
    int i;

    for (i = 0; i < data->jumlahBuku; i++) {
        printf("%d. Kode Buku: %s | Nama: %s | Jenis: %s | Harga: %.2f\n",
               i + 1,
               data->buku[i].kodeBuku,
               data->buku[i].namaBuku,
               data->buku[i].jenisBuku,
               data->buku[i].harga);
    }
}

void sortingBuku(DataToko *data) {
    char pilihan;
    int c;

    if (data->jumlahBuku == 0) {
        printf("Tidak ada data buku untuk diurutkan.\n");
        return;
    }

    do {
        printf("\n===== SORT BUKU =====\n");
        printf("a. Urutkan berdasarkan nama (A-Z, bubble sort)\n");
        printf("b. Urutkan berdasarkan harga (tertinggi ke terendah, selection sort)\n");
        printf("c. Kembali ke menu utama\n");
        printf("Pilih menu (a/b/c): ");

        if (scanf(" %c", &pilihan) != 1) {
            return;
        }

        /* membersihkan sisa input */
        while ((c = getchar()) != '\n' && c != EOF) {
            /* buang sisa karakter */
        }

        switch (pilihan) {
            case 'a':
            case 'A':
                bubbleSortNama(data->buku, data->jumlahBuku);
                printf("\n===== HASIL SORT NAMA (A-Z) =====\n");
                tampilkanHasilSorting(data);
                break;

            case 'b':
            case 'B':
                selectionSortHarga(data->buku, data->jumlahBuku);
                printf("\n===== HASIL SORT HARGA (TERTINGGI KE TERENDAH) =====\n");
                tampilkanHasilSorting(data);
                break;

            case 'c':
            case 'C':
                break;

            default:
                printf("Pilihan tidak tersedia! Pilih a, b, atau c.\n");
                break;
        }
    } while (pilihan != 'c' && pilihan != 'C');
}
