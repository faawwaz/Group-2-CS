#include <stdio.h>

#define BUKU 1
#define MAJALAH 2

struct DataBuku {
    char penulis[50];
    char isbn[20];
};

struct DataMajalah {
    int edisi;
    char bulan[15];
};

union Detail {
    struct DataBuku buku;
    struct DataMajalah majalah;
};

struct Media {
    char judul[100];
    int tahun;
    int jenis;
    union Detail detail;
};

int main() {
    struct Media m;
    int pilihan;

    printf("Judul: ");
    scanf(" %[^\n]", m.judul);
    printf("Tahun terbit: ");
    scanf("%d", &m.tahun);

    do {
        printf("Jenis (1 = Buku, 2 = Majalah): ");
        scanf("%d", &pilihan);
    } while (pilihan != 1 && pilihan != 2);

    if (pilihan == 1) {
        m.jenis = BUKU;
        printf("Penulis: ");
        scanf(" %[^\n]", m.detail.buku.penulis);
        printf("ISBN: ");
        scanf("%s", m.detail.buku.isbn);
    } else {
        m.jenis = MAJALAH;
        printf("Edisi: ");
        scanf("%d", &m.detail.majalah.edisi);
        printf("Bulan: ");
        scanf("%s", m.detail.majalah.bulan);
    }

    printf("\n| Data Media |");
    printf("\nJudul : %s\n", m.judul);
    printf("Tahun : %d\n", m.tahun);
    if (m.jenis == BUKU) {
        printf("Penulis: %s\n", m.detail.buku.penulis);
        printf("ISBN   : %s\n", m.detail.buku.isbn);
    } else {
        printf("Edisi  : %d\n", m.detail.majalah.edisi);
        printf("Bulan  : %s\n", m.detail.majalah.bulan);
    }
    return 0;
}