#ifndef APP_H
#define APP_H

/* Group 2 - Task 1: Alifia Azzahra Prameswary (3002902391). */
#define MAX_BUKU 1000
#define MAX_HISTORY 5000
#define PANJANG_KODE 16
#define PANJANG_NAMA 101
#define PANJANG_JENIS 51

#define FILE_BUKU "databuku.txt"
#define FILE_HISTORY "history.txt"

typedef struct {
    char kodeBuku[PANJANG_KODE];
    char namaBuku[PANJANG_NAMA];
    char jenisBuku[PANJANG_JENIS];
    double harga;
} Buku;

typedef struct {
    char kodeBuku[PANJANG_KODE];
    int jumlahTerjual;
    double totalHarga;
} History;

typedef struct {
    Buku buku[MAX_BUKU];
    int jumlahBuku;
    History history[MAX_HISTORY];
    int jumlahHistory;
} DataToko;

typedef enum {
    FILE_OK,
    FILE_TIDAK_ADA,
    FILE_GAGAL_BUKA,
    FILE_GAGAL_BACA,
    FILE_GAGAL_TULIS,
    FILE_FORMAT_SALAH,
    FILE_KAPASITAS_PENUH,
    FILE_ARGUMEN_SALAH
} StatusFile;

void inisialisasiData(DataToko *data);
StatusFile bacaDataBuku(DataToko *data, const char *namaFile);
StatusFile bacaHistory(DataToko *data, const char *namaFile);
StatusFile bacaSemuaData(DataToko *data, const char *fileBuku,
                        const char *fileHistory);
StatusFile simpanDataBuku(const DataToko *data, const char *namaFile);
StatusFile simpanHistory(const DataToko *data, const char *namaFile);
StatusFile simpanSemuaData(const DataToko *data, const char *fileBuku,
                          const char *fileHistory);
const char *pesanStatusFile(StatusFile status);

/* Hasil 1 berarti kedua file tersimpan dan program boleh keluar. */
int menuExit(const DataToko *data, const char *fileBuku,
             const char *fileHistory);

#endif
