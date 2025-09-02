//implementasi linkedlist untuk data pemain pada klub

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

// Struct untuk data pemain
struct PemainKlub {
    string posisi;
    string nama;
    int usia;
    int no_punggung;
    string klub;
    double rating;
    bool timnas;
    PemainKlub* next; // pointer untuk linked list
    
    PemainKlub() : next(nullptr) {}
};

// Struct untuk data klub
struct Club {
    string nama;
    string kota;
    string stadion;
    int tahunBerdiri;
    string pelatih;
    PemainKlub* pemain; // head pointer untuk linked list pemain
    
    Club() : pemain(nullptr) {}
};

class FootballClubSystem {
private:
    vector<Club> clubs;
    
public:
    // Fungsi untuk memuat data klub dari file
    bool loadClubData() {
        ifstream file("../data/data_club.txt");
        if (!file.is_open()) {
            cout << "Error: Tidak dapat membuka file ./data/data_club.txt" << endl;
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            Club club;
            stringstream ss(line);
            string temp;
            
            // Parse data klub dengan delimiter |
            getline(ss, club.nama, '|');
            getline(ss, club.kota, '|');
            getline(ss, club.stadion, '|');
            getline(ss, temp, '|');
            club.tahunBerdiri = stoi(temp);
            getline(ss, club.pelatih, '|');
            
            clubs.push_back(club);
        }
        
        file.close();
        return true;
    }
    
    // Fungsi untuk memuat data pemain dari file
    bool loadPemainKlubData() {
        ifstream file("../data/data_pemain_club.txt");
        if (!file.is_open()) {
            cout << "Error: Tidak dapat membuka file ../data/data_pemain_club.txt" << endl;
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            PemainKlub* newPemainKlub = new PemainKlub();
            stringstream ss(line);
            string temp;
            
            // Parse data pemain dengan delimiter |
            getline(ss, newPemainKlub->posisi, '|');
            getline(ss, newPemainKlub->nama, '|');
            getline(ss, temp, '|');
            newPemainKlub->usia = stoi(temp);
            getline(ss, temp, '|');
            newPemainKlub->no_punggung = stoi(temp);
            getline(ss, newPemainKlub->klub, '|');
            getline(ss, temp, '|');
            newPemainKlub->rating = stod(temp);
            getline(ss, temp, '|');
            newPemainKlub->timnas = (temp == "1");
            
            // Cari klub yang sesuai dan tambahkan pemain ke linked list
            for (auto& club : clubs) {
                if (club.nama == newPemainKlub->klub) {
                    addPemainKlubToClub(club, newPemainKlub);
                    break;
                }
            }
        }
        
        file.close();
        return true;
    }
    
    // Fungsi untuk menambahkan pemain ke linked list klub
    void addPemainKlubToClub(Club& club, PemainKlub* newPemainKlub) {
        if (club.pemain == nullptr) {
            club.pemain = newPemainKlub;
        } else {
            PemainKlub* current = club.pemain;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newPemainKlub;
        }
    }
    
    // Fungsi untuk menampilkan data klub (tanpa pemain)
    void displayClubInfo(const Club& club) {
        cout << "\n==================== INFORMASI KLUB ====================" << endl;
        cout << "Nama Klub    : " << club.nama << endl;
        cout << "Kota         : " << club.kota << endl;
        cout << "Stadion      : " << club.stadion << endl;
        cout << "Tahun Berdiri: " << club.tahunBerdiri << endl;
        cout << "Pelatih      : " << club.pelatih << endl;
        cout << "=========================================================" << endl;
    }
    
    // Fungsi untuk menampilkan semua pemain dalam klub
    void displayPemainKlubs(const Club& club) {
        cout << "\n=========================== DAFTAR PEMAIN " << club.nama << " ===========================\n";

        if (club.pemain == nullptr) {
            cout << "Tidak ada data pemain untuk klub ini." << endl;
            return;
        }

        cout << left << setw(4) << "No"
            << setw(25) << "Nama"
            << setw(10) << "Posisi"
            << setw(6)  << "Usia"
            << setw(14) << "No. Punggung"
            << setw(8)  << "Rating"
            << setw(10) << "Timnas" << "\n";
        cout << "===========================================================================================\n";

        PemainKlub* current = club.pemain;
        int count = 1;
        while (current != nullptr) {
            cout << left << setw(4) << count
                << setw(25) << current->nama
                << setw(10) << current->posisi
                << setw(6)  << current->usia
                << setw(14) << current->no_punggung
                << setw(8)  << fixed << setprecision(1) << current->rating
                << setw(10) << (current->timnas ? "Ya" : "Tidak") << "\n";
            current = current->next;
            count++;
        }

        cout << "===========================================================================================\n";
    }
    
