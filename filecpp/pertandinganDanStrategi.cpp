//implementasi stack dan queue untuk menyimpan jadwal dan riwayat pertandingan timnas Indonesia
//dengan fitur atur strategi pertandingan mendatang

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

const int MAX_PEMAIN = 11;

struct PertandinganTimnas {
    string lawan;
    string tanggal;
    string tempat;
    string jenisLaga;
    string status;
    int skorTimnas;
    int skorLawan;
    bool sudahTanding;
};

struct Strategi {
    int id;
    string namaStrategi;
    string formasi;
    string instruksi;
    Strategi* next;
    
    Strategi() : next(nullptr) {}
    Strategi(int _id, string _nama, string _formasi, string _instruksi) 
        : id(_id), namaStrategi(_nama), formasi(_formasi), instruksi(_instruksi), next(nullptr) {}
};

// Global variables untuk menyimpan strategi yang dipilih untuk pertandingan tertentu
int selectedMatchIndex = -1;
string selectedMatchInfo = "";

int dateToInt(string tanggal);

// Node untuk Queue (Jadwal Pertandingan)
struct QueueNode {
    PertandinganTimnas data;
    QueueNode* next;
    
    QueueNode(PertandinganTimnas p) : data(p), next(nullptr) {}
};

// Node untuk Stack (Riwayat Pertandingan)
struct StackNode {
    PertandinganTimnas data;
    StackNode* next;
    
    StackNode(PertandinganTimnas p) : data(p), next(nullptr) {}
};

// Stack untuk menyimpan strategi yang dipilih
class StrategiStack {
private:
    Strategi* top;
    int size;
    
public:
    StrategiStack() : top(nullptr), size(0) {}
    
    void push(Strategi s) {
        Strategi* newNode = new Strategi(s.id, s.namaStrategi, s.formasi, s.instruksi);
        newNode->next = top;
        top = newNode;
        size++;
    }
    
    bool isEmpty() {
        return top == nullptr;
    }
    
    int getSize() {
        return size;
    }
    
    Strategi getAt(int index) {
        if (isEmpty() || index < 0 || index >= size) {
            return Strategi(); // Return empty strategi
        }
        
        Strategi* current = top;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        return *current;
    }
    
    void clear() {
        while (top != nullptr) {
            Strategi* temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }
    
    ~StrategiStack() {
        clear();
    }
};

// Global stack untuk strategi yang dipilih
StrategiStack selectedStrategies;

// Implementasi Queue
class JadwalQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int size;
    
public:
    JadwalQueue() : front(nullptr), rear(nullptr), size(0) {}
    
