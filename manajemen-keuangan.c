#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Transaksi {
    char jenis[20];
    float jumlah;
};

// Fungsi untuk menambah transaksi
void tambahTransaksi(struct Transaksi *transaksi, int *jumlahTransaksi) {
    printf("Jenis transaksi (Pemasukan/Pengeluaran): ");
    scanf("%s", transaksi[*jumlahTransaksi].jenis);

    printf("Jumlah transaksi: ");
    scanf("%f", &transaksi[*jumlahTransaksi].jumlah);

    (*jumlahTransaksi)++;
}

// Fungsi untuk menampilkan semua transaksi
void tampilkanTransaksi(struct Transaksi *transaksi, int jumlahTransaksi) {
    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi.\n");
    } else {
        printf("\nDaftar Transaksi:\n");
        for (int i = 0; i < jumlahTransaksi; i++) {
            printf("%d. Jenis: %s, Jumlah: %.2f\n", i + 1, transaksi[i].jenis, transaksi[i].jumlah);
        }
        printf("\n");
    }
}

// Fungsi untuk mengedit transaksi
void editTransaksi(struct Transaksi *transaksi, int jumlahTransaksi) {
    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi untuk diedit.\n");
        return;
    }

    int nomor;
    tampilkanTransaksi(transaksi, jumlahTransaksi);

    printf("Masukkan nomor transaksi yang ingin diedit: ");
    scanf("%d", &nomor);
    nomor--;

    if (nomor >= 0 && nomor < jumlahTransaksi) {
        printf("Jenis transaksi (Pemasukan/Pengeluaran): ");
        scanf("%s", transaksi[nomor].jenis);

        printf("Jumlah transaksi: ");
        scanf("%f", &transaksi[nomor].jumlah);

        printf("Transaksi berhasil diubah.\n");
    } else {
        printf("Nomor transaksi tidak valid.\n");
    }
}

// Fungsi untuk menghapus transaksi
void hapusTransaksi(struct Transaksi *transaksi, int *jumlahTransaksi) {
    if (*jumlahTransaksi == 0) {
        printf("Belum ada transaksi untuk dihapus.\n");
        return;
    }

    int nomor;
    tampilkanTransaksi(transaksi, *jumlahTransaksi);

    printf("Masukkan nomor transaksi yang ingin dihapus: ");
    scanf("%d", &nomor);
    nomor--;

    if (nomor >= 0 && nomor < *jumlahTransaksi) {
        for (int i = nomor; i < *jumlahTransaksi - 1; i++) {
            transaksi[i] = transaksi[i + 1];
        }
        (*jumlahTransaksi)--;
        printf("Transaksi berhasil dihapus.\n");
    } else {
        printf("Nomor transaksi tidak valid.\n");
    }
}

// Fungsi untuk menyimpan transaksi ke dalam file
void simpanTransaksiKeFile(struct Transaksi *transaksi, int jumlahTransaksi) {
    FILE *file = fopen("transaksi.txt", "w");

    if (file != NULL) {
        for (int i = 0; i < jumlahTransaksi; i++) {
            fprintf(file, "%s %.2f\n", transaksi[i].jenis, transaksi[i].jumlah);
        }

        fclose(file);
        printf("Data transaksi berhasil disimpan.\n");
    } else {
        printf("Gagal menyimpan ke file.\n");
    }
}

// Fungsi untuk membaca transaksi dari file
void bacaTransaksiDariFile(struct Transaksi *transaksi, int *jumlahTransaksi) {
    FILE *file = fopen("transaksi.txt", "r");

    if (file != NULL) {
        while (fscanf(file, "%s %f", transaksi[*jumlahTransaksi].jenis, &transaksi[*jumlahTransaksi].jumlah) == 2) {
            (*jumlahTransaksi)++;
        }

        fclose(file);
    }
}

int main() {
    struct Transaksi transaksi[100]; // Maksimum 100 transaksi
    int jumlahTransaksi = 0;
    int pilihan;

    bacaTransaksiDariFile(transaksi, &jumlahTransaksi);

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Transaksi\n");
        printf("2. Tampilkan Transaksi\n");
        printf("3. Edit Transaksi\n");
        printf("4. Hapus Transaksi\n");
        printf("5. Simpan dan Keluar\n");
        printf("0. Keluar tanpa Menyimpan\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahTransaksi(transaksi, &jumlahTransaksi);
                break;
            case 2:
                tampilkanTransaksi(transaksi, jumlahTransaksi);
                break;
            case 3:
                editTransaksi(transaksi, jumlahTransaksi);
                break;
            case 4:
                hapusTransaksi(transaksi, &jumlahTransaksi);
                break;
            case 5:
                simpanTransaksiKeFile(transaksi, jumlahTransaksi);
                printf("Program selesai.\n");
                break;
            case 0:
                printf("Keluar tanpa menyimpan. Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
                break;
        }
    } while (pilihan != 0);

    return 0;
}
