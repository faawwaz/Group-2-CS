#include <stdio.h>
#include <string.h>

#define MAX 1000

struct Siswa {
    char nama[50];
    int umur;
    char nomor_registrasi[20];
};

int main() {
    struct Siswa siswa[MAX];
    int jumlah = 0;
    char namaCari[50];
    int ditemukan = 0;

    // Membuka file
    FILE *file = fopen("siswa.txt", "r");

    if (file == NULL) {
        printf("File tidak ditemukan!\n");
        return 1;
    }

    // Membaca data dari file
    while (jumlah < MAX &&
           fscanf(file, "%49s %d %19s",
                  siswa[jumlah].nama,
                  &siswa[jumlah].umur,
                  siswa[jumlah].nomor_registrasi) == 3) {
        jumlah++;
    }

    fclose(file);

    // Input nama yang dicari
    printf("Masukkan nama siswa: ");
    scanf("%49s", namaCari);

    // Algoritma Linear Search
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(siswa[i].nama, namaCari) == 0) {
            printf("\nData siswa ditemukan!\n");
            printf("Nama  : %s\n", siswa[i].nama);
            printf("Umur  : %d\n", siswa[i].umur);
            printf("No Reg: %s\n",
                   siswa[i].nomor_registrasi);

            ditemukan = 1;
            break;
        }
    }

    // Validasi jika tidak ditemukan
    if (ditemukan == 0) {
        printf("Nama siswa tidak ditemukan!\n");
    }

    return 0;
}