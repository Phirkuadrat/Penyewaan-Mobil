#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ubah_data (int pilihan, int mode){
    FILE* file = fopen(filePenyewaan,"r");
    FILE* fnew = fopen("new.txt","w+");
    int kode=1;
    while (fscanf(file, "Kode: %d\nNama: %[^\n]\nNo HP: %s\nAlamat: %[^\n]\nEmail: %s\nMobil: %s %s\nDurasi Sewa: %d\nHarga Sewa: %ld\nTotal Bayar: %ld\n\n", &penyewa.kode, penyewa.nama, penyewa.nomorHP, penyewa.alamat, penyewa.email, penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama, &penyewa.durasiSewa, &penyewa.mobilPilihan.price ,&penyewa.totalBayar) != EOF){
            if (penyewa.kode != pilihan){
                fprintf(fnew, "Kode: %d\nNama: %s\nNo HP: %s\nAlamat: %s\nEmail: %s\nMobil: %s %s\nDurasi Sewa: %d\nHarga Sewa: %ld\nTotal Bayar: %ld\n\n", kode, penyewa.nama, penyewa.nomorHP, penyewa.alamat, penyewa.email, penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama, penyewa.durasiSewa, penyewa.mobilPilihan.price ,penyewa.totalBayar);
                kode++;
            } else if (mode==1) {
                fprintf(fnew, "Kode: %d\nNama: %s\nNo HP: %s\nAlamat: %s\nEmail: %s\nMobil: %s %s\nDurasi Sewa: %d\nHarga Sewa: %ld\nTotal Bayar: %ld\n\n", kode, ubahPesanan.nama, ubahPesanan.nomorHP, ubahPesanan.alamat, ubahPesanan.email, penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama, penyewa.durasiSewa, penyewa.mobilPilihan.price ,penyewa.totalBayar);
                kode++;
            } else if (mode==2) {
                penyewa.totalBayar = penyewa.mobilPilihan.price * ubahPesanan.durasiSewa;
                fprintf(fnew, "Kode: %d\nNama: %s\nNo HP: %s\nAlamat: %s\nEmail: %s\nMobil: %s %s\nDurasi Sewa: %d\nHarga Sewa: %ld\nTotal Bayar: %ld\n\n", kode, penyewa.nama, penyewa.nomorHP, penyewa.alamat, penyewa.email, penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama, ubahPesanan.durasiSewa, penyewa.mobilPilihan.price ,penyewa.totalBayar);
                kode++;
            } else if (mode==3){
                penyewa.totalBayar = penyewa.durasiSewa * ubahPesanan.mobilPilihan.price;
                fprintf(fnew, "Kode: %d\nNama: %s\nNo HP: %s\nAlamat: %s\nEmail: %s\nMobil: %s %s\nDurasi Sewa: %d\nHarga Sewa: %ld\nTotal Bayar: %ld\n\n", kode, penyewa.nama, penyewa.nomorHP, penyewa.alamat, penyewa.email, ubahPesanan.mobilPilihan.merk, ubahPesanan.mobilPilihan.nama, penyewa.durasiSewa, ubahPesanan.mobilPilihan.price ,penyewa.totalBayar);
                kode++;
            }
        }
    system("cls");
    if (mode==0){
        printf(ANSI_COLOR_GREEN "Pesanan dihapus\n" ANSI_COLOR_RESET);
    } else {
        printf(ANSI_COLOR_GREEN "Pesanan diubah\n" ANSI_COLOR_RESET);
    }
    fclose(file);
    fclose(fnew);
    remove(filePenyewaan);
    rename("new.txt",filePenyewaan);
};

