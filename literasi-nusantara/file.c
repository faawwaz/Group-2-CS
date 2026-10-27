#include "app.h"

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Group 2: Alifia, Cavin, Fawwaz, Damar, Zaveer.
Task 1: Alifia Azzahra Prameswary (3002902391). */

static int teksValid(const char *teks, size_t kapasitas)
{
    size_t i;
    for (i = 0; i < kapasitas && teks[i] != '\0'; i++) {
        if (teks[i] == '|' || teks[i] == '\n' || teks[i] == '\r') return 0;
    }
    return i < kapasitas && strspn(teks, " \t") < i;
}

static int bacaHarga(const char *teks, double *harga)
{
    char *akhir;
    errno = 0;
    *harga = strtod(teks, &akhir);
    if (akhir == teks || errno == ERANGE) return 0;
    akhir += strspn(akhir, " \t");
    return *akhir == '\0' && isfinite(*harga) && *harga >= 0;
}

static int bacaJumlah(const char *teks, int *jumlah)
{
    char *akhir;
    long nilai;
    errno = 0;
    nilai = strtol(teks, &akhir, 10);
    if (akhir == teks || errno == ERANGE || nilai < 1 || nilai > INT_MAX) return 0;
    akhir += strspn(akhir, " \t");
    if (*akhir != '\0') return 0;
    *jumlah = (int)nilai;
    return 1;
}

static StatusFile validasiData(const DataToko *data)
{
    int i;
    if (data == NULL || data->jumlahBuku < 0 || data->jumlahBuku > MAX_BUKU
        || data->jumlahHistory < 0 || data->jumlahHistory > MAX_HISTORY)
        return FILE_ARGUMEN_SALAH;
    for (i = 0; i < data->jumlahBuku; i++) {
        const Buku *b = &data->buku[i];
        if (!teksValid(b->kodeBuku, sizeof b->kodeBuku)
            || !teksValid(b->namaBuku, sizeof b->namaBuku)
            || !teksValid(b->jenisBuku, sizeof b->jenisBuku)
            || !isfinite(b->harga) || b->harga < 0) return FILE_FORMAT_SALAH;
    }
    for (i = 0; i < data->jumlahHistory; i++) {
        const History *h = &data->history[i];
        if (!teksValid(h->kodeBuku, sizeof h->kodeBuku) || h->jumlahTerjual < 1
            || !isfinite(h->totalHarga) || h->totalHarga < 0) return FILE_FORMAT_SALAH;
    }
    return FILE_OK;
}

/* Menyiapkan daftar buku dan history kosong. */
void inisialisasiData(DataToko *data)
{
    if (data != NULL) {
        data->jumlahBuku = 0;
        data->jumlahHistory = 0;
    }
}

/* Membaca satu baris menjadi satu data buku. */
StatusFile bacaDataBuku(DataToko *data, const char *namaFile)
{
    FILE *file;
    char baris[256], harga[64];
    Buku buku;
    StatusFile status = FILE_OK;
    int akhir;

    if (data == NULL || namaFile == NULL || namaFile[0] == '\0')
        return FILE_ARGUMEN_SALAH;
    file = fopen(namaFile, "r");
    if (file == NULL) {
        if (errno == ENOENT) {
            data->jumlahBuku = 0;
            return FILE_TIDAK_ADA;
        }
        return FILE_GAGAL_BUKA;
    }
    data->jumlahBuku = 0;
    while (fgets(baris, sizeof baris, file) != NULL) {
        baris[strcspn(baris, "\r\n")] = '\0';
        if (baris[strspn(baris, " \t")] == '\0') continue;
        akhir = 0;
        if (sscanf(baris, "%15[^|]|%100[^|]|%50[^|]|%63[^|]%n",
                    buku.kodeBuku, buku.namaBuku, buku.jenisBuku, harga, &akhir) != 4
            || baris[akhir] != '\0' || !bacaHarga(harga, &buku.harga)
            || !teksValid(buku.kodeBuku, sizeof buku.kodeBuku)
            || !teksValid(buku.namaBuku, sizeof buku.namaBuku)
            || !teksValid(buku.jenisBuku, sizeof buku.jenisBuku)) {
            status = FILE_FORMAT_SALAH;
            break;
        }
        if (data->jumlahBuku == MAX_BUKU) {
            status = FILE_KAPASITAS_PENUH;
            break;
        }
        data->buku[data->jumlahBuku++] = buku;
    }
    if (ferror(file)) status = FILE_GAGAL_BACA;
    if (fclose(file) != 0) status = FILE_GAGAL_BACA;
    if (status != FILE_OK) data->jumlahBuku = 0;
    return status;
}

