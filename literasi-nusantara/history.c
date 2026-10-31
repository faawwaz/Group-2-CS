#include <stdio.h>
#include "app.h"

void hapusHistory(DataToko *data) {
    int i;
    int index;
    char input[50];
    char tambahan;

    // Tahap 1: Cek apakah history kosong
    if (data->jumlahHistory == 0) {
        printf("History masih kosong.\n");
        return;
    }

    // Tampilkan daftar history
    viewHistory(data);

    // Tahap 2: Minta nomor history yang ingin dihapus
    printf("\nMasukkan nomor history yang ingin dihapus: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return;
    }

    // Validasi input harus berupa angka
    if (sscanf(input, "%d %c", &index, &tambahan) != 1) {
        printf("Input tidak valid! Masukkan angka.\n");
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