void edit_durasi (int pilihan){
    int mode=2, menu;
    system("cls");
    printf("Masukan Durasi Sewa (hari): ");
    scanf("%d",&ubahPesanan.durasiSewa);
    printf("Apakah anda yakin ingin mengubah pesanan [1] Ya [2] Tidak : ");
            scanf("%d",&menu);
            switch (menu){
                case 1:
                    ubah_data(pilihan, mode);
                    break;
                case 2:
                    system("cls");
                    printf("Kembali\n");
                    break;
                default:
                    printf(ANSI_COLOR_RED "Menu Tidak Tersedia\n" ANSI_COLOR_RESET);
                    break;
            }
};

void edit_mobil (int pilihan){
    int inputKode, ditemukan=0, menu,mode=3;
    showAll();
    printf("Masukan Kode Mobil: ");
    scanf("%d",&inputKode);

    FILE* file = fopen("mobil.txt", "r");
    int n = 0;
    while (fscanf(file, "%d %s %s %ld", &sort[n].kode, sort[n].nama, sort[n].merk, &sort[n].price) != EOF) {
        n++;
    }

    int awal = 0, akhir = n - 1, tengah;
    while (awal <= akhir) {
        tengah = (awal + akhir) / 2;
        if (sort[tengah].kode == inputKode) {
            ditemukan = 1;
            system("cls");
            printf("Merk Mobil: %s\n", sort[tengah].merk);
            printf("Nama Mobil: %s\n", sort[tengah].nama);
            printf("Harga Sewa (/hari): Rp.%ld\n", sort[tengah].price);
            printf("Apakah anda yakin ingin mengubah mobil pesanan [1] Ya [2] Tidak : ");
            scanf("%d",&menu);
            switch (menu){
            case 1:
                ubahPesanan.mobilPilihan = sort[tengah];
                ubah_data(pilihan, mode);
                break;
            case 2:
                system("cls");
                printf("Kembali");
                break;
            default:
                printf(ANSI_COLOR_RED "Menu Tidak Tersedia\n" ANSI_COLOR_RESET);
                break;
            }
            break;
        } else if (sort[tengah].kode < inputKode) {
            awal = tengah + 1;
        } else {
            akhir = tengah - 1;
        }
    }

    if (ditemukan == 0) {
        system("cls");
        printf(ANSI_COLOR_RED "Mobil dengan kode tersebut tidak tersedia\n" ANSI_COLOR_RESET);
    }
    fclose(file);
};

void edit_identitas(int pilihan){
    int mode=1, menu;
    system("cls");
    printf("=========================\n");
    printf("Detail Informasi Penyewa\n");
    printf("=========================\n");
    printf("Nama : ");  
    scanf(" %[^\n]s", ubahPesanan.nama);
    printf("Nomor HP: ");
    scanf("%s", &ubahPesanan.nomorHP);
    printf("Alamat: ");
    scanf(" %[^\n]s", ubahPesanan.alamat);;
    printf("Email: ");
    scanf("%s", &ubahPesanan.email);
    printf("Apakah anda yakin ingin mengubah pesanan [1] Ya [2] Tidak : ");
    scanf("%d",&menu);
    switch (menu){
        case 1:
            ubah_data(pilihan, mode);
            break;
        case 2:
            system("cls");
            printf("Kembali\n");
            break;
        default:
            printf(ANSI_COLOR_RED "Menu Tidak Tersedia\n" ANSI_COLOR_RESET);
            break;
        }
};

void edit_pesanan(int pilihan){
    int menu=0;
    printf("\n1. Edit identitas\n2. Edit Mobil\n3. Edit Durasi Sewa\nMasukan Pilihan: ");
    scanf("%d",&menu);
    switch (menu){
    case 1:
        edit_identitas(pilihan);
        break;
    case 2:
        edit_mobil(pilihan);
        break;
    case 3:
        edit_durasi(pilihan);
        break;        
    default:
        printf(ANSI_COLOR_RED "Menu Tidak Tersedia\n" ANSI_COLOR_RESET);
        break;
    }
};

