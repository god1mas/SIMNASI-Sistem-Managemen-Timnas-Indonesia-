//implementasi sorting, searching, hash table, dan binary search tree

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Pemain {
    string posisi;
    string nama;
    int usia;
    int no_punggung;
    string klub;
    double rating;
    bool timnas;
};

// Binary Search Tree untuk pencarian nama
struct BSTNode {
    Pemain data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(Pemain p) : data(p), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;
    
    BSTNode* insert(BSTNode* node, Pemain p) {
        if (node == nullptr) {
            return new BSTNode(p);
        }
        
        if (p.nama < node->data.nama) {
            node->left = insert(node->left, p);
        } else {
            node->right = insert(node->right, p);
        }
        return node;
    }
    
    BSTNode* search(BSTNode* node, string nama) {
        if (node == nullptr || node->data.nama == nama) {
            return node;
        }
        
        if (nama < node->data.nama) {
            return search(node->left, nama);
        }
        return search(node->right, nama);
    }
    
public:
    BST() : root(nullptr) {}
    
    void insert(Pemain p) {
        root = insert(root, p);
    }
    
    Pemain* search(string nama) {
        BSTNode* result = search(root, nama);
        return result ? &(result->data) : nullptr;
    }
};

// Hash Table untuk pencarian nomor punggung
class HashTable {
private:
    static const int TABLE_SIZE = 100;
    
    struct HashNode {
        int key;
        Pemain data;
        HashNode* next;
        
        HashNode(int k, Pemain p) : key(k), data(p), next(nullptr) {}
    };
    
    HashNode* table[TABLE_SIZE];
    
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }
    
public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
    
    void insert(int key, Pemain p) {
        int index = hashFunction(key);
        HashNode* newNode = new HashNode(key, p);
        
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }
    
    Pemain* search(int key) {
        int index = hashFunction(key);
        HashNode* current = table[index];
        
        while (current != nullptr) {
            if (current->key == key) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }
};

// Fungsi untuk mengkonversi posisi ke angka untuk sorting
int posisiToInt(string posisi) {
    if (posisi == "GK") return 1;
    if (posisi == "DF") return 2;
    if (posisi == "MF") return 3;
    if (posisi == "FW") return 4;
    return 5;
}

// Bubble Sort untuk posisi
void bubbleSortPosisi(Pemain arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (posisiToInt(arr[j].posisi) > posisiToInt(arr[j + 1].posisi)) {
                Pemain temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Merge Sort untuk nama
void merge(Pemain arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Pemain* leftArr = new Pemain[n1];
    Pemain* rightArr = new Pemain[n2];
    
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i].nama <= rightArr[j].nama) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
    
    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(Pemain arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Selection Sort untuk rating
void selectionSortRating(Pemain arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].rating > arr[maxIdx].rating) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Pemain temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
        }
    }
}

// Linear Search untuk posisi
void linearSearchPosisi(Pemain arr[], int n, string posisi) {
    bool found = false;
    cout << "\n=== HASIL PENCARIAN BERDASARKAN POSISI: " << posisi << " ===\n";
    cout << "----------------------------------------------------------------\n";
    
    for (int i = 0; i < n; i++) {
        if (arr[i].posisi == posisi) {
            found = true;
            cout << "Nama: " << arr[i].nama << "\n";
            cout << "Posisi: " << arr[i].posisi << "\n";
            cout << "Usia: " << arr[i].usia << " tahun\n";
            cout << "No Punggung: " << arr[i].no_punggung << "\n";
            cout << "Klub: " << arr[i].klub << "\n";
            cout << "Rating: " << arr[i].rating << "\n";
            cout << "----------------------------------------------------------------\n";
        }
    }
    
    if (!found) {
        cout << "Tidak ada pemain dengan posisi " << posisi << "\n";
    }
}