    // Fungsi untuk mencari klub berdasarkan nama
    Club* findClub(const string& namaKlub) {
        for (auto& club : clubs) {
            if (club.nama == namaKlub) {
                return &club;
            }
        }
        return nullptr;
    }
    
    // Menu utama
    void mainMenu() {
        cout << "\n============== SISTEM MANAJEMEN KLUB SEPAK BOLA ==============" << endl;
        cout << "1. Lihat Klub" << endl;
        cout << "0. Kembali" << endl;
        cout << "===============================================================" << endl;
        cout << "Pilih menu: ";
    }
    
    // Menu pilihan klub
    void clubSelectionMenu() {
        cout << "\n==================== PILIH KLUB ====================" << endl;
        cout << "1. Persebaya Surabaya" << endl;
        cout << "2. Persib Bandung" << endl;
        cout << "3. Dewa United" << endl;
        cout << "4. Persija" << endl;
        cout << "5. Arema" << endl;
        cout << "0. Kembali" << endl;
        cout << "=====================================================" << endl;
        cout << "Pilih klub: ";
    }
    
    // Menu klub detail
    void clubDetailMenu() {
        cout << "\n==================== MENU KLUB ====================" << endl;
        cout << "1. Tampilkan Pemain" << endl;
        cout << "2. Kembali" << endl;
        cout << "====================================================" << endl;
        cout << "Pilih menu: ";
    }
    
    // Fungsi utama untuk menjalankan sistem
    void run() {
        // Load data dari file
        cout << "Memuat data klub..." << endl;
        if (!loadClubData()) {
            cout << "Gagal memuat data klub!" << endl;
            return;
        }
        
        cout << "Memuat data pemain..." << endl;
        if (!loadPemainKlubData()) {
            cout << "Gagal memuat data pemain!" << endl;
            return;
        }
        
        cout << "Data berhasil dimuat!" << endl;
        
        // Menu loop
        int choice;
        while (true) {
            mainMenu();
            cin >> choice;
            
            switch (choice) {
                case 1: {
                    int clubChoice;
                    while (true) {
                        clubSelectionMenu();
                        cin >> clubChoice;
                        
                        if (clubChoice == 0) break;
                        
                        string clubNames[] = {"", "Persebaya Surabaya", "Persib Bandung", 
                                            "Dewa United", "Persija Jakarta", "Arema FC"};
                        
                        if (clubChoice >= 1 && clubChoice <= 5) {
                            Club* selectedClub = findClub(clubNames[clubChoice]);
                            if (selectedClub != nullptr) {
                                displayClubInfo(*selectedClub);
                                
                                int detailChoice;
                                while (true) {
                                    clubDetailMenu();
                                    cin >> detailChoice;
                                    
                                    switch (detailChoice) {
                                        case 1:
                                            displayPemainKlubs(*selectedClub);
                                            break;
                                        case 2:
                                            goto club_selection; // Kembali ke menu pilih klub
                                        default:
                                            cout << "Pilihan tidak valid!" << endl;
                                            break;
                                    }
                                }
                            } else {
                                cout << "Klub tidak ditemukan!" << endl;
                            }
                        } else {
                            cout << "Pilihan tidak valid!" << endl;
                        }
                        club_selection:;
                    }
                    break;
                }
                case 0:
                    cout << "Terima kasih telah menggunakan sistem ini!" << endl;
                    return;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                    break;
            }
        }
    }
    
    // Destructor untuk membersihkan memory
    ~FootballClubSystem() {
        for (auto& club : clubs) {
            PemainKlub* current = club.pemain;
            while (current != nullptr) {
                PemainKlub* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

// Fungsi main
void menuKlub() {
    FootballClubSystem system;
    system.run();
}