void batal_pesanan(int pilihan){
    int menu=0,kode, mode=0;
    printf("Apakah anda yakin ingin menghapus pesanan [1] Ya [2] Tidak : ");
    scanf("%d",&menu);
    FILE* fakun = fopen("akun.txt", "r+");
    FILE* fakunTmp = fopen("akun2.txt", "w+");
    switch (menu){
    case 1:
        while (fscanf(fakun, "%s %s %d\n", akun.username, akun.password, &akun.kode) != EOF) {
                if (strcmp(usernameDigunakan, akun.username) == 0) {
                    kode= akun.kode - 1;
                    fprintf(fakunTmp, "%s %s %d\n", akun.username, akun.password, kode);
                } else {
                    fprintf(fakunTmp, "%s %s %d\n", akun.username, akun.password, akun.kode);
                }
            }
        ubah_data(pilihan, mode);
        break;
    case 2:
        system("cls");
        printf("Kembali\n");
        break;

    default:
        printf(ANSI_COLOR_RED "Menu Tidak Tersedia\n" ANSI_COLOR_RESET);
        break;
    }
    
    fclose(fakun);
    fclose(fakunTmp);
    remove("akun.txt");
    rename("akun2.txt", "akun.txt");
};

void menu_ubah(){
    int menu=0, pilihan=0, ditemukan=0;
    printf("Masukan urutan: ");
    scanf("%d",&pilihan);
    FILE* file =fopen(filePenyewaan,"r+");
    while (fscanf(file, "Kode: %d\nNama: %[^\n]\nNo HP: %s\nAlamat: %[^\n]\nEmail: %s\nMobil: %s %s\nDurasi Sewa: %d\nHarga Sewa: %ld\nTotal Bayar: %ld\n\n", &penyewa.kode, penyewa.nama, penyewa.nomorHP, penyewa.alamat, penyewa.email, penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama, &penyewa.durasiSewa, &penyewa.mobilPilihan.price ,&penyewa.totalBayar) != EOF) {
        if (penyewa.kode == pilihan) {
            ditemukan=1;
            system("cls");
            printf("============= Data Pemesanan =============\n");
            printf("NAMA        : %s\n", penyewa.nama);
            printf("NOMOR HP    : %s\n", penyewa.nomorHP);
            printf("ALAMAT      : %s\n", penyewa.alamat);
            printf("EMAIL       : %s\n", penyewa.email);
            printf("MOBIL       : %s %s\n", penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama);
            printf("DURASI SEWA : %d Hari\n", penyewa.durasiSewa);
            printf("HARGA SEWA  : Rp. %ld\n", penyewa.mobilPilihan.price);
            printf("TOTAL BAYAR : Rp. %ld           \n", penyewa.totalBayar + 200000);
            printf("==========================================\n");
        } 
    }
    fclose(file);
    if (ditemukan==1){
        printf("1. Batalkan Pesanan\n2. Edit Pesanan\n3. Kembali\nMasukan Pilihan: ");
        scanf("%d",&menu);
        switch (menu){
        case 1:
            batal_pesanan(pilihan);
            break;
        case 2:
            edit_pesanan(pilihan);
            break;
        case 3:
            system("cls");
            printf("Kembali\n");
            break;
        default:
            system("cls");
            printf(ANSI_COLOR_RED "Menu Tidak Tersedia\n" ANSI_COLOR_RESET);
            break;
        } 
    } else {
            system("cls");
            printf(ANSI_COLOR_RED "list tidak tersedia\n" ANSI_COLOR_RESET);
    } 
}

