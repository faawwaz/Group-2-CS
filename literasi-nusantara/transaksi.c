void inputTransaksi(Buku buku[], int nBuku, History hist[], int *nHist) {
    char kode[10], line[50];
    int jumlah = 0, pos = -1, i;

    if (nBuku == 0) {
        printf("Belum ada data buku. Input buku terlebih dahulu.\n");
        return;
    }

    /* 1. Input kode buku (huruf kecil otomatis jadi besar) */
    printf("Kode buku      : ");
    fgets(kode, sizeof(kode), stdin);
    kode[strcspn(kode, "\n")] = '\0';
    for (i = 0; kode[i]; i++)
        if (kode[i] >= 'a' && kode[i] <= 'z') kode[i] -= 32;

    /* 2. Cari harga buku dari daftar */
    for (i = 0; i < nBuku; i++) {
        if (strcmp(buku[i].kode, kode) == 0) { pos = i; break; }
    }
    if (pos == -1) {
        printf("Kode buku tidak ditemukan!\n");
        return;
    }

    /* 3. Input jumlah terjual (minimal 1) */
    do {
        printf("Jumlah terjual : ");
        fgets(line, sizeof(line), stdin);
        if (sscanf(line, "%d", &jumlah) != 1 || jumlah < 1) {
            printf("Jumlah minimal 1 dan harus angka!\n");
            jumlah = 0;
        }
    } while (jumlah < 1);

    /* 4. Hitung total = jumlah x harga, tambahkan ke history */
    strcpy(hist[*nHist].kode, kode);
    hist[*nHist].jumlah = jumlah;
    hist[*nHist].total = jumlah * buku[pos].harga;
    (*nHist)++;

    printf("Transaksi berhasil dicatat.\n");
}