// Fungsi untuk menampilkan data pemain
void tampilkanData(Pemain arr[], int n) {
    cout << "\n=== DATA PEMAIN TIMNAS INDONESIA ===\n";
    cout << "====================================\n";
    
    for (int i = 0; i < n; i++) {
        cout << (i + 1) << ". " << arr[i].nama << "\n";
        cout << "   Posisi: " << arr[i].posisi << "\n";
        cout << "   Usia: " << arr[i].usia << " tahun\n";
        cout << "   No Punggung: " << arr[i].no_punggung << "\n";
        cout << "   Klub: " << arr[i].klub << "\n";
        cout << "   Rating: " << arr[i].rating << "\n";
        cout << "   --------------------------------\n";
    }
}

void hapusPemain(Pemain arr[], int& n, int index) {
    if (index < 0 || index >= n) {
        cout << "Index tidak valid!\n";
        return;
    }
    
    // Geser elemen setelah index yang dihapus
    for (int i = index; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--;
    cout << "Pemain berhasil dihapus!\n";
}

void tulisDataKeFile(Pemain arr[], int n, string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Gagal membuka file untuk ditulis!\n";
        return;
    }
    
    for (int i = 0; i < n; i++) {
        file << arr[i].posisi << "|" 
             << arr[i].nama << "|"
             << arr[i].usia << "|"
             << arr[i].no_punggung << "|"
             << arr[i].klub << "|"
             << arr[i].rating << "|"
             << (arr[i].timnas ? "1" : "0") << "\n";
    }
    
    file.close();
    cout << "Data berhasil disimpan ke file!\n";
}