void menu_pesanan(){
    int kondisi=0, ditemukan=0;
    system("cls");
    FILE* file= fopen(filePenyewaan,"r+");
    printf("============================ Daftar Penyewaan =================================\n");
    while ((kondisi=fscanf(file, "Kode: %d\nNama: %[^\n]\nNo HP: %s\nAlamat: %[^\n]\nEmail: %s\nMobil: %s %s\nDurasi Sewa: %d\nHarga Sewa: %ld\nTotal Bayar: %ld\n\n", &penyewa.kode, penyewa.nama, penyewa.nomorHP, penyewa.alamat, penyewa.email, penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama, &penyewa.durasiSewa, &penyewa.mobilPilihan.price ,&penyewa.totalBayar)) != EOF) {
        if (kondisi == 10) {
            printf("| %-3d | %-20s | %s %-12s | %-3d %s | Rp.%-10ld |\n", penyewa.kode, penyewa.nama, penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama, penyewa.durasiSewa, "Hari", penyewa.totalBayar);
            ditemukan=1;
        }
    }
    printf("===============================================================================\n");
    if (ditemukan == 0 || file == NULL){
        system("cls");
        printf(ANSI_COLOR_RED "Tidak ada penyewaan\n" ANSI_COLOR_RESET);
        fclose(file);
    } else if (ditemukan == 1){
        fclose(file);
        menu_ubah();   
    }
};

void menu_cetak(){
    int menu=0;
    printf("Tekan [1] untuk cetak Struk Pemesanan, Tekan [2] untuk kembali ke menu: ");
    scanf("%d",&menu);
    switch (menu){
    case 1:
        system("cls");
        printf("=====================================\n");
        printf("|          STRUK PEMESANAN          |\n");
        printf("=====================================\n");
        printf("NAMA      : %s\n", penyewa.nama);
        printf("NOMOR HP  : %s\n", penyewa.nomorHP);
        printf("ALAMAT    : %s\n", penyewa.alamat);
        printf("EMAIL     : %s\n", penyewa.email);
        printf("MOBIL     : %s %s\n", penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama);
        printf("HARGA SEWA: Rp. %ld\n", penyewa.mobilPilihan.price);
        printf("=====================================\n");
        printf("|              Catatan              |\n");
        printf("| Menyewa mobil dikenakan biaya     |\n");
        printf("| deposit sebesar Rp.200.000        |\n");
        printf("| Uang Deposit akan dikembalikan    |\n");
        printf("| setelah mobil sewa                |\n");
        printf("| dikembalikan tanpa kerusakan.     |\n");
        printf("=====================================\n");
        printf("| TOTAL     : Rp. %ld           |\n", penyewa.totalBayar + 200000);
        printf("=====================================\n");
        break;
    case 2:
        system("cls");
        printf("Kembali ke menu\n");
        break;

    default:
        system("cls");
        printf("Kembali ke menu\n");
        break;
    }
};

void inputPenyewa(){
    printf("\n=========================\n");
    printf("Detail Informasi Penyewa\n");
    printf("=========================\n");
    printf("Nama : ");  
    scanf(" %[^\n]s", penyewa.nama);
    printf("Nomor HP: ");
    scanf("%s", &penyewa.nomorHP);
    printf("Alamat: ");
    scanf(" %[^\n]s", penyewa.alamat);;
    printf("Email: ");
    scanf("%s", &penyewa.email);
    printf("Durasi Sewa (hari): ");
    scanf("%d", &penyewa.durasiSewa);
};

