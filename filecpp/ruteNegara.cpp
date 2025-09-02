//Implementasi Graph pada rute perjalanan timnas Asia
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Negara {
    string nama_negara;
    string bandara;
    string kota_bandara;
};

const int MAX_NEGARA = 20;
const int INF = 999999;

// Inisialisasi data negara Asia
void inisialisasiNegara(Negara negara[], int &jumlahNegara) {
    jumlahNegara = 15;
    
    negara[0] = {"Indonesia", "Soekarno-Hatta International Airport", "Jakarta"};
    negara[1] = {"Thailand", "Suvarnabhumi Airport", "Bangkok"};
    negara[2] = {"Malaysia", "Kuala Lumpur International Airport", "Kuala Lumpur"};
    negara[3] = {"Singapore", "Changi Airport", "Singapore"};
    negara[4] = {"Vietnam", "Tan Son Nhat International Airport", "Ho Chi Minh City"};
    negara[5] = {"Philippines", "Ninoy Aquino International Airport", "Manila"};
    negara[6] = {"Japan", "Narita International Airport", "Tokyo"};
    negara[7] = {"South Korea", "Incheon International Airport", "Seoul"};
    negara[8] = {"China", "Beijing Capital International Airport", "Beijing"};
    negara[9] = {"India", "Indira Gandhi International Airport", "New Delhi"};
    negara[10] = {"Saudi Arabia", "King Khalid International Airport", "Riyadh"};
    negara[11] = {"UAE", "Dubai International Airport", "Dubai"};
    negara[12] = {"Qatar", "Hamad International Airport", "Doha"};
    negara[13] = {"Australia", "Sydney Kingsford Smith Airport", "Sydney"};
    negara[14] = {"Iran", "Imam Khomeini International Airport", "Tehran"};
}

