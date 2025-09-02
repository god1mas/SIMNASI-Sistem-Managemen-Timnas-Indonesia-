#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Struct untuk Training Camp
struct TrainingCamp {
    int id;
    string nama_camp;
    string lokasi;
    string tanggal_mulai;   // DD/MM/YYYY
    string tanggal_selesai;
    int durasi_hari;
    int jumlah_pemain;
    string tujuan;          // "Persiapan Piala AFF", "TC Rutin", "Persiapan Kualifikasi"
    bool sedang_berlangsung;
    string pelatih_utama;
};

// Node untuk implementasi queue manual
struct TrainingQueueNode {
    TrainingCamp data;
    TrainingQueueNode* next;
    
    TrainingQueueNode(TrainingCamp tc) : data(tc), next(nullptr) {}
};

// Class untuk Queue manual
class TrainingQueue {
private:
    TrainingQueueNode* front;
    TrainingQueueNode* rear;
    int size;

public:
    TrainingQueue() : front(nullptr), rear(nullptr), size(0) {}
    
    // Copy constructor untuk menghindari masalah saat passing by value
    TrainingQueue(const TrainingQueue& other) : front(nullptr), rear(nullptr), size(0) {
        TrainingQueueNode* current = other.front;
        while (current != nullptr) {
            enqueue(current->data);
            current = current->next;
        }
    }
    