void menu_rental() {
    int menu = 0, kode;
    FILE* file = fopen(filePenyewaan, "a");
    FILE* fakun = fopen("akun.txt", "r+");
    FILE* fakunTmp = fopen("akun2.txt", "w+");

    printf("\nApakah ingin menyewa mobil yang dicari?\n1. Ya\n2. Tidak\nMasukan Pilihan: ");
    scanf("%d", &menu);

    switch (menu) {
        case 1: 
            while (fscanf(fakun, "%s %s %d\n", akun.username, akun.password, &akun.kode) != EOF) {
                if (strcmp(usernameDigunakan, akun.username) == 0) {
                    kode= akun.kode + 1;
                    fprintf(fakunTmp, "%s %s %d\n", akun.username, akun.password, kode);
                } else {
                    fprintf(fakunTmp, "%s %s %d\n", akun.username, akun.password, akun.kode);
                }
            }
            inputPenyewa();
            penyewa.totalBayar = penyewa.durasiSewa * penyewa.mobilPilihan.price;
            fprintf(file, "Kode: %d\nNama: %s\nNo HP: %s\nAlamat: %s\nEmail: %s\nMobil: %s %s\nDurasi Sewa: %d\nHarga Sewa: %ld\nTotal Bayar: %ld\n\n", kode, penyewa.nama, penyewa.nomorHP, penyewa.alamat, penyewa.email, penyewa.mobilPilihan.merk, penyewa.mobilPilihan.nama, penyewa.durasiSewa, penyewa.mobilPilihan.price ,penyewa.totalBayar);
            printf(ANSI_COLOR_GREEN "\nPesanan selesai\n" ANSI_COLOR_RESET);
            menu_cetak();
            break;

        case 2:
            system("cls");
            printf("Kembali ke menu\n");
            break;

        default:
            system("cls");
            printf(ANSI_COLOR_RED "Menu tidak tersedia\n" ANSI_COLOR_RESET);
            break;
    }
    fclose(file);
    fclose(fakun);
    fclose(fakunTmp);
    remove("akun.txt");
    rename("akun2.txt", "akun.txt");
};

void showHighest(){
    int n=0;
    FILE* file= fopen("mobil.txt","r");
    while (fscanf(file, "%d %s %s %ld", &sort[n].kode, sort[n].merk, sort[n].nama, &sort[n].price)!=EOF){
        n++;
    }

    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (sort[j].price < sort[j + 1].price){
                data_mobil temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
            }
        }
    }
    
    system ("cls");
    printf("=================== Highest to Lowest ==================\n");
    printf("========================================================\n");
    printf("| %-5s | %-12s | %-15s | %-12s |\n", "KODE", "MERK", "NAMA", "PRICE");
    printf("========================================================\n");
    for (int i = 0; i < n; i++){
        printf("| %-5d | %-12s | %-15s | Rp.%-9ld |\n", sort[i].kode, sort[i].merk, sort[i].nama, sort[i].price);
    }
    printf("========================================================\n");
    fclose(file);
};

void showLowest(){
    int n=0;
    FILE* file= fopen("mobil.txt","r");
    while (fscanf(file, "%d %s %s %ld", &sort[n].kode, sort[n].merk, sort[n].nama, &sort[n].price)!=EOF){
        n++;
    }

    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (sort[j].price > sort[j + 1].price){
                data_mobil temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
            }
        }
    }

    system ("cls");
    printf("=================== Lowest to Highest ==================\n");
    printf("========================================================\n");
    printf("| %-5s | %-12s | %-15s | %-12s |\n", "KODE", "MERK", "NAMA", "PRICE");
    printf("========================================================\n");
    for (int i = 0; i < n; i++){
        printf("| %-5d | %-12s | %-15s | Rp.%-9ld |\n", sort[i].kode, sort[i].merk, sort[i].nama, sort[i].price);
    }
    printf("========================================================\n");
    fclose(file);
};

void showAll(){
    system ("cls");
    printf("======================= Show All =======================\n");
    printf("========================================================\n");
    printf("| %-5s | %-12s | %-15s | %-12s |\n", "KODE", "MERK", "NAMA", "PRICE");
    printf("========================================================\n");
    FILE* file = fopen("mobil.txt","r");
    while (fscanf(file, "%d %s %s %ld", &mobil.kode, mobil.merk, mobil.nama, &mobil.price) != EOF){
        printf("| %-5d | %-12s | %-15s | Rp.%-9ld |\n", mobil.kode, mobil.merk, mobil.nama, mobil.price);
    }
    printf("========================================================\n");
    fclose(file);
};

