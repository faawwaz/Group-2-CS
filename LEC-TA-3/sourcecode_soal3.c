#include <stdio.h>
#include <string.h>

#define MAX 1000

struct Siswa {
    char Nama[50];
    int Umur;
    char Nomor_Registrasi[20];
};

int main() {
    struct Siswa siswa[MAX];
    int jumlah = 0;
    char namaCari[50];
    int ditemukan = 0;

    // mebuka file data siswa.txt
    FILE *file = fopen("siswa.txt", "r");

    if (file == NULL) {
        printf("File tidak ditemukan!\n");
        return 1;
    }

    // membaca isi file dan menyimpan data ke array siswa
    while (jumlah < MAX &&
           fscanf(file, "%49s %d %19s",
                  siswa[jumlah].Nama,
                  &siswa[jumlah].Umur,
                  siswa[jumlah].Nomor_Registrasi) == 3) {
        jumlah++;
    }
    fclose(file);

    // input nama siswa yang ingin dicari
    printf("Masukkan nama siswa: ");
    scanf("%49s", namaCari);

    // algoritma linear search
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(siswa[i].Nama, namaCari) == 0) {
            printf("\nData siswa ditemukan!\n");
            printf("Nama  : %s\n", siswa[i].Nama);
            printf("Umur  : %d\n", siswa[i].Umur);
            printf("No Reg: %s\n",
                   siswa[i].Nomor_Registrasi);

            ditemukan = 1;
            break;
        }
    }

    // validasi jika data tidak ditemukan
    if (ditemukan == 0) {
        printf("Nama siswa tidak ditemukan!\n");
    }

    return 0;
}