void tampilkanPemainTimnas() {
    const int MAX_PemainS = 100;
    Pemain Pemains[MAX_PemainS];
    int jumlahPemain = 0;
    
    // Membaca file
    ifstream file("../data/data_pemain_timnas.txt");
    if (!file.is_open()) {
        cout << "Error: File tidak dapat dibuka!\n";
        return;
    }
    
    string line;
    while (getline(file, line) && jumlahPemain < MAX_PemainS) {
        stringstream ss(line);
        string token;
        
        // Parse data dengan delimiter |
        getline(ss, Pemains[jumlahPemain].posisi, '|');
        getline(ss, Pemains[jumlahPemain].nama, '|');
        
        getline(ss, token, '|');
        Pemains[jumlahPemain].usia = stoi(token);
        
        getline(ss, token, '|');
        Pemains[jumlahPemain].no_punggung = stoi(token);
        
        getline(ss, Pemains[jumlahPemain].klub, '|');
        
        getline(ss, token, '|');
        Pemains[jumlahPemain].rating = stod(token);
        
        getline(ss, token, '|');
        Pemains[jumlahPemain].timnas = (token == "1");
        
        jumlahPemain++;
    }
    file.close();
    
    if (jumlahPemain == 0) {
        cout << "Tidak ada data pemain yang ditemukan!\n";
        return;
    }
    
    // Setup BST dan Hash Table
    BST bst;
    HashTable hashTable;
    
    for (int i = 0; i < jumlahPemain; i++) {
        bst.insert(Pemains[i]);
        hashTable.insert(Pemains[i].no_punggung, Pemains[i]);
    }
    
    int pilihan;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tampilkan Data\n";
        cout << "2. Sorting\n";
        cout << "3. Searching\n";
        cout << "4. Hapus Pemain\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tampilkanData(Pemains, jumlahPemain);
                break;
                
            case 2: {
                int sortChoice;
                cout << "\n=== MENU SORTING ===\n";
                cout << "1. Sort berdasarkan Posisi (Bubble Sort)\n";
                cout << "2. Sort berdasarkan Nama (Merge Sort)\n";
                cout << "3. Sort berdasarkan Rating (Selection Sort)\n";
                cout << "Pilih: ";
                cin >> sortChoice;
                
                Pemain tempPemains[MAX_PemainS];
                for (int i = 0; i < jumlahPemain; i++) {
                    tempPemains[i] = Pemains[i];
                }
                
                switch (sortChoice) {
                    case 1:
                        bubbleSortPosisi(tempPemains, jumlahPemain);
                        cout << "\nData berhasil diurutkan berdasarkan posisi:\n";
                        break;
                    case 2:
                        mergeSort(tempPemains, 0, jumlahPemain - 1);
                        cout << "\nData berhasil diurutkan berdasarkan nama:\n";
                        break;
                    case 3:
                        selectionSortRating(tempPemains, jumlahPemain);
                        cout << "\nData berhasil diurutkan berdasarkan rating (tertinggi ke terendah):\n";
                        break;
                    default:
                        cout << "Pilihan tidak valid!\n";
                        continue;
                }
                tampilkanData(tempPemains, jumlahPemain);
                break;
            }
            
            case 3: {
                int searchChoice;
                cout << "\n=== MENU SEARCHING ===\n";
                cout << "1. Search berdasarkan Nama (Binary Search Tree)\n";
                cout << "2. Search berdasarkan No Punggung (Hash Table)\n";
                cout << "3. Search berdasarkan Posisi (Linear Search)\n";
                cout << "Pilih: ";
                cin >> searchChoice;
                cin.ignore();
                
                switch (searchChoice) {
                    case 1: {
                        string nama;
                        cout << "Masukkan nama pemain: ";
                        getline(cin, nama);
                        
                        Pemain* result = bst.search(nama);
                        if (result) {
                            cout << "\n=== PEMAIN DITEMUKAN ===\n";
                            cout << "Nama: " << result->nama << "\n";
                            cout << "Posisi: " << result->posisi << "\n";
                            cout << "Usia: " << result->usia << " tahun\n";
                            cout << "No Punggung: " << result->no_punggung << "\n";
                            cout << "Klub: " << result->klub << "\n";
                            cout << "Rating: " << result->rating << "\n";
                        } else {
                            cout << "Pemain dengan nama \"" << nama << "\" tidak ditemukan!\n";
                        }
                        break;
                    }
                    
                    case 2: {
                        int noPunggung;
                        cout << "Masukkan nomor punggung: ";
                        cin >> noPunggung;
                        
                        Pemain* result = hashTable.search(noPunggung);
                        if (result) {
                            cout << "\n=== PEMAIN DITEMUKAN ===\n";
                            cout << "Nama: " << result->nama << "\n";
                            cout << "Posisi: " << result->posisi << "\n";
                            cout << "Usia: " << result->usia << " tahun\n";
                            cout << "No Punggung: " << result->no_punggung << "\n";
                            cout << "Klub: " << result->klub << "\n";
                            cout << "Rating: " << result->rating << "\n";
                        } else {
                            cout << "Pemain dengan nomor punggung " << noPunggung << " tidak ditemukan!\n";
                        }
                        break;
                    }
                    
                    case 3: {
                        string posisi;
                        cout << "Masukkan posisi (GK/DF/MF/FW): ";
                        cin >> posisi;
                        linearSearchPosisi(Pemains, jumlahPemain, posisi);
                        break;
                    }
                    
                    default:
                        cout << "Pilihan tidak valid!\n";
                }
                break;
            }

            case 4: {  // Menu hapus pemain
                tampilkanData(Pemains, jumlahPemain);
                int index;
                cout << "Masukkan nomor pemain yang ingin dihapus (1-" << jumlahPemain << "): ";
                cin >> index;
                
                if (index < 1 || index > jumlahPemain) {
                    cout << "Nomor tidak valid!\n";
                } else {
                    hapusPemain(Pemains, jumlahPemain, index - 1);
                    tulisDataKeFile(Pemains, jumlahPemain, "../data/data_pemain_timnas.txt");
                }
                break;
            }

            
            case 0:
                cout << "Terima kasih!\n";
                break;
                
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);
}