/* Membaca kode buku, jumlah terjual, dan total harga. */
StatusFile bacaHistory(DataToko *data, const char *namaFile)
{
    FILE *file;
    char baris[128], jumlah[32], total[64];
    History history;
    StatusFile status = FILE_OK;
    int akhir;

    if (data == NULL || namaFile == NULL || namaFile[0] == '\0')
        return FILE_ARGUMEN_SALAH;
    file = fopen(namaFile, "r");
    if (file == NULL) {
        if (errno == ENOENT) {
            data->jumlahHistory = 0;
            return FILE_TIDAK_ADA;
        }
        return FILE_GAGAL_BUKA;
    }
    data->jumlahHistory = 0;
    while (fgets(baris, sizeof baris, file) != NULL) {
        baris[strcspn(baris, "\r\n")] = '\0';
        if (baris[strspn(baris, " \t")] == '\0') continue;
        akhir = 0;
        if (sscanf(baris, "%15[^|]|%31[^|]|%63[^|]%n",
                    history.kodeBuku, jumlah, total, &akhir) != 3
            || baris[akhir] != '\0' || !bacaJumlah(jumlah, &history.jumlahTerjual)
            || !bacaHarga(total, &history.totalHarga)
            || !teksValid(history.kodeBuku, sizeof history.kodeBuku)) {
            status = FILE_FORMAT_SALAH;
            break;
        }
        if (data->jumlahHistory == MAX_HISTORY) {
            status = FILE_KAPASITAS_PENUH;
            break;
        }
        data->history[data->jumlahHistory++] = history;
    }
    if (ferror(file)) status = FILE_GAGAL_BACA;
    if (fclose(file) != 0) status = FILE_GAGAL_BACA;
    if (status != FILE_OK) data->jumlahHistory = 0;
    return status;
}

/* Dipanggil saat startup; file belum ada dianggap normal. */
StatusFile bacaSemuaData(DataToko *data, const char *fileBuku, const char *fileHistory)
{
    StatusFile status;
    if (data == NULL || fileBuku == NULL || fileHistory == NULL
        || fileBuku[0] == '\0' || fileHistory[0] == '\0'
        || strcmp(fileBuku, fileHistory) == 0) return FILE_ARGUMEN_SALAH;
    inisialisasiData(data);
    status = bacaDataBuku(data, fileBuku);
    if (status == FILE_OK || status == FILE_TIDAK_ADA)
        status = bacaHistory(data, fileHistory);
    if (status == FILE_OK || status == FILE_TIDAK_ADA) return FILE_OK;
    inisialisasiData(data);
    return status;
}

/* Mode w membuat file baru atau mengganti data buku lama. */
StatusFile simpanDataBuku(const DataToko *data, const char *namaFile)
{
    FILE *file;
    int i;
    StatusFile status = validasiData(data);
    if (namaFile == NULL || namaFile[0] == '\0') return FILE_ARGUMEN_SALAH;
    if (status != FILE_OK) return status;
    file = fopen(namaFile, "w");
    if (file == NULL) return FILE_GAGAL_BUKA;
    for (i = 0; i < data->jumlahBuku; i++) {
        const Buku *b = &data->buku[i];
        if (fprintf(file, "%s|%s|%s|%.17g\n", b->kodeBuku, b->namaBuku,
                    b->jenisBuku, b->harga) < 0) {
            status = FILE_GAGAL_TULIS;
            break;
        }
    }
    if (fclose(file) != 0) status = FILE_GAGAL_TULIS;
    return status;
}

/* Dapat dipanggil setelah transaksi maupun saat menu 6. */
StatusFile simpanHistory(const DataToko *data, const char *namaFile)
{
    FILE *file;
    int i;
    StatusFile status = validasiData(data);
    if (namaFile == NULL || namaFile[0] == '\0') return FILE_ARGUMEN_SALAH;
    if (status != FILE_OK) return status;
    file = fopen(namaFile, "w");
    if (file == NULL) return FILE_GAGAL_BUKA;
    for (i = 0; i < data->jumlahHistory; i++) {
        const History *h = &data->history[i];
        if (fprintf(file, "%s|%d|%.17g\n", h->kodeBuku,
                    h->jumlahTerjual, h->totalHarga) < 0) {
            status = FILE_GAGAL_TULIS;
            break;
        }
    }
    if (fclose(file) != 0) status = FILE_GAGAL_TULIS;
    return status;
}

/* Menyimpan kedua daftar sebelum program keluar. */
StatusFile simpanSemuaData(const DataToko *data, const char *fileBuku, const char *fileHistory)
{
    StatusFile status;
    if (fileBuku == NULL || fileHistory == NULL || fileBuku[0] == '\0'
        || fileHistory[0] == '\0' || strcmp(fileBuku, fileHistory) == 0)
        return FILE_ARGUMEN_SALAH;
    status = simpanDataBuku(data, fileBuku);
    if (status == FILE_OK) status = simpanHistory(data, fileHistory);
    return status;
}

/* Pesan status untuk modul pemanggil. */
const char *pesanStatusFile(StatusFile status)
{
    switch (status) {
        case FILE_OK: return "berhasil";
        case FILE_TIDAK_ADA: return "file belum ada, data dimulai dari kosong";
        case FILE_GAGAL_BUKA: return "file tidak dapat dibuka";
        case FILE_GAGAL_BACA: return "file tidak dapat dibaca";
        case FILE_GAGAL_TULIS: return "penyimpanan file gagal";
        case FILE_FORMAT_SALAH: return "format atau nilai data tidak valid";
        case FILE_KAPASITAS_PENUH: return "jumlah data melebihi kapasitas";
        case FILE_ARGUMEN_SALAH: return "parameter atau jumlah data tidak valid";
        default: return "status tidak dikenal";
    }
}

/* Main mengakhiri loop hanya jika kedua file berhasil disimpan. */
int menuExit(const DataToko *data, const char *fileBuku, const char *fileHistory)
{
    StatusFile status = simpanSemuaData(data, fileBuku, fileHistory);
    if (status != FILE_OK) {
        printf("Data belum tersimpan: %s.\n", pesanStatusFile(status));
        puts("Program tetap berjalan.");
        return 0;
    }
    puts("Data buku dan history berhasil disimpan.");
    puts("Program selesai.");
    return 1;
}