void menu_list(){
    int menu;
    printf("\n=== List Mobil===\n");
    printf("1. Show All\n2. Sort price from lowest to highest\n3. Sort price from highest to lowest\n4. Kembali\nMasukan Pilihan: ");
    scanf("%d",&menu);
    switch (menu) {
        case 1: 
            showAll();
            break;
        case 2:
            showLowest();
            break;
        case 3:
            showHighest();
            break;
        case 4: 
            system("cls");
            printf("Kembali\n");
            break;
        default:
            system("cls");
            printf(ANSI_COLOR_RED "Menu tidak tersedia.\n" ANSI_COLOR_RESET);
            break;
    }
};

void cari_kode(int ditemukan) {
    int inputKode;
    printf("\nMasukan kode mobil: ");
    scanf("%d", &inputKode);

    FILE* file = fopen("mobil.txt", "r");
    int n = 0;
    while (fscanf(file, "%d %s %s %ld", &sort[n].kode, sort[n].nama, sort[n].merk, &sort[n].price) != EOF) {
        n++;
    }

    int awal = 0, akhir = n - 1, tengah;
    while (awal <= akhir) {
        tengah = (awal + akhir) / 2;
        if (sort[tengah].kode == inputKode) {
            system("cls");
            printf("Merk Mobil: %s\n", sort[tengah].merk);
            printf("Nama Mobil: %s\n", sort[tengah].nama);
            printf("Harga Sewa (/hari): Rp.%ld", sort[tengah].price);
            penyewa.mobilPilihan = sort[tengah];
            ditemukan = 1;
            fclose(file);
            menu_rental();
            break;
        } else if (sort[tengah].kode < inputKode) {
            awal = tengah + 1;
        } else {
            akhir = tengah - 1;
        }
    }

    if (ditemukan == 0) {
        system("cls");
        printf(ANSI_COLOR_RED "Mobil dengan kode tersebut tidak tersedia\n" ANSI_COLOR_RESET);
    }
    fclose(file);
};

void cari_nama(int ditemukan){
    char inputNama[50];
    printf("\nMasukan nama mobil: ");
    scanf("%s", inputNama);

    FILE* file= fopen("mobil.txt","r");
    while (fscanf(file,"%d %s %s %ld", &mobil.kode, mobil.nama, mobil.merk, &mobil.price)!=EOF){
        if (strcmp(mobil.nama, inputNama)==0){
            system("cls");
            printf("Merk Mobil: %s\n", mobil.merk);
            printf("Nama Mobil: %s\n", mobil.nama);
            printf("Harga Sewa (/hari): Rp.%ld", mobil.price);
            penyewa.mobilPilihan = mobil;
            ditemukan = 1;
            menu_rental();
        }
    }
    if (ditemukan==0){
        system("cls");
        printf(ANSI_COLOR_RED "Mobil dengan nama tersebut tidak tersedia\n" ANSI_COLOR_RESET);
    }
};

void menu_cari(){
    int menu, ditemukan=0;
    printf("\n===== Pencarian =====\n1. Nama Mobil\n2. Kode Mobil\n3. Kembali\n");
    printf("Masukan Pilihan: ");        
    scanf("%d", &menu);
    switch (menu) {
        case 1:
            cari_nama(ditemukan);
            break;
        case 2:
            cari_kode(ditemukan);
            break;
        case 3:
            system("cls");
            printf("Kembali\n");
            break;
        default:
            system("cls");
            printf(ANSI_COLOR_RED "Menu tidak tersedia\n" ANSI_COLOR_RESET);
            break;
        }
};

void menu_sesudah_login() {
    int menu;
    sprintf(filePenyewaan, "Penyewaan_%s.txt", usernameDigunakan);
    while (menu!=4){
        printf("\n=== Rental Mobil ===\n1. List Mobil\n2. Cari Mobil\n3. List Penyewaan\n4. Logout\nMasukan Pilihan: ");
        scanf("%d",&menu);
        switch (menu){
            case 1:
                menu_list();
                break;
            case 2:
                menu_cari();
                break;
            case 3:
                menu_pesanan();
                break;
            case 4: 
                system ("cls");
                printf("Berhasil Logout\n\n");
                break;
            default:
                system ("cls");
                printf("Menu tidak tersedia, coba lagi\n\n");
                break;
        }
    }
};