// Inisialisasi adjacency matrix dengan jarak (dalam km)
void inisialisasiGraph(int graph[][MAX_NEGARA], int jumlahNegara) {
    // Inisialisasi semua jarak dengan INF
    for (int i = 0; i < jumlahNegara; i++) {
        for (int j = 0; j < jumlahNegara; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }
    
    // Menambahkan edge dengan jarak (dalam ratusan km untuk simplifikasi)
    // Indonesia ke negara lain
    graph[0][1] = 15; graph[1][0] = 15; // Indonesia - Thailand
    graph[0][2] = 12; graph[2][0] = 12; // Indonesia - Malaysia
    graph[0][3] = 9;  graph[3][0] = 9;  // Indonesia - Singapore
    graph[0][4] = 13; graph[4][0] = 13; // Indonesia - Vietnam
    graph[0][5] = 17; graph[5][0] = 17; // Indonesia - Philippines
    
    // Thailand ke negara lain
    graph[1][2] = 8;  graph[2][1] = 8;  // Thailand - Malaysia
    graph[1][3] = 11; graph[3][1] = 11; // Thailand - Singapore
    graph[1][4] = 6;  graph[4][1] = 6;  // Thailand - Vietnam
    graph[1][9] = 25; graph[9][1] = 25; // Thailand - India
    
    // Malaysia ke negara lain
    graph[2][3] = 3;  graph[3][2] = 3;  // Malaysia - Singapore
    graph[2][4] = 12; graph[4][2] = 12; // Malaysia - Vietnam
    graph[2][5] = 18; graph[5][2] = 18; // Malaysia - Philippines
    
    // Singapore ke negara lain
    graph[3][4] = 14; graph[4][3] = 14; // Singapore - Vietnam
    graph[3][5] = 20; graph[5][3] = 20; // Singapore - Philippines
    graph[3][13] = 62; graph[13][3] = 62; // Singapore - Australia
    
    // Vietnam ke negara lain
    graph[4][5] = 11; graph[5][4] = 11; // Vietnam - Philippines
    graph[4][8] = 18; graph[8][4] = 18; // Vietnam - China
    
    // Philippines ke negara lain
    graph[5][6] = 30; graph[6][5] = 30; // Philippines - Japan
    graph[5][8] = 28; graph[8][5] = 28; // Philippines - China
    
    // Japan ke negara lain
    graph[6][7] = 12; graph[7][6] = 12; // Japan - South Korea
    graph[6][8] = 21; graph[8][6] = 21; // Japan - China
    
    // South Korea ke negara lain
    graph[7][8] = 9;  graph[8][7] = 9;  // South Korea - China
    
    // China ke negara lain
    graph[8][9] = 36; graph[9][8] = 36; // China - India
    graph[8][14] = 58; graph[14][8] = 58; // China - Iran
    
    // India ke negara lain
    graph[9][10] = 35; graph[10][9] = 35; // India - Saudi Arabia
    graph[9][11] = 32; graph[11][9] = 32; // India - UAE
    graph[9][14] = 42; graph[14][9] = 42; // India - Iran
    
    // Saudi Arabia ke negara lain
    graph[10][11] = 8; graph[11][10] = 8; // Saudi Arabia - UAE
    graph[10][12] = 12; graph[12][10] = 12; // Saudi Arabia - Qatar
    graph[10][14] = 16; graph[14][10] = 16; // Saudi Arabia - Iran
    
    // UAE ke negara lain
    graph[11][12] = 4; graph[12][11] = 4; // UAE - Qatar
    graph[11][14] = 12; graph[14][11] = 12; // UAE - Iran
    
    // Qatar ke negara lain
    graph[12][14] = 15; graph[14][12] = 15; // Qatar - Iran
    
    // Australia (isolated for this example - connected via Singapore)
}

// Fungsi untuk menampilkan semua negara
void tampilkanSemuaNegara(Negara negara[], int jumlahNegara) {
    cout << "\n========== DAFTAR NEGARA ASIA ==========\n";
    cout << "No.\tNegara\t\t\tBandara\t\t\t\t\tKota\n";
    cout << "===================================================================================\n";
    
    for (int i = 0; i < jumlahNegara; i++) {
        cout << (i + 1) << ".\t";
        cout << negara[i].nama_negara;
        
        // Padding untuk alignment
        int padding = 20 - negara[i].nama_negara.length();
        for (int j = 0; j < padding; j++) cout << " ";
        
        cout << negara[i].bandara.substr(0, 35);
        
        padding = 40 - negara[i].bandara.length();
        if (padding < 0) padding = 5;
        for (int j = 0; j < padding; j++) cout << " ";
        
        cout << negara[i].kota_bandara << "\n";
    }
    cout << "===================================================================================\n";
}

// Fungsi untuk menampilkan adjacency matrix
void tampilkanRuteGraph(Negara negara[], int graph[][MAX_NEGARA], int jumlahNegara) {
    cout << "\n========== GRAPH RUTE PERJALANAN TIMNAS ASIA ==========\n";
    cout << "Jarak antar negara (dalam ratusan km):\n\n";

    const int kolom_lebar = 8;

    // Header
    cout << setw(kolom_lebar) << left << "";
    for (int i = 0; i < jumlahNegara; i++) {
        cout << setw(kolom_lebar) << left << negara[i].nama_negara.substr(0, 6);
    }
    cout << "\n";

    // Baris data
    for (int i = 0; i < jumlahNegara; i++) {
        cout << setw(kolom_lebar) << left << negara[i].nama_negara.substr(0, 6);
        for (int j = 0; j < jumlahNegara; j++) {
            if (graph[i][j] == INF) {
                cout << setw(kolom_lebar) << left << "-";
            } else {
                cout << setw(kolom_lebar) << left << graph[i][j];
            }
        }
        cout << "\n";
    }

    cout << "\nKeterangan:\n";
    cout << "- Angka menunjukkan jarak dalam ratusan kilometer\n";
    cout << "- Tanda '-' menunjukkan tidak ada rute langsung\n";
    cout << "========================================================\n";
}

// Algoritma Dijkstra untuk mencari rute terpendek
void dijkstra(int graph[][MAX_NEGARA], int src, int dest, int jumlahNegara, Negara negara[]) {
    int dist[MAX_NEGARA];
    bool visited[MAX_NEGARA];
    int parent[MAX_NEGARA];
    
    // Inisialisasi
    for (int i = 0; i < jumlahNegara; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }
    
    dist[src] = 0;
    
    // Algoritma Dijkstra
    for (int count = 0; count < jumlahNegara - 1; count++) {
        int u = -1;
        
        // Cari vertex dengan jarak minimum yang belum dikunjungi
        for (int v = 0; v < jumlahNegara; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        
        visited[u] = true;
        
        // Update jarak ke tetangga
        for (int v = 0; v < jumlahNegara; v++) {
            if (!visited[v] && graph[u][v] != INF && 
                dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
    
    // Output hasil
    cout << "\n========== RUTE TERPENDEK ==========\n";
    cout << "Dari: " << negara[src].nama_negara << " (" << negara[src].kota_bandara << ")\n";
    cout << "Ke: " << negara[dest].nama_negara << " (" << negara[dest].kota_bandara << ")\n";
    
    if (dist[dest] == INF) {
        cout << "Tidak ada rute yang tersedia!\n";
        return;
    }
    
    cout << "Jarak Total: " << dist[dest] << " x 100 km = " << (dist[dest] * 100) << " km\n";
    
    // Rekonstruksi path
    int path[MAX_NEGARA];
    int pathLength = 0;
    int current = dest;
    
    while (current != -1) {
        path[pathLength++] = current;
        current = parent[current];
    }
    
    cout << "\nRute Perjalanan:\n";
    for (int i = pathLength - 1; i >= 0; i--) {
        cout << (pathLength - i) << ". " << negara[path[i]].nama_negara 
             << " - " << negara[path[i]].bandara 
             << " (" << negara[path[i]].kota_bandara << ")";
        
        if (i > 0) {
            int currentNode = path[i];
            int nextNode = path[i-1];
            cout << "\n   -> Jarak ke " << negara[nextNode].nama_negara 
                 << ": " << graph[currentNode][nextNode] << " x 100 km\n";
        }
    }
    cout << "\n=====================================\n";
}

// Menu rute perjalanan
void menuRutePerjalanan() {
    Negara negara[MAX_NEGARA];
    int graph[MAX_NEGARA][MAX_NEGARA];
    int jumlahNegara;
    
    inisialisasiNegara(negara, jumlahNegara);
    inisialisasiGraph(graph, jumlahNegara);
    
    int pilihan;
    do {
        cout << "\n========== MENU RUTE PERJALANAN TIMNAS ==========\n";
        cout << "1. Tampilkan Graph Rute Keseluruhan\n";
        cout << "2. Cari Rute Terpendek ke Negara Tujuan\n";
        cout << "3. Tampilkan Daftar Negara\n";
        cout << "4. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tampilkanRuteGraph(negara, graph, jumlahNegara);
                break;
            case 2: {
                tampilkanSemuaNegara(negara, jumlahNegara);
                
                int asal, tujuan;
                cout << "\nMasukkan nomor negara asal (Indonesia = 1): ";
                cin >> asal;
                cout << "Masukkan nomor negara tujuan: ";
                cin >> tujuan;
                
                if (asal < 1 || asal > jumlahNegara || tujuan < 1 || tujuan > jumlahNegara) {
                    cout << "Nomor negara tidak valid!\n";
                    break;
                }
                
                asal--; // Convert ke index array (0-based)
                tujuan--;
                
                dijkstra(graph, asal, tujuan, jumlahNegara, negara);
                break;
            }
            case 3:
                tampilkanSemuaNegara(negara, jumlahNegara);
                break;
            case 4:
                cout << "\nTerima kasih telah menggunakan sistem rute perjalanan!\n";
                cout << "Program berakhir.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 4);
}

// Fungsi utama
void ruteNegara() {
    cout << "========================================\n";
    cout << "  SISTEM RUTE PERJALANAN TIMNAS\n";
    cout << "========================================\n";
    
    menuRutePerjalanan();
}