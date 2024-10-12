#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_KARYAWAN 100
#define MAX_NAMA 100
#define MAX_USERNAME 100
#define MAX_PASSWORD 100

typedef struct {
    char nama[MAX_NAMA];
    int hadir;
    int lembur;
    time_t jamMasuk;
    time_t jamKeluar;
} Karyawan;

Karyawan daftarKaryawan[MAX_KARYAWAN];
int jumlahKaryawan = 0;
char akunPassword[MAX_PASSWORD] = "1234";
char akunUsername[MAX_USERNAME] = "admin";

void tambahKaryawan(const char *nama) {
    if (jumlahKaryawan < MAX_KARYAWAN) {
        strcpy(daftarKaryawan[jumlahKaryawan].nama, nama);
        daftarKaryawan[jumlahKaryawan].hadir = 0;
        daftarKaryawan[jumlahKaryawan].lembur = 0;
        daftarKaryawan[jumlahKaryawan].jamMasuk = 0;
        daftarKaryawan[jumlahKaryawan].jamKeluar = 0;
        jumlahKaryawan++;
    } else {
        printf("Daftar karyawan penuh!\n");
    }
}

void DaftarKaryawan (void) {
    printf("\nDaftar Karyawan:\n");
    for (int i = 0; i < jumlahKaryawan; i++) {
        printf("%d. %s\n", i + 1, daftarKaryawan[i].nama);
    }
}

void absenMasukKaryawan(int nomorKaryawan) {
    if (nomorKaryawan > 0 && nomorKaryawan <= jumlahKaryawan) {
        Karyawan *karyawan = &daftarKaryawan[nomorKaryawan - 1];
        if (!karyawan->hadir) {
            karyawan->hadir = 1;
            karyawan->jamMasuk = time(NULL);
            printf("%s telah diabsen masuk.\n", karyawan->nama);
        } else {
            printf("%s sudah absen masuk sebelumnya.\n", karyawan->nama);
        }
    } else {
        printf("Nomor karyawan tidak valid.\n");
    }
}

void absenPulangKaryawan(int nomorKaryawan) {
    if (nomorKaryawan > 0 && nomorKaryawan <= jumlahKaryawan) {
        Karyawan *karyawan = &daftarKaryawan[nomorKaryawan - 1];
        if (karyawan->hadir) {
            karyawan->jamKeluar = time(NULL);
            double durasi = difftime(karyawan->jamKeluar, karyawan->jamMasuk) / 3600.0;
            printf("%s telah diabsen pulang.\n", karyawan->nama);
            printf("Durasi kerja: %.2f jam\n", durasi);
        } else {
            printf("%s belum absen masuk.\n", karyawan->nama);
        }
    } else {
        printf("Nomor karyawan tidak valid.\n");
    }
}

void lihatDaftarHadir(void) {
    printf("\nDaftar Hadir Karyawan:\n");
    for (int i = 0; i < jumlahKaryawan; i++) {
        Karyawan *karyawan = &daftarKaryawan[i];
        printf("Nama: %s, Hadir: %s, Jam Masuk: %s, Jam Keluar: %s\n",
               karyawan->nama,
               karyawan->hadir ? "Ya" : "Tidak",
               karyawan->hadir ? ctime(&karyawan->jamMasuk) : "Belum absen masuk",
               karyawan->jamKeluar ? ctime(&karyawan->jamKeluar) : "Belum absen pulang");
    }
}

int login(void) {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Login Program Absensi\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Bandingkan dengan akun yang benar
    if (strcmp(username, akunUsername) == 0 && strcmp(password, akunPassword) == 0) {
        printf("Login berhasil! Selamat datang, %s.\n", username);
        return 1;
    } else {
        printf("Username atau password salah.\n");
        return 0;
    }
}

void gantiUsername(void) {
    char usernameBaru[MAX_USERNAME];
    printf("Masukkan Username baru: ");
    scanf("%s", usernameBaru);
    strcpy(akunUsername, usernameBaru);
    printf("Username Berhasil diganti menjadi %s\n", akunUsername);
}

void lemburKaryawan(int idLembur) {
    if (idLembur > 0 && idLembur <= jumlahKaryawan) {
        Karyawan *karyawan = &daftarKaryawan[idLembur - 1];
        karyawan->lembur = 1;  // Tandai lembur
        printf("%s telah ditandai untuk lembur.\n", karyawan->nama);
    } else {
        printf("Nomor karyawan tidak valid.\n");
    }
}


// saya disini menamni anda bahwasannya
int main(void) {
    tambahKaryawan("Satriya Dwi Mahardhika as Head Manager");
    tambahKaryawan("M. Arif Suthon Abdulloh as Staff IT");
    tambahKaryawan("Echa Serlvy Windiani as Personal Manager");
    tambahKaryawan("M. Farhan Roby Syaifullah as HRD");
    tambahKaryawan("Surya Yoga Pratama as Enginering");
    tambahKaryawan("Ibadryansyah Inalasma as Personal Manager");
    tambahKaryawan("Boy Pablo as HRD");
    tambahKaryawan("Kingsa Cantika Putri Atmodjo as Enginering");
    tambahKaryawan("Lukman Ihsan Setiawan as Staff IT");
    
   
    while (1) {
        if (!login()) {
            printf("Login gagal, silakan coba lagi.\n");
            continue;
        }
        
        
        while (1) {
            int pilihan;
            printf("\nProgram Absensi\n");
            printf("1. Lihat Daftar Karyawan\n");
            printf("2. Tambah Karyawan\n");
            printf("3. Absen Masuk Karyawan\n");
            printf("4. Absen Pulang Karyawan\n");
            printf("5. Lihat Daftar Hadir\n");
            printf("6. Logout\n");
            printf("7. Ganti Username\n");
            printf("8. Lembur Karyawan\n");
            printf("Pilih menu: ");
            scanf("%d", &pilihan);
            
            switch (pilihan) {
                case 1:
                    DaftarKaryawan();
                    break;
                case 2: {
                    char nama[MAX_NAMA];
                    printf("Masukkan nama karyawan baru: ");
                    scanf(" %[^\n]%*c", nama);
                    tambahKaryawan(nama);
                    break;
                }
                case 3: {
                    int nomor;
                    printf("Masukkan nomor karyawan yang akan diabsen masuk: ");
                    scanf("%d", &nomor);
                    absenMasukKaryawan(nomor);
                    break;
                }
                case 4: {
                    int nomor;
                    printf("Masukkan nomor karyawan yang akan absen pulang: ");
                    scanf("%d", &nomor);
                    absenPulangKaryawan(nomor);
                    break;
                }
                case 5:
                    lihatDaftarHadir();
                    break;
                case 6:
                    printf("Logout berhasil!\n");
                    break;
                case 7:
                    gantiUsername();
                    break;
                case 8: {
                    int idLembur;
                    printf("Masukkan ID Karyawan untuk lembur: ");
                    scanf("%d", &idLembur);
                    lemburKaryawan(idLembur);
                    break;
                }
                default:
                    printf("Pilihan tidak valid.\n");
                    break;
            }

            if (pilihan == 6) {
                break;
            }
        }
    }

    return 0;
}




//16 - 21 desember 2024 pukul 8.40 sampai 10.20
// pelatihan dasar teknologi digital > lab komputer bahasa a- gedung ict lt 6 f/g/h/j  materi implementasi fumgsi define/typedef/if else/switch/struct


