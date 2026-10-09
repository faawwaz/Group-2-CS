
#include <stdio.h>

// data pegawai
struct pegawai {
    char nip[20];
    char nama[50];
    char alamat[50];
    char hp[20];
    char jabatan[30];
    char gol[5];
    long gaji;
};

// Menampilkan angka dgn format rupiah
void tampil(long n) {
    if (n >= 1000000)
        printf("Rp%ld.%03ld.%03ld", n / 1000000, n / 1000 % 1000, n % 1000);
    else
        printf("Rp%ld.%03ld", n / 1000, n % 1000);
}

int main() {
    struct pegawai p;

    // input data pegawai
    printf("Masukkan NIP       : ");
    scanf(" %[^\n]", p.nip);
    printf("Masukkan Nama      : ");
    scanf(" %[^\n]", p.nama);
    printf("Masukkan Alamat    : ");
    scanf(" %[^\n]", p.alamat);
    printf("Masukkan No HP     : ");
    scanf(" %[^\n]", p.hp);
    printf("Masukkan Jabatan   : ");
    scanf(" %[^\n]", p.jabatan);

    // input golongan
    printf("Masukkan Golongan  : ");
    scanf(" %s", p.gol);
    while (!((p.gol[0] == 'D' || p.gol[0] == 'd') &&
             (p.gol[1] == '1' || p.gol[1] == '2' || p.gol[1] == '3') &&
             p.gol[2] == '\0')) {
        printf("Golongan harus D1, D2, atau D3\n");
        printf("Masukkan Golongan  : ");
        scanf(" %s", p.gol);
    }

    // gaji pokok sesuai golongan
    if (p.gol[1] == '1')
        p.gaji = 3000000;
    else if (p.gol[1] == '2')
        p.gaji = 2500000;
    else
        p.gaji = 2000000;

    // tampilkan data
    printf("\nNIP      = %s\n", p.nip);
    printf("Nama     = %s\n", p.nama);
    printf("Alamat   = %s\n", p.alamat);
    printf("No HP    = %s\n", p.hp);
    printf("Jabatan  = %s\n", p.jabatan);
    printf("Golongan = %s\n", p.gol);
    printf("Gaji Pokok Anda: ");
    tampil(p.gaji);
    printf("\n");
    return 0;
}
