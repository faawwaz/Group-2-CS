#include <stdio.h>

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) { // Kesalahan ada pada penulisan n-1 seharusnya i < n. Loop luar berhenti satu langkah terlalu cepat, sehingga elemen terakhir (22) tidak pernah diproses
        for (j = i + 1 ; j < n; j++) { // Disini juga ada kesalahan sedikit seharusnya j=i + 1 mengapa? karena kita hanya membandingkan arr[i] dengan elemen di sebelah kanannya
            if (arr[j] < arr[i]) { // disini juga lota harus merubah ">" menjadi "<" agar mengurut dari yang terkecil ke terbesar
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
int main() {
    int arr[] = {64, 34, 25, 12, 22};
    int n = sizeof(arr)/sizeof(arr[0]);
    sort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}