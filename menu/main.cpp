#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include "../filecpp/pemain.cpp"
#include "../filecpp/klub.cpp"
#include "../filecpp/pertandinganDanStrategi.cpp"
#include "../filecpp/seleksiTimnas.cpp"
#include "../filecpp/staf.cpp"
#include "../filecpp/keuangan_logistic.cpp"
#include "../filecpp/ruteNegara.cpp"
#include "../filecpp/latihan.cpp"

using namespace std;

void tampilkanMenuUtama() {
    cout << "=====================================" << endl;
    cout << "  SISTEM INFORMASI TIMNAS INDONESIA  " <<endl;
    cout << "=====================================" << endl;
    cout << "1. Pemain Timnas Indonesia" << endl;
    cout << "2. Seleksi Timnas" << endl;
    cout << "3. Klub" << endl;
    cout << "4. Pertandingan" << endl;
    cout << "5. Staf" << endl;
    cout << "6. Latihan" << endl;
    cout << "7. Perjalanan" << endl;
    cout << "8. Keuangan dan Logistik" << endl;
    cout << "9. Keluar" << endl; 
}

int main() {
    int pilihan;

    while (true) {
        tampilkanMenuUtama();
        cout << "Masukkan pilihan Anda (1-9): ";
        cin >> pilihan;

        // Validasi input
        if (cin.fail()) {
            cin.clear(); // Reset flag kesalahan input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Buang input yang salah
            cout << "Input tidak valid. Harap masukkan angka antara 1 sampai 9.\n\n";
            continue;
        }

        switch (pilihan) {
            case 1:
            system("cls");
                tampilkanPemainTimnas();
                break;
            case 2:
            system("cls");
                seleksiTimnas();
                break;
            case 3:
            system("cls");
                menuKlub();
                break;
            case 4:
            system("cls");
                jadwalPertandingan();
                break;
            case 5:
            system("cls");
                staf();
                break;
            case 6:
            system("cls");
                latihan();
                break;
            case 7:
            system("cls");
                ruteNegara();
                break;
            case 8:
            system("cls");
                KeuanganDanLogistic();
                break;
            case 9:
                return 0; // Mengakhiri program
            default:
                cout << "Pilihan tidak tersedia. Silakan pilih antara 1 sampai 9.\n\n";
        }
    }
    return 0;
}