    void enqueue(PertandinganTimnas p) {
        QueueNode* newNode = new QueueNode(p);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    int getSize() {
        return size;
    }
    
    PertandinganTimnas getAt(int index) {
        QueueNode* current = front;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    // Method untuk sorting berdasarkan tanggal
    void sortByDate() {
        if (isEmpty()) return;
        
        bool swapped;
        do {
            swapped = false;
            QueueNode* current = front;
            while (current != nullptr && current->next != nullptr) {
                if (dateToInt(current->data.tanggal) > dateToInt(current->next->data.tanggal)) {
                    // Swap data
                    PertandinganTimnas temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }
    
    ~JadwalQueue() {
        while (front != nullptr) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

// Implementasi Stack
class RiwayatStack {
private:
    StackNode* top;
    int size;
    
public:
    RiwayatStack() : top(nullptr), size(0) {}
    
    void push(PertandinganTimnas p) {
        StackNode* newNode = new StackNode(p);
        newNode->next = top;
        top = newNode;
        size++;
    }
    
    bool isEmpty() {
        return top == nullptr;
    }
    
    int getSize() {
        return size;
    }
    
    PertandinganTimnas getAt(int index) {
        StackNode* current = top;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    ~RiwayatStack() {
        while (top != nullptr) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

// Fungsi untuk mengubah string tanggal DD-MM-YYYY menjadi integer untuk perbandingan
int dateToInt(string tanggal) {
    int day = stoi(tanggal.substr(0, 2));
    int month = stoi(tanggal.substr(3, 2));
    int year = stoi(tanggal.substr(6, 4));
    return year * 10000 + month * 100 + day;
}

// Fungsi untuk membaca strategi dari file
vector<Strategi> bacaStrategiDariFile() {
    vector<Strategi> strategiList;
    ifstream file("../data/data_strategi.txt"); // Ubah path menjadi relatif
    
    if (!file.is_open()) {
        cout << "Error: Tidak dapat membuka file ../data/data_strategi.txt" << endl;
        cout << "Pastikan file ../data/data_strategi.txt ada di direktori yang sama dengan program." << endl;
        system("pause");
        return strategiList;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        try {
            stringstream ss(line);
            string token;
            Strategi s;
            
            // Parse data dengan delimiter |
            if (!getline(ss, token, '|') || token.empty()) {
                cout << "Warning: Baris data tidak valid (ID kosong): " << line << endl;
                continue;
            }
            s.id = stoi(token);
            
            if (!getline(ss, s.namaStrategi, '|')) {
                cout << "Warning: Nama strategi tidak ditemukan pada baris: " << line << endl;
                continue;
            }
            
            if (!getline(ss, s.formasi, '|')) {
                cout << "Warning: Formasi tidak ditemukan pada baris: " << line << endl;
                continue;
            }
            
            if (!getline(ss, s.instruksi, '|')) {
                cout << "Warning: Instruksi tidak ditemukan pada baris: " << line << endl;
                continue;
            }
            
            strategiList.push_back(s);
        }
        catch (const exception& e) {
            cout << "Error parsing baris: " << line << endl;
            cout << "Error: " << e.what() << endl;
            continue;
        }
    }
    
    file.close();
    cout << "Berhasil membaca " << strategiList.size() << " strategi dari file." << endl;
    return strategiList;
}

// Fungsi untuk menulis strategi ke file
void tulisStrategiKeFile(const vector<Strategi>& strategiList) {
    ofstream file("../data/data_strategi.txt"); // Ubah path menjadi relatif
    
    if (!file.is_open()) {
        cout << "Error: Tidak dapat membuka file ../data/data_strategi.txt untuk menulis" << endl;
        cout << "Pastikan direktori dapat ditulis." << endl;
        system("pause");
        return;
    }
    
    for (const auto& s : strategiList) {
        file << s.id << "|" << s.namaStrategi << "|" << s.formasi << "|" << s.instruksi << endl;
    }
    
    file.close();
    cout << "Strategi berhasil disimpan ke file!" << endl;
}

// Fungsi untuk membaca data dari file
void bacaDataPertandingan(JadwalQueue& jadwal, RiwayatStack& riwayat) {
    ifstream file("../data/data_pertandingan.txt");
    if (!file.is_open()) {
        cout << "Error: Tidak dapat membuka file data_pertandingan.txt" << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        PertandinganTimnas p;
        
        // Parse data dengan delimiter |
        getline(ss, p.lawan, '|');
        getline(ss, p.tanggal, '|');
        getline(ss, p.tempat, '|');
        getline(ss, p.jenisLaga, '|');
        getline(ss, p.status, '|');
        
        getline(ss, token, '|');
        p.skorTimnas = stoi(token);
        
        getline(ss, token, '|');
        p.skorLawan = stoi(token);
        
        getline(ss, token, '|');
        p.sudahTanding = (token == "1" || token == "true");
        
        if (p.sudahTanding) {
            riwayat.push(p);
        } else {
            jadwal.enqueue(p);
        }
    }
    
    file.close();
    
    // Sorting jadwal berdasarkan tanggal
    jadwal.sortByDate();
}

// Fungsi untuk menampilkan detail pertandingan
void tampilkanPertandingan(PertandinganTimnas p) {
    cout << "\n========================================" << endl;
    cout << "Lawan         : " << p.lawan << endl;
    cout << "Tanggal       : " << p.tanggal << endl;
    cout << "Tempat        : " << p.tempat << endl;
    cout << "Jenis Laga    : " << p.jenisLaga << endl;
    cout << "Status        : " << p.status << endl;
    
    if (p.sudahTanding) {
        cout << "Skor          : Indonesia " << p.skorTimnas << " - " << p.skorLawan << " " << p.lawan << endl;
        string hasil;
        if (p.skorTimnas > p.skorLawan) hasil = "MENANG";
        else if (p.skorTimnas < p.skorLawan) hasil = "KALAH";
        else hasil = "SERI";
        cout << "Hasil         : " << hasil << endl;
    } else {
        cout << "Status        : Belum Tanding" << endl;
    }
    cout << "========================================" << endl;
}

// Fungsi untuk menampilkan strategi
void tampilkanStrategi(const Strategi& s) {
    cout << "\n========================================" << endl;
    cout << "ID Strategi   : " << s.id << endl;
    cout << "Nama Strategi : " << s.namaStrategi << endl;
    cout << "Formasi       : " << s.formasi << endl;
    cout << "Instruksi     : " << s.instruksi << endl;
    cout << "========================================" << endl;
}

// Menu untuk edit strategi
Strategi editStrategi(Strategi s) {
    Strategi edited = s;
    int pilihan;
    
    do {
        system("cls");
        cout << "\n=== EDIT STRATEGI ===" << endl;
        tampilkanStrategi(edited);
        
        cout << "\nApa yang ingin diedit?" << endl;
        cout << "1. Nama Strategi" << endl;
        cout << "2. Formasi" << endl;
        cout << "3. Instruksi" << endl;
        cout << "4. Selesai Edit" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(); // Clear buffer
        
        switch (pilihan) {
            case 1: {
                cout << "Nama Strategi baru: ";
                getline(cin, edited.namaStrategi);
                break;
            }
            case 2: {
                cout << "Formasi baru: ";
                getline(cin, edited.formasi);
                break;
            }
            case 3: {
                cout << "Instruksi baru: ";
                getline(cin, edited.instruksi);
                break;
            }
            case 4:
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                system("pause");
        }
    } while (pilihan != 4);
    
    return edited;
}

// Menu untuk memilih strategi dari default
void menuPilihStrategi() {
    cout << "Sedang membaca data strategi..." << endl;
    vector<Strategi> strategiList = bacaStrategiDariFile();
    
    if (strategiList.empty()) {
        cout << "\nTidak ada strategi yang tersedia!" << endl;
        cout << "Pastikan file ../data/data_strategi.txt tersedia dan berisi data yang valid." << endl;
        cout << "\nFormat data dalam file harus: ID|Nama|Formasi|Instruksi" << endl;
        cout << "Contoh: 1|Serangan Balik Cepat|4-2-3-1|Bertahan lalu meluncurkan serangan cepat" << endl;
        system("pause");
        return;
    }
    
    int currentIndex = 0;
    char pilihan;
    
    do {
        system("cls");
        cout << "\n=== PILIH STRATEGI DEFAULT ===" << endl;
        cout << "Strategi ke-" << (currentIndex + 1) << " dari " << strategiList.size() << endl;
        
        Strategi current = strategiList[currentIndex];
        tampilkanStrategi(current);
        
        if (!selectedStrategies.isEmpty()) {
            cout << "\nStrategi yang sudah dipilih: " << selectedStrategies.getSize() << " strategi" << endl;
        }
        
        cout << "\nMenu:" << endl;
        cout << "1. Edit Strategi" << endl;
        cout << "2. Pilih Strategi (tambah ke daftar)" << endl;
        cout << "3. Next" << endl;
        cout << "4. Back" << endl;
        cout << "5. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input tidak valid!" << endl;
            system("pause");
            continue;
        }
        
        switch (pilihan) {
            case '1': {
                Strategi edited = editStrategi(current);
                strategiList[currentIndex] = edited;
                tulisStrategiKeFile(strategiList);
                cout << "Strategi berhasil diedit dan disimpan!" << endl;
                system("pause");
                break;
            }
            case '2': {
                selectedStrategies.push(current);
                cout << "Strategi '" << current.namaStrategi << "' berhasil ditambahkan!" << endl;
                system("pause");
                break;
            }
            case '3': {
                if (currentIndex < (int)strategiList.size() - 1) {
                    currentIndex++;
                } else {
                    cout << "Ini adalah strategi terakhir!" << endl;
                    system("pause");
                }
                break;
            }
            case '4': {
                if (currentIndex > 0) {
                    currentIndex--;
                } else {
                    cout << "Ini adalah strategi pertama!" << endl;
                    system("pause");
                }
                break;
            }
            case '5':
                cout << "Kembali ke menu sebelumnya..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                system("pause");
        }
    } while (pilihan != '5');
}

// Menu untuk menampilkan strategi yang dipilih
void menuTampilkanStrategi() {
    if (selectedStrategies.isEmpty()) {
        cout << "\nBelum ada strategi yang dipilih untuk pertandingan ini." << endl;
        cout << "Silakan pilih strategi terlebih dahulu." << endl;
        system("pause");
        return;
    }
    
    int currentIndex = 0;
    char pilihan;
    
    do {
        system("cls");
        cout << "\n=== STRATEGI YANG DIPILIH ===" << endl;
        if (selectedMatchIndex >= 0) {
            cout << "Untuk pertandingan: " << selectedMatchInfo << endl;
        }
        cout << "Strategi ke-" << (currentIndex + 1) << " dari " << selectedStrategies.getSize() << endl;
        
        Strategi current = selectedStrategies.getAt(currentIndex);
        tampilkanStrategi(current);
        
        cout << "\nNavigasi:" << endl;
        cout << "n/N - Next (Selanjutnya)" << endl;
        cout << "b/B - Back (Sebelumnya)" << endl;
        cout << "x/X - Kembali ke menu utama" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 'n':
            case 'N':
                if (currentIndex < selectedStrategies.getSize() - 1) {
                    currentIndex++;
                } else {
                    cout << "Ini adalah strategi terakhir!" << endl;
                    system("pause");
                }
                break;
            case 'b':
            case 'B':
                if (currentIndex > 0) {
                    currentIndex--;
                } else {
                    cout << "Ini adalah strategi pertama!" << endl;
                    system("pause");
                }
                break;
            case 'x':
            case 'X':
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                system("pause");
        }
    } while (pilihan != 'x' && pilihan != 'X');
}

// Menu untuk memilih pertandingan yang akan diatur strateginya
void menuPilihPertandingan(JadwalQueue& jadwal) {
    if (jadwal.isEmpty()) {
        cout << "\nTidak ada jadwal pertandingan yang tersedia." << endl;
        system("pause");
        return;
    }
    
    int currentIndex = 0;
    char pilihan;
    
    do {
        system("cls");
        cout << "\n=== PILIH PERTANDINGAN UNTUK ATUR STRATEGI ===" << endl;
        cout << "Pertandingan ke-" << (currentIndex + 1) << " dari " << jadwal.getSize() << endl;
        
        PertandinganTimnas current = jadwal.getAt(currentIndex);
        tampilkanPertandingan(current);
        
        if (selectedMatchIndex == currentIndex) {
            cout << "\n*** PERTANDINGAN INI SUDAH DIPILIH ***" << endl;
        }
        
        cout << "\nMenu:" << endl;
        cout << "s/S - Pilih pertandingan ini untuk atur strategi" << endl;
        cout << "n/N - Next (Selanjutnya)" << endl;
        cout << "b/B - Back (Sebelumnya)" << endl;
        cout << "x/X - Kembali ke menu utama" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 's':
            case 'S': {
                selectedMatchIndex = currentIndex;
                selectedMatchInfo = current.lawan + " (" + current.tanggal + ")";
                selectedStrategies.clear(); // Clear previous strategies
                cout << "\nPertandingan vs " << current.lawan << " berhasil dipilih!" << endl;
                cout << "Sekarang Anda dapat mengatur strategi untuk pertandingan ini." << endl;
                system("pause");
                return;
            }
            case 'n':
            case 'N':
                if (currentIndex < jadwal.getSize() - 1) {
                    currentIndex++;
                } else {
                    cout << "Ini adalah jadwal terakhir!" << endl;
                    system("pause");
                }
                break;
            case 'b':
            case 'B':
                if (currentIndex > 0) {
                    currentIndex--;
                } else {
                    cout << "Ini adalah jadwal pertama!" << endl;
                    system("pause");
                }
                break;
            case 'x':
            case 'X':
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                system("pause");
        }
    } while (pilihan != 'x' && pilihan != 'X');
}

// Menu utama untuk atur strategi
void menuAturStrategi(JadwalQueue& jadwal) {
    int pilihan;
    
    do {
        system("cls");
        cout << "\n========================================" << endl;
        cout << "    ATUR STRATEGI PERTANDINGAN MENDATANG" << endl;
        cout << "========================================" << endl;
        
        if (selectedMatchIndex >= 0) {
            cout << "Pertandingan yang dipilih: " << selectedMatchInfo << endl;
            cout << "Jumlah strategi dipilih: " << selectedStrategies.getSize() << endl;
        } else {
            cout << "Belum ada pertandingan yang dipilih" << endl;
        }
        
        cout << "========================================" << endl;
        cout << "1. Tampilkan Strategi yang Dipilih" << endl;
        cout << "2. Pilih/Edit Strategi" << endl;
        cout << "3. Pilih Pertandingan" << endl;
        cout << "4. Kembali ke Menu Utama" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                menuTampilkanStrategi();
                break;
            case 2:
                if (selectedMatchIndex >= 0) {
                    menuPilihStrategi();
                } else {
                    cout << "\nSilakan pilih pertandingan terlebih dahulu!" << endl;
                    system("pause");
                }
                break;
            case 3:
                menuPilihPertandingan(jadwal);
                break;
            case 4:
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
                system("pause");
        }
    } while (pilihan != 4);
}

// Menu Jadwal Pertandingan
void menuJadwalPertandingan(JadwalQueue& jadwal) {
    if (jadwal.isEmpty()) {
        cout << "\nTidak ada jadwal pertandingan yang tersedia." << endl;
        return;
    }
    
    int currentIndex = 0;
    char pilihan;
    
    do {
        system("cls"); // Untuk Windows, gunakan system("clear") untuk Linux/Mac
        cout << "\n=== JADWAL PERTANDINGAN TIMNAS INDONESIA ===" << endl;
        cout << "Pertandingan ke-" << (currentIndex + 1) << " dari " << jadwal.getSize() << endl;
        
        PertandinganTimnas current = jadwal.getAt(currentIndex);
        tampilkanPertandingan(current);
        
        cout << "\nNavigasi:" << endl;
        cout << "n/N - Next (Selanjutnya)" << endl;
        cout << "b/B - Back (Sebelumnya)" << endl;
        cout << "x/X - Kembali ke menu utama" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 'n':
            case 'N':
                if (currentIndex < jadwal.getSize() - 1) {
                    currentIndex++;
                } else {
                    cout << "Ini adalah jadwal terakhir!" << endl;
                    system("pause");
                }
                break;
            case 'b':
            case 'B':
                if (currentIndex > 0) {
                    currentIndex--;
                } else {
                    cout << "Ini adalah jadwal pertama!" << endl;
                    system("pause");
                }
                break;
            case 'x':
            case 'X':
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                system("pause");
        }
    } while (pilihan != 'x' && pilihan != 'X');
}

// Menu Riwayat Pertandingan
void menuRiwayatPertandingan(RiwayatStack& riwayat) {
    if (riwayat.isEmpty()) {
        cout << "\nTidak ada riwayat pertandingan yang tersedia." << endl;
        return;
    }
    
    int currentIndex = 0;
    char pilihan;
    
    do {
        system("cls"); // Untuk Windows, gunakan system("clear") untuk Linux/Mac
        cout << "\n=== RIWAYAT PERTANDINGAN TIMNAS INDONESIA ===" << endl;
        cout << "Pertandingan ke-" << (currentIndex + 1) << " dari " << riwayat.getSize() << endl;
        cout << "(Urutan dari yang terbaru)" << endl;
        
        PertandinganTimnas current = riwayat.getAt(currentIndex);
        tampilkanPertandingan(current);
        
        cout << "\nNavigasi:" << endl;
        cout << "n/N - Next (Selanjutnya)" << endl;
        cout << "b/B - Back (Sebelumnya)" << endl;
        cout << "x/X - Kembali ke menu utama" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 'n':
            case 'N':
                if (currentIndex < riwayat.getSize() - 1) {
                    currentIndex++;
                } else {
                    cout << "Ini adalah riwayat terakhir!" << endl;
                    system("pause");
                }
                break;
            case 'b':
            case 'B':
                if (currentIndex > 0) {
                    currentIndex--;
                } else {
                    cout << "Ini adalah riwayat pertama!" << endl;
                    system("pause");
                }
                break;
            case 'x':
            case 'X':
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                system("pause");
        }
    } while (pilihan != 'x' && pilihan != 'X');
}

void jadwalPertandingan() {
    JadwalQueue jadwal;
    RiwayatStack riwayat;
    
    // Baca data dari file
    bacaDataPertandingan(jadwal, riwayat);
    
    int pilihan;
    
    do {
        system("cls"); // Untuk Windows, gunakan system("clear") untuk Linux/Mac
        cout << "\n========================================" << endl;
        cout << "    MENU PERTANDINGAN TIMNAS INDONESIA" << endl;
        cout << "========================================" << endl;
        cout << "1. Jadwal Pertandingan" << endl;
        cout << "2. Atur Strategi Pertandingan Mendatang" << endl;
        cout << "3. Riwayat Pertandingan" << endl;
        cout << "4. Keluar" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                menuJadwalPertandingan(jadwal);
                break;
            case 2:
                menuAturStrategi(jadwal);
                break;
            case 3:
                menuRiwayatPertandingan(riwayat);
                break;
            case 4:
                cout << "\nTerima kasih! Program selesai." << endl;
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
                system("pause");
        }
    } while (pilihan != 4);
}