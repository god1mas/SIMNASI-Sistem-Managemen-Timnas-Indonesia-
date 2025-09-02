#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Logistik {
    int id;
    string nama_barang;
    int jumlah;
    string kondisi;
    string kategori;
    string lokasi_penyimpanan;
    string tanggal_masuk;
    bool tersedia;
};

struct Keuangan {
    int id;
    string tanggal;
    string keterangan;
    double nominal;
    string jenis_transaksi;
    string sumber_dana;
};

// Fungsi untuk membaca data keuangan dari file
void bacaDataKeuangan(Keuangan keuangan[], int &jumlah) {
    ifstream file("../data/keuangan.txt");
    jumlah = 0;
    string line;
    
    while (getline(file, line) && jumlah < 100) {
        stringstream ss(line);
        string item;
        int col = 0;
        
        while (getline(ss, item, '|')) {
            switch(col) {
                case 0: keuangan[jumlah].id = stoi(item); break;
                case 1: keuangan[jumlah].tanggal = item; break;
                case 2: keuangan[jumlah].keterangan = item; break;
                case 3: keuangan[jumlah].nominal = stod(item); break;
                case 4: keuangan[jumlah].jenis_transaksi = item; break;
                case 5: keuangan[jumlah].sumber_dana = item; break;
            }
            col++;
        }
        jumlah++;
    }
    file.close();
}

// Fungsi untuk membaca data logistik dari file
void bacaDataLogistik(Logistik logistik[], int &jumlah) {
    ifstream file("../data/logistic.txt");
    jumlah = 0;
    string line;
    
    while (getline(file, line) && jumlah < 100) {
        stringstream ss(line);
        string item;
        int col = 0;
        
        while (getline(ss, item, '|')) {
            switch(col) {
                case 0: logistik[jumlah].id = stoi(item); break;
                case 1: logistik[jumlah].nama_barang = item; break;
                case 2: logistik[jumlah].jumlah = stoi(item); break;
                case 3: logistik[jumlah].kondisi = item; break;
                case 4: logistik[jumlah].kategori = item; break;
                case 5: logistik[jumlah].lokasi_penyimpanan = item; break;
                case 6: logistik[jumlah].tanggal_masuk = item; break;
                case 7: logistik[jumlah].tersedia = (item == "1"); break;
            }
            col++;
        }
        jumlah++;
    }
    file.close();
}

// Fungsi untuk menulis data keuangan ke file
void tulisDataKeuangan(Keuangan keuangan[], int jumlah) {
    ofstream file("../data/keuangan.txt");
    for (int i = 0; i < jumlah; i++) {
        file << keuangan[i].id << "|"
             << keuangan[i].tanggal << "|"
             << keuangan[i].keterangan << "|"
             << keuangan[i].nominal << "|"
             << keuangan[i].jenis_transaksi << "|"
             << keuangan[i].sumber_dana << "\n";
    }
    file.close();
}

// Fungsi untuk menulis data logistik ke file
void tulisDataLogistik(Logistik logistik[], int jumlah) {
    ofstream file("../data/logistic.txt");
    for (int i = 0; i < jumlah; i++) {
        file << logistik[i].id << "|"
             << logistik[i].nama_barang << "|"
             << logistik[i].jumlah << "|"
             << logistik[i].kondisi << "|"
             << logistik[i].kategori << "|"
             << logistik[i].lokasi_penyimpanan << "|"
             << logistik[i].tanggal_masuk << "|"
             << (logistik[i].tersedia ? 1 : 0) << "\n";
    }
    file.close();
}

// Fungsi untuk menampilkan data keuangan
void tampilkanDataKeuangan(Keuangan keuangan[], int jumlah) {
    cout << "\n============================== DATA KEUANGAN TIMNAS INDONESIA ================================\n";
    cout << left << setw(5)  << "ID"
         << setw(12) << "Tanggal"
         << setw(35) << "Keterangan"
         << setw(15) << "Nominal (k)"
         << setw(15) << "Jenis"
         << setw(20) << "Sumber Dana" << "\n";

    cout << "==============================================================================================\n";

    for (int i = 0; i < jumlah; i++) {
        cout << left << setw(5)  << keuangan[i].id
             << setw(12) << keuangan[i].tanggal
             << setw(35) << keuangan[i].keterangan
             << setw(15) << keuangan[i].nominal
             << setw(15) << keuangan[i].jenis_transaksi
             << setw(20) << keuangan[i].sumber_dana << "\n";
    }

    cout << "===============================================================================================\n";
}

