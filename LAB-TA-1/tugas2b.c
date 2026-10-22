#include <stdio.h>

// fungsi agar output dapat menampilkan format rupiah dengan benar
void cetakRupiah(int x) {
    if (x >= 1000000)
        printf("%d.%03d.%03d", x / 1000000, (x / 1000) % 1000, x % 1000);
    else if (x >= 1000)
        printf("%d.%03d", x / 1000, x % 1000);
    else
        printf("%d", x);
}

// fungsi untuk menghitung total gaji bulanan yang telah ditotal dengan jam lembur
int hitungTotalGaji(int gajiPokok, int tarifLembur, int jamLembur) {
    return gajiPokok + (tarifLembur * jamLembur);
}

int main() {
    char nip[30];
    char golongan[10];

    int gajiPokok = 0;
    int tarifLembur = 0;
    int jamLembur;
    int totalGaji;
    int valid, hasilInput, karakter;

    // input NIP pegawai
    printf("Masukkan NIP       : ");
    if (scanf("%29s", nip) != 1) {
        printf("NIP gagal dibaca.\n");
        return 1;
    }

    // membersihkan sisa input tidak valid yang tidak dibutuhkan
    while ((karakter = getchar()) != '\n' && karakter != EOF) {
    }

    // input golongan dan validasi D1, D2, atau D3
    do {
        printf("Masukkan Golongan  : ");
        if (scanf("%9s", golongan) != 1) {
            printf("Golongan gagal dibaca.\n");
            return 1;
        }

        valid = 1;

        // pemeriksaan apakah ada input tambahan
        while ((karakter = getchar()) != '\n' && karakter != EOF) {
            if (karakter != ' ' && karakter != '\t' && karakter != '\r') {
                valid = 0;
            }
        }

        // menentukan gaji pokok sesuai golongan dan gaji lembur
        if (valid && golongan[0] == 'D' && golongan[1] == '1' && golongan[2] == '\0') {
            gajiPokok = 3000000;
            tarifLembur = 15000;
        }
        else if (valid && golongan[0] == 'D' && golongan[1] == '2' && golongan[2] == '\0') {
            gajiPokok = 2500000;
            tarifLembur = 10000;
        }
        else if (valid && golongan[0] == 'D' && golongan[1] == '3' && golongan[2] == '\0') {
            gajiPokok = 2000000;
            tarifLembur = 5000;
        }
        else {
            printf("Golongan tidak valid! Pilih D1, D2, atau D3.\n");
            valid = 0;
        }

    } while (valid == 0);

    // input dan validasi jam lembur
    do {
        printf("Masukkan Jam Lembur: ");
        hasilInput = scanf("%d", &jamLembur);
        valid = 1;

        // pemeriksaan ulang untuk mengantisipasi input jika ada huruf atau angka pecahan
        while ((karakter = getchar()) != '\n' && karakter != EOF) {
            if (karakter != ' ' && karakter != '\t' && karakter != '\r') {
                valid = 0;
            }
        }

        if (hasilInput == EOF) {
            printf("Input jam lembur gagal dibaca.\n");
            return 1;
        }

        // validasi input minimal dan maksimal yaitu sebesar 744 jam yang didapat dari total jam maksimal dalam satu bulan (24 * 31)
        if (hasilInput != 1 || valid == 0 || jamLembur < 0 || jamLembur > 744) {
            printf("Jam lembur harus bilangan bulat antara 0 sampai 744.\n");
            valid = 0;
        }

    } while (valid == 0);

    // fungsi untuk menentukan gaji keseluruhan
    totalGaji = hitungTotalGaji(gajiPokok, tarifLembur, jamLembur);

    // menampilkan hasil perhitungan yang telah diproses
    printf("\n=== HASIL AKHIR PERHITUNGAN ===\n");
    printf("NIP = %s\n", nip);
    printf("Golongan = %s\n", golongan);
    printf("Lembur = %d jam\n", jamLembur);

    printf("Total Gaji Bulan Ini = Rp ");
    cetakRupiah(totalGaji);
    printf("\n");

    return 0;
}
