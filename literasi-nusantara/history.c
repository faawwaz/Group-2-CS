#include <stdio.h>
#include "app.h"

void hapusHistory(DataToko *data) {
    int i;
    int index;
    int hasil;
    int c;

    // Tahap 1: Cek apakah history kosong
    if (data->jumlahHistory == 0) {
        printf("History masih kosong.\n");
        return;
    }

    // Tampilkan daftar history
    printf("\n===== DAFTAR HISTORY PENJUALAN =====\n");

    for (i = 0; i < data->jumlahHistory; i++) {
        printf("%d. Kode Buku: %s | Jumlah Terjual: %d | Total Harga: %.2f\n",
               i + 1,
               data->history[i].kodeBuku,
               data->history[i].jumlahTerjual,
               data->history[i].totalHarga);
    }

    // Tahap 2: Minta nomor history yang ingin dihapus
    printf("\nMasukkan nomor history yang ingin dihapus: ");
    hasil = scanf("%d", &index);

    // Validasi input harus berupa angka
    if (hasil != 1) {
        printf("Input tidak valid! Masukkan angka.\n");
   
        while ((c = getchar()) != '\n' && c != EOF);

        return;
    }

    // Validasi rentang nomor history
    if (index < 1 || index > data->jumlahHistory) {
        printf("Nomor history tidak valid.\n");
        return;
    }

    // Tahap 3: Geser elemen setelah data yang dihapus
    for (i = index - 1; i < data->jumlahHistory - 1; i++) {
        data->history[i] = data->history[i + 1];
    }

    // Kurangi jumlah history
    data->jumlahHistory--;

    printf("Data Successfully delete..\n");
}