// Fungsi untuk menampilkan data logistik
void tampilkanDataLogistik(Logistik logistik[], int jumlah) {
    cout << "\n============================================ DATA LOGISTIK TIMNAS INDONESIA ============================================\n";
    cout << left << setw(5)  << "ID"
         << setw(30) << "Nama Barang"
         << setw(10) << "Jumlah"
         << setw(10) << "Kondisi"
         << setw(22) << "Kategori"
         << setw(20) << "Lokasi"
         << setw(15) << "Tanggal"
         << setw(10) << "Tersedia" << "\n";
    cout << "========================================================================================================================\n";

    for (int i = 0; i < jumlah; i++) {
        cout << left << setw(5)  << logistik[i].id
             << setw(30) << logistik[i].nama_barang
             << setw(10) << logistik[i].jumlah
             << setw(10) << logistik[i].kondisi
             << setw(22) << logistik[i].kategori
             << setw(20) << logistik[i].lokasi_penyimpanan
             << setw(15) << logistik[i].tanggal_masuk
             << setw(10) << (logistik[i].tersedia ? "Ya" : "Tidak") << "\n";
    }

    cout << "========================================================================================================================\n";
}
// Fungsi untuk menambah data keuangan
void tambahDataKeuangan(Keuangan keuangan[], int &jumlah) {
    cout << "\n========== TAMBAH DATA KEUANGAN ==========\n";
    
    keuangan[jumlah].id = jumlah + 1;
    
    cout << "Masukkan tanggal (DD-MM-YYYY): ";
    cin >> keuangan[jumlah].tanggal;
    
    cout << "Masukkan keterangan: ";
    cin.ignore();
    getline(cin, keuangan[jumlah].keterangan);
    
    cout << "Masukkan nominal: ";
    cin >> keuangan[jumlah].nominal;
    
    cout << "Masukkan jenis transaksi (Pemasukan/Pengeluaran): ";
    cin >> keuangan[jumlah].jenis_transaksi;
    
    cout << "Masukkan sumber dana: ";
    cin >> keuangan[jumlah].sumber_dana;
    
    jumlah++;
    tulisDataKeuangan(keuangan, jumlah);
    
    cout << "Data keuangan berhasil ditambahkan!\n";
}

// Fungsi untuk menambah data logistik
void tambahDataLogistik(Logistik logistik[], int &jumlah) {
    cout << "\n========== TAMBAH DATA LOGISTIK ==========\n";
    
    logistik[jumlah].id = jumlah + 1;
    
    cout << "Masukkan nama barang: ";
    cin.ignore();
    getline(cin, logistik[jumlah].nama_barang);
    
    cout << "Masukkan jumlah: ";
    cin >> logistik[jumlah].jumlah;
    
    cout << "Masukkan kondisi (Baik/Rusak/Baru/Hilang): ";
    cin >> logistik[jumlah].kondisi;
    
    cout << "Masukkan kategori: ";
    cin.ignore();
    getline(cin, logistik[jumlah].kategori);
    
    cout << "Masukkan lokasi penyimpanan: ";
    getline(cin, logistik[jumlah].lokasi_penyimpanan);
    
    cout << "Masukkan tanggal masuk (DD-MM-YYYY): ";
    cin >> logistik[jumlah].tanggal_masuk;
    
    cout << "Apakah tersedia? (1 untuk Ya, 0 untuk Tidak): ";
    int tersedia;
    cin >> tersedia;
    logistik[jumlah].tersedia = (tersedia == 1);
    
    jumlah++;
    tulisDataLogistik(logistik, jumlah);
    
    cout << "Data logistik berhasil ditambahkan!\n";
}

