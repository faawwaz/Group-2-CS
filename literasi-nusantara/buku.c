#include <stdio.h>
#include <string.h>
#include "app.h"

// Membuang sisa karakter di baris input
static void bersihkanInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Cek apakah kode sudah dipakai buku lain
static int kodeSudahAda(const DataToko *data, const char *kode)
{
    int i;
    for (i = 0; i < data->jumlahBuku; i++) {
        if (strcmp(data->buku[i].kodeBuku, kode) == 0) return 1;
    }
    return 0;
}

// Menampilkan semua buku dalam bentuk tabel
void tampilkanDaftarBuku(const DataToko *data)
{
    int i;

    printf("%-4s%-8s%-40s%-20s%14s\n", "No", "Kode", "Nama Buku", "Jenis", "Harga (Rp)");
    printf("=========================\n");
    for (i = 0; i < data->jumlahBuku; i++) {
        printf("%-4d%-8s%-40s%-20s%14.2f\n", i + 1,
               data->buku[i].kodeBuku, data->buku[i].namaBuku,
               data->buku[i].jenisBuku, data->buku[i].harga);
    }
}

// Menu 1: input data buku baru, kode dibuat otomatis
void tambahBuku(DataToko *data)
{
    Buku baru;
    int nomor, hasil;

    if (data->jumlahBuku >= MAX_BUKU) {
        printf("Data buku penuh.\n");
        return;
    }

    printf("\n INPUT DATA BUKU BARU \n");

    do {
        printf("Nama buku  : ");
        if (scanf(" %100[^\n]", baru.namaBuku) != 1) return;
        bersihkanInput();
        if (strchr(baru.namaBuku, '|') != NULL) printf("Karakter '|' tidak boleh dipakai!\n");
    } while (strchr(baru.namaBuku, '|') != NULL);

    do {
        printf("Jenis buku : ");
        if (scanf(" %50[^\n]", baru.jenisBuku) != 1) return;
        bersihkanInput();
        if (strchr(baru.jenisBuku, '|') != NULL) printf("Karakter '|' tidak boleh dipakai!\n");
    } while (strchr(baru.jenisBuku, '|') != NULL);

    do {
        printf("Harga buku : ");
        hasil = scanf("%lf", &baru.harga);
        bersihkanInput();
        if (hasil == EOF) return;
        if (hasil != 1 || !(baru.harga > 0)) printf("Harga tidak valid! Masukkan angka lebih dari 0.\n");
    } while (hasil != 1 || !(baru.harga > 0));

    // Kode = jumlah buku + 1; lewati kode yang sudah terpakai (misal setelah ada yang dihapus)
    nomor = data->jumlahBuku + 1;
    do {
        sprintf(baru.kodeBuku, "BK%03d", nomor++);
    } while (kodeSudahAda(data, baru.kodeBuku));

    data->buku[data->jumlahBuku] = baru;
    data->jumlahBuku++;
    printf("Buku berhasil ditambahkan dengan kode %s.\n", baru.kodeBuku);
}

// Menu 3: tampilkan seluruh data buku
void viewBuku(const DataToko *data)
{
    printf("\n DAFTAR BUKU \n");
    if (data->jumlahBuku == 0) {
        printf("Belum ada data buku.\n");
        return;
    }
    tampilkanDaftarBuku(data);
}

// Menu 5: hapus buku berdasarkan nomor urut
void hapusBuku(DataToko *data)
{
    int index, i;

    if (data->jumlahBuku == 0) {
        printf("Tidak ada data buku untuk dihapus.\n");
        return;
    }

    printf("\n HAPUS DATA BUKU \n");
    tampilkanDaftarBuku(data);

    printf("\nMasukkan nomor buku yang ingin dihapus (1-%d): ", data->jumlahBuku);
    if (scanf("%d", &index) != 1) {
        printf("Input tidak valid. Masukkan angka.\n");
        bersihkanInput();
        return;
    }
    bersihkanInput();

    if (index < 1 || index > data->jumlahBuku) {
        printf("Nomor buku tidak valid.\n");
        return;
    }

    for (i = index - 1; i < data->jumlahBuku - 1; i++) {
        data->buku[i] = data->buku[i + 1];
    }
    data->jumlahBuku--;

    printf("Data Successfully delete..\n");
}
