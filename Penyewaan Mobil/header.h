#ifndef header_h
#define header_h

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct {
  int kode;
  char nama[30];
  char merk[50];
  long int price;
} data_mobil;

typedef struct{
  int kode;
  char nama[30];
  char nomorHP[30];
  char email[50];
  char alamat[50];
  int durasiSewa;
  long int totalBayar;
  data_mobil mobilPilihan;
} data_sewa;

typedef struct{
    char username[20];
    char password[20];
    int kode;
} data_user;
 
data_sewa penyewa, ubahPesanan;
data_user akun;
data_mobil mobil, sort[100];
char usernameDigunakan [30];
char filePenyewaan [50];

void ubah_data (int pilihan, int mode);
void edit_durasi (int pilihan);
void edit_mobil (int pilihan);
void edit_identitas(int pilihan);
void hapus_data(int pilihan);
void edit_pesanan(int pilihan);
void batal_pesanan(int pilihan);
void menu_ubah();
void menu_pesanan();
void menu_cetak();
void inputPenyewa();
void menu_rental();
void showHighest();
void showLowest();
void showAll();
void menu_list();
void menu_cari();
void menu_sesudah_login();
int cek_login(char inputUsername[], char inputPassword []);
void menu_login();
int cek_registrasi(char inputUsername[], char inputPassword []);
void menu_registrasi();
void menu();

#endif