    // Assignment operator
    TrainingQueue& operator=(const TrainingQueue& other) {
        if (this != &other) {
            // Clear current queue
            while (!isEmpty()) {
                dequeue();
            }
            
            // Copy from other
            TrainingQueueNode* current = other.front;
            while (current != nullptr) {
                enqueue(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    ~TrainingQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    void enqueue(TrainingCamp tc) {
        TrainingQueueNode* newNode = new TrainingQueueNode(tc);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    void dequeue() {
        if (isEmpty()) return;
        
        TrainingQueueNode* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
    }
    
    TrainingCamp getFront() {
        if (!isEmpty()) {
            return front->data;
        }
        return TrainingCamp{}; // Return empty struct jika kosong
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    int getSize() {
        return size;
    }
    
    // Method untuk display semua data dalam queue
    void displayAll() {
        TrainingQueueNode* current = front;
        int counter = 1;
        
        cout << "\n" << string(80, '=') << endl;
        cout << "              ANTRIAN TRAINING CAMP TIMNAS INDONESIA" << endl;
        cout << string(80, '=') << endl;
        
        if (isEmpty()) {
            cout << "Tidak ada training camp yang terjadwal." << endl;
            return;
        }
        
        while (current != nullptr) {
            cout << "\n[" << counter << "] Training Camp Details:" << endl;
            cout << string(40, '-') << endl;
            cout << "ID               : " << current->data.id << endl;
            cout << "Nama Camp        : " << current->data.nama_camp << endl;
            cout << "Lokasi           : " << current->data.lokasi << endl;
            cout << "Tanggal Mulai    : " << current->data.tanggal_mulai << endl;
            cout << "Tanggal Selesai  : " << current->data.tanggal_selesai << endl;
            cout << "Durasi           : " << current->data.durasi_hari << " hari" << endl;
            cout << "Jumlah Pemain    : " << current->data.jumlah_pemain << " orang" << endl;
            cout << "Tujuan           : " << current->data.tujuan << endl;
            cout << "Status           : " << (current->data.sedang_berlangsung ? "Sedang Berlangsung" : "Belum Dimulai") << endl;
            cout << "Pelatih Utama    : " << current->data.pelatih_utama << endl;
            
            current = current->next;
            counter++;
        }
        cout << "\nTotal Training Camp dalam antrian: " << size << endl;
    }
};

// Function untuk mengkonversi tanggal DD/MM/YYYY ke format yang bisa dibandingkan
int TrainingdataToInt(string date) {
    // Validasi format tanggal
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
        return 0; // Return 0 jika format tidak valid
    }
    
    try {
        string day = date.substr(0, 2);
        string month = date.substr(3, 2);
        string year = date.substr(6, 4);
        
        return stoi(year) * 10000 + stoi(month) * 100 + stoi(day);
    } catch (...) {
        return 0; // Return 0 jika terjadi error parsing
    }
}

// Function untuk parsing line dari file
TrainingCamp parseLine(string line) {
    TrainingCamp tc = {}; // Initialize dengan nilai default
    stringstream ss(line);
    string token;
    int field = 0;
    
    try {
        while (getline(ss, token, '|') && field < 10) {
            switch (field) {
                case 0: tc.id = stoi(token); break;
                case 1: tc.nama_camp = token; break;
                case 2: tc.lokasi = token; break;
                case 3: tc.tanggal_mulai = token; break;
                case 4: tc.tanggal_selesai = token; break;
                case 5: tc.durasi_hari = stoi(token); break;
                case 6: tc.jumlah_pemain = stoi(token); break;
                case 7: tc.tujuan = token; break;
                case 8: tc.sedang_berlangsung = (stoi(token) == 1); break;
                case 9: tc.pelatih_utama = token; break;
            }
            field++;
        }
    } catch (...) {
        // Jika terjadi error parsing, return struct kosong
        tc = {};
    }
    
    return tc;
}

// Function untuk load data dan sort berdasarkan tanggal
TrainingQueue loadTrainingData() {
    TrainingQueue queue;
    TrainingCamp camps[100]; // Array sementara untuk sorting
    int count = 0;
    
    ifstream file("../data/data_latihan.txt");
    string line;
    
    if (!file.is_open()) {
        cout << "Error: Tidak dapat membuka file data_latihan.txt" << endl;
        // Buat beberapa data dummy untuk testing
        TrainingCamp dummy1 = {1, "TC Persiapan AFF", "Jakarta", "15/01/2025", "25/01/2025", 10, 25, "Persiapan Piala AFF", false, "Shin Tae-yong"};
        TrainingCamp dummy2 = {2, "TC Rutin Bulanan", "Yogyakarta", "01/02/2025", "10/02/2025", 9, 23, "TC Rutin", false, "Shin Tae-yong"};
        queue.enqueue(dummy1);
        queue.enqueue(dummy2);
        return queue;
    }
    
    // Baca semua data ke array
    while (getline(file, line) && count < 100) {
        if (!line.empty()) { // Skip empty lines
            camps[count] = parseLine(line);
            if (camps[count].id != 0) { // Only add valid data
                count++;
            }
        }
    }
    file.close();
    
    if (count == 0) {
        cout << "Warning: File kosong atau tidak ada data valid" << endl;
        return queue;
    }
    
    // Simple bubble sort berdasarkan tanggal mulai
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (TrainingdataToInt(camps[j].tanggal_mulai) > TrainingdataToInt(camps[j + 1].tanggal_mulai)) {
                TrainingCamp temp = camps[j];
                camps[j] = camps[j + 1];
                camps[j + 1] = temp;
            }
        }
    }
    
    // Masukkan data yang sudah terurut ke queue
    for (int i = 0; i < count; i++) {
        queue.enqueue(camps[i]);
    }
    
    return queue;
}

// Function untuk menampilkan training camp yang sedang berlangsung
void tampilkanSedangBerlangsung() {
    cout << "\n" << string(60, '=') << endl;
    cout << "         TRAINING CAMP YANG SEDANG BERLANGSUNG" << endl;
    cout << string(60, '=') << endl;
    
    TrainingQueue tempQueue = loadTrainingData();
    bool found = false;
    
    while (!tempQueue.isEmpty()) {
        TrainingCamp tc = tempQueue.getFront();
        if (tc.sedang_berlangsung) {
            found = true;
            cout << "\n>> " << tc.nama_camp << " <<" << endl;
            cout << "Lokasi    : " << tc.lokasi << endl;
            cout << "Durasi    : " << tc.tanggal_mulai << " - " << tc.tanggal_selesai << endl;
            cout << "Pelatih   : " << tc.pelatih_utama << endl;
            cout << "Pemain    : " << tc.jumlah_pemain << " orang" << endl;
            cout << "Tujuan    : " << tc.tujuan << endl;
        }
        tempQueue.dequeue();
    }
    
    if (!found) {
        cout << "\nTidak ada training camp yang sedang berlangsung saat ini." << endl;
    }
}

// Function untuk menampilkan training camp berdasarkan tujuan
void tampilkanBerdasarkanTujuan() {
    cout << "\n" << string(50, '=') << endl;
    cout << "    FILTER BERDASARKAN TUJUAN TRAINING" << endl;
    cout << string(50, '=') << endl;
    
    cout << "1. Persiapan Piala AFF" << endl;
    cout << "2. TC Rutin" << endl;
    cout << "3. Persiapan Kualifikasi" << endl;
    cout << "Pilih kategori (1-3): ";
    
    int pilihan;
    if (!(cin >> pilihan)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid!" << endl;
        return;
    }
    
    string tujuan;
    switch (pilihan) {
        case 1: tujuan = "Persiapan Piala AFF"; break;
        case 2: tujuan = "TC Rutin"; break;
        case 3: tujuan = "Persiapan Kualifikasi"; break;
        default: 
            cout << "Pilihan tidak valid!" << endl;
            return;
    }
    
    cout << "\n--- Training Camp: " << tujuan << " ---" << endl;
    
    TrainingQueue tempQueue = loadTrainingData();
    bool found = false;
    int counter = 1;
    
    while (!tempQueue.isEmpty()) {
        TrainingCamp tc = tempQueue.getFront();
        if (tc.tujuan == tujuan) {
            found = true;
            cout << "\n[" << counter << "] " << tc.nama_camp << endl;
            cout << "    Lokasi: " << tc.lokasi << endl;
            cout << "    Jadwal: " << tc.tanggal_mulai << " - " << tc.tanggal_selesai << endl;
            cout << "    Pelatih: " << tc.pelatih_utama << endl;
            counter++;
        }
        tempQueue.dequeue();
    }
    
    if (!found) {
        cout << "Tidak ada training camp dengan tujuan tersebut." << endl;
    }
}

// Function untuk menampilkan training camp terdekat
void tampilkanTerdekat(TrainingQueue& queue) {
    cout << "\n" << string(50, '=') << endl;
    cout << "       TRAINING CAMP TERDEKAT" << endl;
    cout << string(50, '=') << endl;
    
    if (queue.isEmpty()) {
        cout << "Tidak ada training camp yang terjadwal." << endl;
        return;
    }
    
    TrainingCamp next = queue.getFront();
    cout << "\n>> TRAINING CAMP SELANJUTNYA <<" << endl;
    cout << "Nama        : " << next.nama_camp << endl;
    cout << "Lokasi      : " << next.lokasi << endl;
    cout << "Mulai       : " << next.tanggal_mulai << endl;
    cout << "Selesai     : " << next.tanggal_selesai << endl;
    cout << "Durasi      : " << next.durasi_hari << " hari" << endl;
    cout << "Pemain      : " << next.jumlah_pemain << " orang" << endl;
    cout << "Tujuan      : " << next.tujuan << endl;
    cout << "Pelatih     : " << next.pelatih_utama << endl;
    cout << "Status      : " << (next.sedang_berlangsung ? "Sedang Berlangsung" : "Belum Dimulai") << endl;
}

// Function untuk statistik singkat
void tampilkanStatistik() {
    cout << "\n" << string(50, '=') << endl;
    cout << "          STATISTIK TRAINING CAMP" << endl;
    cout << string(50, '=') << endl;
    
    TrainingQueue tempQueue = loadTrainingData();
    int totalTC = 0, sedangBerlangsung = 0;
    int totalPemain = 0;
    int pialaAFF = 0, tcRutin = 0, kualifikasi = 0;
    
    while (!tempQueue.isEmpty()) {
        TrainingCamp tc = tempQueue.getFront();
        totalTC++;
        totalPemain += tc.jumlah_pemain;
        
        if (tc.sedang_berlangsung) sedangBerlangsung++;
        
        if (tc.tujuan == "Persiapan Piala AFF") pialaAFF++;
        else if (tc.tujuan == "TC Rutin") tcRutin++;
        else if (tc.tujuan == "Persiapan Kualifikasi") kualifikasi++;
        
        tempQueue.dequeue();
    }
    
    cout << "\nTotal Training Camp     : " << totalTC << endl;
    cout << "Sedang Berlangsung      : " << sedangBerlangsung << endl;
    cout << "Total Pemain Terlibat   : " << totalPemain << endl;
    cout << "Rata-rata Pemain/TC     : " << (totalTC > 0 ? totalPemain/totalTC : 0) << endl;
    cout << "\nKategori Tujuan:" << endl;
    cout << "  - Persiapan Piala AFF : " << pialaAFF << endl;
    cout << "  - TC Rutin            : " << tcRutin << endl;
    cout << "  - Persiapan Kualifikasi: " << kualifikasi << endl;
}

// Function untuk menampilkan menu
void tampilkanMenu() {
    cout << "\n" << string(60, '=') << endl;
    cout << "           MENU MANAJEMEN TRAINING CAMP TIMNAS" << endl;
    cout << string(60, '=') << endl;
    cout << "1. Tampilkan Semua Antrian Training Camp" << endl;
    cout << "2. Tampilkan Training Camp Terdekat" << endl;
    cout << "3. Tampilkan Training Camp Sedang Berlangsung" << endl;
    cout << "4. Filter Berdasarkan Tujuan" << endl;
    cout << "5. Statistik Training Camp" << endl;
    cout << "0. Kembali ke Menu Utama" << endl;
    cout << string(60, '=') << endl;
    cout << "Pilih menu (1-6): ";
}

void latihan() {
    TrainingQueue trainingQueue;
    int pilihan;
    
    cout << string(60, '=') << endl;
    cout << "    SISTEM MANAJEMEN TRAINING CAMP TIMNAS INDONESIA" << endl;
    cout << string(60, '=') << endl;
    cout << "Loading data training camp..." << endl;
    
    trainingQueue = loadTrainingData();
    
    cout << "Data berhasil dimuat! Total: " << trainingQueue.getSize() << " training camp" << endl;
    
    do {
        tampilkanMenu();
        
        // Validasi input
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInput tidak valid! Silakan masukkan angka 1-6." << endl;
            continue;
        }
        
        switch (pilihan) {
            case 1:
                trainingQueue.displayAll();
                break;
            case 2:
                tampilkanTerdekat(trainingQueue);
                break;
            case 3:
                tampilkanSedangBerlangsung();
                break;
            case 4:
                tampilkanBerdasarkanTujuan();
                break;
            case 5:
                tampilkanStatistik();
                break;
            case 0:
                cout << "\nKembali ke menu utama..." << endl;
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan pilih 1-6." << endl;
        }
        
        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }

    } while (pilihan != 0);
}