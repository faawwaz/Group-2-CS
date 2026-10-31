#include <stdio.h>
#include <string.h>
#include "app.h"

/* Group 2 - Task 3: Cavin. */

static void bersihkanInput(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void viewHistory(const DataToko *data)
{
    int i;

    printf("\n===== HISTORY TRANSAKSI PENJUALAN =====\n");
    if (data->jumlahHistory == 0) {
        printf("History masih kosong.\n");
        return;
    }

    printf("%-4s%-12s%-18s%16s\n", "No", "Kode Buku", "Jumlah Terjual", "Total Harga");
    for (i = 0; i < data->jumlahHistory; i++) {
        printf("%-4d%-12s%-18d%16.2f\n", i + 1,
               data->history[i].kodeBuku,
               data->history[i].jumlahTerjual,
               data->history[i].totalHarga);
    }
}

void inputTransaksi(DataToko *data)
{
    char kodeBuku[PANJANG_KODE];
    char input[50];
    char tambahan;
    int jumlahTerjual;
    int indexBuku = -1;
    int i;
    StatusFile status;

    if (data->jumlahBuku == 0) {
        printf("Belum ada data buku. Input buku terlebih dahulu.\n");
        return;
    }

    if (data->jumlahHistory >= MAX_HISTORY) {
        printf("History transaksi sudah penuh.\n");
        return;
    }

    printf("\n===== INPUT TRANSAKSI PENJUALAN =====\n");
    printf("Kode buku      : ");
    if (scanf(" %15s", kodeBuku) != 1) {
        return;
    }
    bersihkanInput();

    for (i = 0; kodeBuku[i] != '\0'; i++) {
        if (kodeBuku[i] >= 'a' && kodeBuku[i] <= 'z') {
            kodeBuku[i] = kodeBuku[i] - ('a' - 'A');
        }
    }

    for (i = 0; i < data->jumlahBuku; i++) {
        if (strcmp(data->buku[i].kodeBuku, kodeBuku) == 0) {
            indexBuku = i;
            break;
        }
    }

    if (indexBuku == -1) {
        printf("Kode buku tidak ditemukan.\n");
        return;
    }

    do {
        printf("Jumlah terjual : ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            return;
        }
        if (strchr(input, '\n') == NULL) {
            bersihkanInput();
        }

        if (sscanf(input, "%d %c", &jumlahTerjual, &tambahan) != 1
            || jumlahTerjual < 1) {
            printf("Jumlah terjual harus berupa angka minimal 1.\n");
            jumlahTerjual = 0;
        }
    } while (jumlahTerjual < 1);

    strcpy(data->history[data->jumlahHistory].kodeBuku, kodeBuku);
    data->history[data->jumlahHistory].jumlahTerjual = jumlahTerjual;
    data->history[data->jumlahHistory].totalHarga =
        jumlahTerjual * data->buku[indexBuku].harga;
    data->jumlahHistory++;

    status = simpanHistory(data, FILE_HISTORY);
    if (status == FILE_OK) {
        printf("Transaksi berhasil dicatat.\n");
    } else {
        printf("Transaksi dicatat, tetapi history belum tersimpan: %s.\n",
               pesanStatusFile(status));
    }
}