int cek_login(char inputUsername[], char inputPassword []){
    FILE* file= fopen("akun.txt","r");
    while (fscanf(file, "%s %s %d\n", akun.username, akun.password, &akun.kode) != EOF){
        if (strcmp(akun.username, inputUsername) == 0 && strcmp(akun.password, inputPassword) == 0){
            fclose(file);
            return 1;
        }  
    }
    fclose(file);
    return 0;
}

void menu_login(){
    int menu=0;
    char inputUsername[30], inputPassword[30];
    FILE* file= fopen("akun.txt","r");
    if (file == NULL) {
        printf(ANSI_COLOR_RED "Tidak ada akun yang terdaftar, daftar terlebih dahulu!\n\n" ANSI_COLOR_RESET);
        fclose(file);
    } else {
        while (menu!=1){
            printf("=== Menu Login ===\n");
            printf("Username (tekan '#' untuk kembali): ");
            scanf("%s", inputUsername);
            if (inputUsername[0] == '#') {
                menu = 0;
                system("cls");
                printf("Kembali\n\n");
                break;
            }
            printf("Password: ");
            scanf("%s", inputPassword);
            menu = cek_login(inputUsername, inputPassword);
            if (menu == 1) {
                strcpy(usernameDigunakan, inputUsername);
                break;
            } else {
                system("cls");
                printf(ANSI_COLOR_RED "Username atau password salah. Coba lagi.\n\n" ANSI_COLOR_RESET);
            }
        }
        if (menu !=0){
            fclose(file);
            system("cls");
            printf(ANSI_COLOR_GREEN "Berhasil login\n" ANSI_COLOR_RESET);
            menu_sesudah_login();
        }   
    }
};

int cek_registrasi(char inputUsername[], char inputPassword[]){
    if (strchr(inputUsername, '#') != NULL){
            return 1;
        }
    FILE* file= fopen("akun.txt","a+");
    while (fscanf(file, "%s %s", akun.username, akun.password) != EOF){
        if (strcmp(akun.username, inputUsername) == 0){
            return 2;
        }  
    }
    fprintf(file, "%s %s %d\n", inputUsername, inputPassword, 0);
    fclose(file);
    return 0;
};

void menu_registrasi(){
    char inputUsername [30];
    char inputPassword [30];
    printf("=== Menu Registrasi ===\n");
    printf("Masukan username (maksimal 10 karakter): ");
    scanf("%s", inputUsername);
    printf("Masukan password (maksimal 10 karakter): ");
    scanf("%s", inputPassword);
    int hasil=cek_registrasi(inputUsername,inputPassword);
    if (hasil==1){
        system("cls");
        printf(ANSI_COLOR_RED "Terdapat penggunaan karakter khusus pada username. Akun gagal dibuat\n\n" ANSI_COLOR_RESET);
    } else if (hasil==2){
        system("cls");
        printf(ANSI_COLOR_RED "Username sudah digunakan. Akun gagal dibuat\n\n" ANSI_COLOR_RESET);
    } else {
        system("cls");
        printf(ANSI_COLOR_GREEN "Akun berhasil dibuat\n\n" ANSI_COLOR_RESET);
    }
};

void menu(){
    int menu = 0;
    while (menu != 3) {
        printf("===== Menu =====\n1. Registrasi\n2. Login\n3. Keluar\n");
        printf("Masukan Pilihan: ");
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                system("cls");
                menu_registrasi();
                break;
            case 2:
                system("cls");
                menu_login();
                break;
            case 3:
                printf("Terimakasih sudah berkunjung");
                break;
            default:
                printf("Menu tidak tersedia, Coba lagi\n");
                break;
            }
    }
};