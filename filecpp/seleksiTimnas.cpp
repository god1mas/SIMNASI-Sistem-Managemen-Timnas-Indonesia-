//Implementasi Queue pada data pemain Timnas yang diseleksi

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

struct PemainSeleksiTimnas {
    string posisi;
    string nama;
    int usia;
    int no_punggung;
    string klub;
    double rating;
    bool timnas;
    PemainSeleksiTimnas* next;

    PemainSeleksiTimnas() : next(nullptr) {}
};

vector<PemainSeleksiTimnas> loadData(const string& path) {
    vector<PemainSeleksiTimnas> pemainList;
    ifstream file(path);
    string line;

    while (getline(file, line)) {
        PemainSeleksiTimnas p;
        stringstream ss(line, ios::in);
        string usiaStr, noStr, ratingStr, timnasStr;

        getline(ss, p.posisi, '|');
        getline(ss, p.nama, '|');
        getline(ss, usiaStr, '|');
        getline(ss, noStr, '|');
        getline(ss, p.klub, '|');
        getline(ss, ratingStr, '|');
        getline(ss, timnasStr, '|');

        p.usia = stoi(usiaStr);
        p.no_punggung = stoi(noStr);
        p.rating = stod(ratingStr);
        p.timnas = stoi(timnasStr) == 1;

        pemainList.push_back(p);
    }

    return pemainList;
}

void tampilkanDataRingkas(const vector<PemainSeleksiTimnas>& data) {
    cout << "\n================================= DATA RINGKAS PEMAIN SELEKSI TIMNAS =================================\n";
    cout << left 
         << setw(6)  << "Pos"
         << setw(6)  << "No"
         << setw(25) << "Nama"
         << setw(25) << "Klub"
         << setw(8)  << "Rating"
         << setw(6)  << "Usia"
         << setw(8)  << "Timnas" << "\n";
    cout << "========================================================================================================\n";

    for (const auto& p : data) {
        cout << left
             << setw(6)  << p.posisi
             << setw(6)  << p.no_punggung
             << setw(25) << p.nama
             << setw(25) << p.klub
             << setw(8)  << fixed << setprecision(1) << p.rating
             << setw(6)  << p.usia
             << setw(8)  << (p.timnas ? "Ya" : "Tidak") << "\n";
    }

    cout << "========================================================================================================\n";
}

void simpanData(const string& path, const vector<PemainSeleksiTimnas>& data) {
    ofstream file(path);
    for (const auto& p : data) {
        file << p.posisi << "|" << p.nama << "|" << p.usia << "|" 
             << p.no_punggung << "|" << p.klub << "|" 
             << p.rating << "|" << (p.timnas ? 1 : 0) << "\n";
    }
}

void tulisQueueToFile(PemainSeleksiTimnas* head, const string& path) {
    ofstream file(path);
    while (head) {
        file << head->posisi << "|" << head->nama << "|" << head->usia << "|"
             << head->no_punggung << "|" << head->klub << "|"
             << head->rating << "|" << (head->timnas ? 1 : 0) << "\n";
        head = head->next;
    }
}

void menuFilter(vector<PemainSeleksiTimnas>& semuaPemain) {
    int pilih;
    cout << "1. Filter by Posisi\n2. Filter by Usia\n3. Filter by Naturalisasi\n";
    cin >> pilih;
    if (pilih == 1) {
        string posisi;
        cout << "Masukkan posisi: ";
        cin >> posisi;
        for (const auto& p : semuaPemain)
            if (p.posisi == posisi)
                cout << p.posisi << " | " << p.nama << " | " << p.usia << endl;
    } else if (pilih == 2) {
        int a, b;
        cout << "Usia dari: "; cin >> a;
        cout << "Usia sampai: "; cin >> b;
        for (const auto& p : semuaPemain)
            if (p.usia >= a && p.usia <= b)
                cout << p.posisi << " | " << p.nama << " | " << p.usia << endl;
    } else if (pilih == 3) {
        auto pemainNaturalisasi = loadData("../data/data_pemain_naturalisasi.txt");
        tampilkanDataRingkas(pemainNaturalisasi);
    }
}

void pickPemain(vector<PemainSeleksiTimnas>& pemainList, PemainSeleksiTimnas*& head) {
    string nama;
    cout << "Masukkan nama pemain yang ingin di-pick: ";
    cin.ignore(); getline(cin, nama);

    for (auto& p : pemainList) {
        if (p.nama == nama) {
            p.timnas = true;

            PemainSeleksiTimnas* baru = new PemainSeleksiTimnas(p);
            if (!head) head = baru;
            else {
                PemainSeleksiTimnas* tail = head;
                while (tail->next) tail = tail->next;
                tail->next = baru;
            }

            cout << "Pemain berhasil di-pick!\n";
            tulisQueueToFile(head, "../data/data_pemain_seleksi.txt");
            return;
        }
    }

    cout << "Pemain tidak ditemukan.\n";
}

void dapatkanPemain(PemainSeleksiTimnas*& head) {
    tulisQueueToFile(head, "../data/data_pemain_timnas.txt");

    ofstream kosong("../data/data_pemain_seleksi.txt", ios::trunc);
    kosong.close();

    // Clear queue
    while (head) {
        PemainSeleksiTimnas* temp = head;
        head = head->next;
        delete temp;
    }

    cout << "Pemain timnas telah disimpan.\n";
}

void seleksiTimnas() {
    vector<PemainSeleksiTimnas> pemainClub = loadData("../data/data_pemain_club.txt");
    vector<PemainSeleksiTimnas> pemainNaturalisasi = loadData("../data/data_pemain_naturalisasi.txt");
    PemainSeleksiTimnas* queueHead = nullptr;

    int menu;
    do {
        cout << "\n=== Menu Seleksi Timnas ===\n";
        cout << "1. Cari Pemain\n2. Tampilkan Semua Pemain\n3. Filter\n4. Dapatkan Pemain\n0. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> menu;
        cin.ignore();

        switch (menu) {
            case 1: {
                string cari;
                cout << "Masukkan nama pemain: ";
                getline(cin, cari);
                for (const auto& p : pemainClub)
                    if (p.nama == cari)
                        cout << p.posisi << " | " << p.nama << " | " << p.usia << endl;
                for (const auto& p : pemainNaturalisasi)
                    if (p.nama == cari)
                        cout << p.posisi << " | " << p.nama << " | " << p.usia << endl;

                cout << "Masukkan pilihan: ";
                cout << "\n1. Pick\n0. Kembali\n";
                int pilih;
                cin >> pilih;
                if (pilih == 1)
                    pickPemain(pemainClub, queueHead);
                break;
            }
            case 2: {
                tampilkanDataRingkas(pemainClub);
                tampilkanDataRingkas(pemainNaturalisasi);

                cout << "Masukkan pilihan: ";
                cout << "\n1. Pick\n0. Kembali\n";
                int pilih;
                cin >> pilih;
                if (pilih == 1)
                    pickPemain(pemainClub, queueHead);
                break;
            }
            case 3:
                menuFilter(pemainClub);
                cout << "Masukkan pilihan: ";
                cout << "\n1. Pick\n0. Kembali\n";
                int pilih;
                cin >> pilih;
                if (pilih == 1)
                    pickPemain(pemainClub, queueHead);
                break;
            case 4:
                dapatkanPemain(queueHead);
                break;
            case 0:
                cout << "Keluar.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (menu != 0);
}