// Fungsi untuk mengedit data keuangan
void editDataKeuangan(Keuangan keuangan[], int jumlah) {
    int id;
    cout << "\nMasukkan ID data keuangan yang ingin diedit: ";
    cin >> id;
    
    int index = -1;
    for (int i = 0; i < jumlah; i++) {
        if (keuangan[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "Data dengan ID tersebut tidak ditemukan!\n";
        return;
    }
    
    cout << "\n========== EDIT DATA KEUANGAN ==========\n";
    cout << "Data saat ini:\n";
    cout << "Tanggal: " << keuangan[index].tanggal << "\n";
    cout << "Keterangan: " << keuangan[index].keterangan << "\n";
    cout << "Nominal: " << keuangan[index].nominal << "\n";
    cout << "Jenis Transaksi: " << keuangan[index].jenis_transaksi << "\n";
    cout << "Sumber Dana: " << keuangan[index].sumber_dana << "\n";
    
    cout << "\nMasukkan data baru:\n";
    cout << "Tanggal baru (DD-MM-YYYY): ";
    cin >> keuangan[index].tanggal;
    
    cout << "Keterangan baru: ";
    cin.ignore();
    getline(cin, keuangan[index].keterangan);
    
    cout << "Nominal baru: ";
    cin >> keuangan[index].nominal;
    
    cout << "Jenis transaksi baru (Pemasukan/Pengeluaran): ";
    cin >> keuangan[index].jenis_transaksi;
    
    cout << "Sumber dana baru: ";
    cin >> keuangan[index].sumber_dana;
    
    tulisDataKeuangan(keuangan, jumlah);
    cout << "Data keuangan berhasil diedit!\n";
}

// Fungsi untuk mengedit data logistik
void editDataLogistik(Logistik logistik[], int jumlah) {
    int id;
    cout << "\nMasukkan ID data logistik yang ingin diedit: ";
    cin >> id;
    
    int index = -1;
    for (int i = 0; i < jumlah; i++) {
        if (logistik[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "Data dengan ID tersebut tidak ditemukan!\n";
        return;
    }
    
    cout << "\n========== EDIT DATA LOGISTIK ==========\n";
    cout << "Data saat ini:\n";
    cout << "Nama Barang: " << logistik[index].nama_barang << "\n";
    cout << "Jumlah: " << logistik[index].jumlah << "\n";
    cout << "Kondisi: " << logistik[index].kondisi << "\n";
    cout << "Kategori: " << logistik[index].kategori << "\n";
    cout << "Lokasi: " << logistik[index].lokasi_penyimpanan << "\n";
    cout << "Tanggal Masuk: " << logistik[index].tanggal_masuk << "\n";
    cout << "Tersedia: " << (logistik[index].tersedia ? "Ya" : "Tidak") << "\n";
    
    cout << "\nMasukkan data baru:\n";
    cout << "Nama barang baru: ";
    cin.ignore();
    getline(cin, logistik[index].nama_barang);
    
    cout << "Jumlah baru: ";
    cin >> logistik[index].jumlah;
    
    cout << "Kondisi baru (Baik/Rusak/Baru/Hilang): ";
    cin >> logistik[index].kondisi;
    
    cout << "Kategori baru: ";
    cin.ignore();
    getline(cin, logistik[index].kategori);
    
    cout << "Lokasi penyimpanan baru: ";
    getline(cin, logistik[index].lokasi_penyimpanan);
    
    cout << "Tanggal masuk baru (DD-MM-YYYY): ";
    cin >> logistik[index].tanggal_masuk;
    
    cout << "Apakah tersedia? (1 untuk Ya, 0 untuk Tidak): ";
    int tersedia;
    cin >> tersedia;
    logistik[index].tersedia = (tersedia == 1);
    
    tulisDataLogistik(logistik, jumlah);
    cout << "Data logistik berhasil diedit!\n";
}

// Fungsi untuk menghapus data keuangan
void hapusDataKeuangan(Keuangan keuangan[], int &jumlah) {
    int id;
    cout << "\nMasukkan ID data keuangan yang ingin dihapus: ";
    cin >> id;
    
    int index = -1;
    for (int i = 0; i < jumlah; i++) {
        if (keuangan[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "Data dengan ID tersebut tidak ditemukan!\n";
        return;
    }
    
    // Geser data ke kiri untuk menghapus
    for (int i = index; i < jumlah - 1; i++) {
        keuangan[i] = keuangan[i + 1];
    }
    jumlah--;
    
    // Update ID untuk menjaga urutan
    for (int i = 0; i < jumlah; i++) {
        keuangan[i].id = i + 1;
    }
    
    tulisDataKeuangan(keuangan, jumlah);
    cout << "Data keuangan berhasil dihapus!\n";
}

// Fungsi untuk menghapus data logistik
void hapusDataLogistik(Logistik logistik[], int &jumlah) {
    int id;
    cout << "\nMasukkan ID data logistik yang ingin dihapus: ";
    cin >> id;
    
    int index = -1;
    for (int i = 0; i < jumlah; i++) {
        if (logistik[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "Data dengan ID tersebut tidak ditemukan!\n";
        return;
    }
    
    // Geser data ke kiri untuk menghapus
    for (int i = index; i < jumlah - 1; i++) {
        logistik[i] = logistik[i + 1];
    }
    jumlah--;
    
    // Update ID untuk menjaga urutan
    for (int i = 0; i < jumlah; i++) {
        logistik[i].id = i + 1;
    }
    
    tulisDataLogistik(logistik, jumlah);
    cout << "Data logistik berhasil dihapus!\n";
}

// Menu untuk keuangan
void menuKeuangan() {
    Keuangan keuangan[100];
    int jumlahKeuangan = 0;
    
    bacaDataKeuangan(keuangan, jumlahKeuangan);
    
    int pilihan;
    do {
        cout << "\n========== MENU KEUANGAN TIMNAS ==========\n";
        cout << "1. Tampilkan Data Keuangan\n";
        cout << "2. Tambah Data Keuangan\n";
        cout << "3. Edit Data Keuangan\n";
        cout << "4. Hapus Data Keuangan\n";
        cout << "5. Kembali ke Menu Utama\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tampilkanDataKeuangan(keuangan, jumlahKeuangan);
                break;
            case 2:
                tambahDataKeuangan(keuangan, jumlahKeuangan);
                break;
            case 3:
                tampilkanDataKeuangan(keuangan, jumlahKeuangan);
                editDataKeuangan(keuangan, jumlahKeuangan);
                break;
            case 4:
                tampilkanDataKeuangan(keuangan, jumlahKeuangan);
                hapusDataKeuangan(keuangan, jumlahKeuangan);
                break;
            case 5:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);
}

// Menu untuk logistik
void menuLogistik() {
    Logistik logistik[100];
    int jumlahLogistik = 0;
    
    bacaDataLogistik(logistik, jumlahLogistik);
    
    int pilihan;
    do {
        cout << "\n========== MENU LOGISTIK TIMNAS ==========\n";
        cout << "1. Tampilkan Data Logistik\n";
        cout << "2. Tambah Data Logistik\n";
        cout << "3. Edit Data Logistik\n";
        cout << "4. Hapus Data Logistik\n";
        cout << "5. Kembali ke Menu Utama\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tampilkanDataLogistik(logistik, jumlahLogistik);
                break;
            case 2:
                tambahDataLogistik(logistik, jumlahLogistik);
                break;
            case 3:
                tampilkanDataLogistik(logistik, jumlahLogistik);
                editDataLogistik(logistik, jumlahLogistik);
                break;
            case 4:
                tampilkanDataLogistik(logistik, jumlahLogistik);
                hapusDataLogistik(logistik, jumlahLogistik);
                break;
            case 5:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);
}

// Fungsi utama
void KeuanganDanLogistic() {
    int pilihan;
    
    cout << "========================================\n";
    cout << "  SISTEM MANAJEMEN TIMNAS INDONESIA\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== MENU UTAMA ==========\n";
        cout << "1. Manajemen Keuangan\n";
        cout << "2. Manajemen Logistik\n";
        cout << "3. Kembali\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                menuKeuangan();
                break;
            case 2:
                menuLogistik();
                break;
            case 3:
                cout << "\nTerima kasih telah menggunakan sistem ini!\n";
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    } while (pilihan != 3);
}