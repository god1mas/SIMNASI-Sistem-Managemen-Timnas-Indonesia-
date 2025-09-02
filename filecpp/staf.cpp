#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Staf {
    int id;
    string nama;
    int umur;
    string posisi;
    string lisensi;
    int pengalaman;
    string kebangsaan;
    int status;
    
    Staf() : id(0), umur(0), pengalaman(0), status(1) {}
    
    Staf(int _id, string _nama, int _umur, string _posisi, string _lisensi, 
         int _pengalaman, string _kebangsaan, int _status) 
        : id(_id), nama(_nama), umur(_umur), posisi(_posisi), lisensi(_lisensi),
          pengalaman(_pengalaman), kebangsaan(_kebangsaan), status(_status) {}
};

class TreeNode {
public:
    string kategori;
    vector<Staf> stafList;
    vector<TreeNode*> children;
    TreeNode* parent;
    
    TreeNode(string kat) : kategori(kat), parent(nullptr) {}
    
    ~TreeNode() {
        for(TreeNode* child : children) {
            delete child;
        }
    }
    
    void addChild(TreeNode* child) {
        child->parent = this;
        children.push_back(child);
    }
    
    void addStaf(const Staf& staf) {
        stafList.push_back(staf);
    }
    
    bool removeStaf(const string& nama) {
        for(int i = 0; i < stafList.size(); i++) {
            if(stafList[i].nama == nama) {
                stafList.erase(stafList.begin() + i);
                return true;
            }
        }
        
        for(TreeNode* child : children) {
            if(child->removeStaf(nama)) {
                return true;
            }
        }
        
        return false;
    }
    
    void displayHierarchy(int level = 0) {
        // Indentasi berdasarkan level
        for(int i = 0; i < level; i++) {
            cout << "  ";
        }
        
        cout << "--> " << kategori << endl;
        
        // Tampilkan staf dalam kategori ini
        for(const Staf& staf : stafList) {
            for(int i = 0; i <= level; i++) {
                cout << "  ";
            }
            cout << "    | [" << staf.id << "]. " << staf.nama << " (" << staf.umur << " tahun, " 
                 << staf.kebangsaan << ", lisensi: " << staf.lisensi << ", pengalaman: " << staf.pengalaman << " tahun)" << endl;
        }
        
        // Tampilkan children
        for(TreeNode* child : children) {
            child->displayHierarchy(level + 1);
        }
    }
};

class StafManager {
private:
    TreeNode* root;
    int nextId;
    
    void initializeHierarchy() {
        root = new TreeNode("Struktur Organisasi Tim");
        
        // Level 1: Direktur
        TreeNode* direktur = new TreeNode("Direktur");
        root->addChild(direktur);
        
        // Level 2: Manager
        TreeNode* manager = new TreeNode("Manager");
        direktur->addChild(manager);
        
        // Level 3: Kepala Pelatih
        TreeNode* kepalaPeratih = new TreeNode("Kepala Pelatih");
        manager->addChild(kepalaPeratih);
        
        // Level 4: Asisten
        TreeNode* asisten = new TreeNode("Asisten");
        kepalaPeratih->addChild(asisten);
        
        // Level 4: Pelatih Kiper
        TreeNode* pelatihKiper = new TreeNode("Pelatih Kiper");
        kepalaPeratih->addChild(pelatihKiper);
        
        // Level 4: Pelatih Fisik
        TreeNode* pelatihFisik = new TreeNode("Pelatih Fisik");
        kepalaPeratih->addChild(pelatihFisik);
        
        // Level 4: Pelatih Teknik
        TreeNode* pelatihTeknik = new TreeNode("Pelatih Teknik");
        kepalaPeratih->addChild(pelatihTeknik);
        
        // Level 4: Tim Medis
        TreeNode* timMedis = new TreeNode("Tim Medis");
        kepalaPeratih->addChild(timMedis);
        
        // Sub Tim Medis
        TreeNode* dokterTim = new TreeNode("Dokter Tim");
        TreeNode* fisioterapis = new TreeNode("Fisioterapis");
        TreeNode* masseur = new TreeNode("Masseur");
        timMedis->addChild(dokterTim);
        timMedis->addChild(fisioterapis);
        timMedis->addChild(masseur);
        
        // Level 4: Tim Analisis & Teknologi
        TreeNode* timAnalisis = new TreeNode("Tim Analisis & Teknologi");
        kepalaPeratih->addChild(timAnalisis);
        
        // Sub Tim Analisis
        TreeNode* analisVideo = new TreeNode("Analisis Video");
        TreeNode* performanceAnalyst = new TreeNode("Performance Analyst");
        TreeNode* statistikData = new TreeNode("Statistik & Data");
        timAnalisis->addChild(analisVideo);
        timAnalisis->addChild(performanceAnalyst);
        timAnalisis->addChild(statistikData);
        
        // Level 4: Support Staff
        TreeNode* psikologTim = new TreeNode("Psikolog Tim");
        TreeNode* chefNutrisi = new TreeNode("Chef Tim & Nutrisionis");
        TreeNode* mediaOfficer = new TreeNode("Media Officer");
        TreeNode* kitmanLogistik = new TreeNode("Kitman & Logistik");
        
        kepalaPeratih->addChild(psikologTim);
        kepalaPeratih->addChild(chefNutrisi);
        kepalaPeratih->addChild(mediaOfficer);
        kepalaPeratih->addChild(kitmanLogistik);
    }
    
    TreeNode* findCategoryNode(const string& posisi) {
        return findCategoryNodeRecursive(root, posisi);
    }
    
    TreeNode* findCategoryNodeRecursive(TreeNode* node, const string& posisi) {
        if(!node) return nullptr;
        
        // Mapping posisi ke kategori
        if(posisi == "Direktur" && node->kategori == "Direktur") return node;
        if(posisi == "Manager" && node->kategori == "Manager") return node;
        if(posisi == "Kepala Pelatih" && node->kategori == "Kepala Pelatih") return node;
        if(posisi == "Asisten" && node->kategori == "Asisten") return node;
        if(posisi == "Pelatih Kiper" && node->kategori == "Pelatih Kiper") return node;
        if(posisi == "Pelatih Fisik" && node->kategori == "Pelatih Fisik") return node;
        if(posisi == "Pelatih Teknik" && node->kategori == "Pelatih Teknik") return node;
        if(posisi == "Dokter Tim" && node->kategori == "Dokter Tim") return node;
        if(posisi == "Fisioterapis" && node->kategori == "Fisioterapis") return node;
        if(posisi == "Masseur" && node->kategori == "Masseur") return node;
        if(posisi == "Analisis Video" && node->kategori == "Analisis Video") return node;
        if(posisi == "Performance Analyst" && node->kategori == "Performance Analyst") return node;
        if(posisi == "Statistik & Data" && node->kategori == "Statistik & Data") return node;
        if(posisi == "Psikolog Tim" && node->kategori == "Psikolog Tim") return node;
        if(posisi == "Chef Tim & Nutrisionis" && node->kategori == "Chef Tim & Nutrisionis") return node;
        if(posisi == "Media Officer" && node->kategori == "Media Officer") return node;
        if(posisi == "Kitman & Logistik" && node->kategori == "Kitman & Logistik") return node;
        
        // Cari di children
        for(TreeNode* child : node->children) {
            TreeNode* result = findCategoryNodeRecursive(child, posisi);
            if(result) return result;
        }
        
        return nullptr;
    }
    
public:
    StafManager() : nextId(1) {
        initializeHierarchy();
        loadDataFromFile();
    }
    
    ~StafManager() {
        delete root;
    }
    
    void loadDataFromFile() {
        ifstream file("../data/../data/data_staf.txt");
        if(!file.is_open()) {
            cout << "File ../data/data_staf.txt tidak ditemukan!" << endl;
            return;
        }
        
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string item;
            vector<string> tokens;
            
            while(getline(ss, item, '|')) {
                tokens.push_back(item);
            }
            
            if(tokens.size() >= 7) {
                Staf staf(
                    stoi(tokens[0]),     // id
                    tokens[1],           // nama
                    stoi(tokens[2]),     // umur
                    tokens[3],           // posisi
                    tokens[4],           // lisensi
                    stoi(tokens[5]),     // pengalaman
                    tokens[6],           // kebangsaan
                    tokens.size() > 7 ? stoi(tokens[7]) : 1  // status
                );
                
                TreeNode* categoryNode = findCategoryNode(staf.posisi);
                if(categoryNode) {
                    categoryNode->addStaf(staf);
                }
                
                if(staf.id >= nextId) {
                    nextId = staf.id + 1;
                }
            }
        }
        file.close();
        cout << "Data berhasil dimuat dari file!" << endl;
    }
    
    void tampilkanHirarki() {
        cout << "\n=== HIRARKI STAF TIM ===" << endl;
        root->displayHierarchy();
        cout << endl;
    }
    
    void tambahStaf() {
        cout << "\n=== TAMBAH STAF BARU ===" << endl;
        
        Staf stafBaru;
        stafBaru.id = nextId++;
        
        cout << "Nama: ";
        cin.ignore();
        getline(cin, stafBaru.nama);
        
        cout << "Umur: ";
        cin >> stafBaru.umur;
        
        cout << "\nPilih Posisi:" << endl;
        cout << "1. Direktur" << endl;
        cout << "2. Manager" << endl;
        cout << "3. Kepala Pelatih" << endl;
        cout << "4. Asisten" << endl;
        cout << "5. Pelatih Kiper" << endl;
        cout << "6. Pelatih Fisik" << endl;
        cout << "7. Pelatih Teknik" << endl;
        cout << "8. Dokter Tim" << endl;
        cout << "9. Fisioterapis" << endl;
        cout << "10. Masseur" << endl;
        cout << "11. Analisis Video" << endl;
        cout << "12. Performance Analyst" << endl;
        cout << "13. Statistik & Data" << endl;
        cout << "14. Psikolog Tim" << endl;
        cout << "15. Chef Tim & Nutrisionis" << endl;
        cout << "16. Media Officer" << endl;
        cout << "17. Kitman & Logistik" << endl;
        
        int pilihan;
        cout << "Pilihan (1-17): ";
        cin >> pilihan;
        
        string posisiArray[] = {
            "Direktur", "Manager", "Kepala Pelatih", "Asisten", "Pelatih Kiper",
            "Pelatih Fisik", "Pelatih Teknik", "Dokter Tim", "Fisioterapis", "Masseur",
            "Analisis Video", "Performance Analyst", "Statistik & Data", "Psikolog Tim",
            "Chef Tim & Nutrisionis", "Media Officer", "Kitman & Logistik"
        };
        
        if(pilihan >= 1 && pilihan <= 17) {
            stafBaru.posisi = posisiArray[pilihan - 1];
        } else {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }
        
        cout << "Lisensi: ";
        cin.ignore();
        getline(cin, stafBaru.lisensi);
        
        cout << "Pengalaman (tahun): ";
        cin >> stafBaru.pengalaman;
        
        cout << "Kebangsaan: ";
        cin.ignore();
        getline(cin, stafBaru.kebangsaan);
        
        stafBaru.status = 1;
        
        TreeNode* categoryNode = findCategoryNode(stafBaru.posisi);
        if(categoryNode) {
            categoryNode->addStaf(stafBaru);
            cout << "Staf berhasil ditambahkan!" << endl;
            
            // Simpan ke file
            saveToFile();
        } else {
            cout << "Kategori tidak ditemukan!" << endl;
        }
    }
    
    void hapusStaf() {
        cout << "\n=== HAPUS STAF ===" << endl;
        cout << "Masukkan nama staf yang akan dihapus: ";
        
        string nama;
        cin.ignore();
        getline(cin, nama);
        
        if(root->removeStaf(nama)) {
            cout << "Staf '" << nama << "' berhasil dihapus!" << endl;
            saveToFile();
        } else {
            cout << "Staf dengan nama '" << nama << "' tidak ditemukan!" << endl;
        }
    }
    
    void saveToFile() {
        ofstream file("../data/data_staf.txt");
        if(!file.is_open()) {
            cout << "Error: Tidak dapat menyimpan ke file!" << endl;
            return;
        }
        
        saveNodeToFile(file, root);
        file.close();
        cout << "Data berhasil disimpan ke file!" << endl;
    }
    
    void saveNodeToFile(ofstream& file, TreeNode* node) {
        if(!node) return;
        
        for(const Staf& staf : node->stafList) {
            file << staf.id << "|" << staf.nama << "|" << staf.umur << "|"
                 << staf.posisi << "|" << staf.lisensi << "|" << staf.pengalaman << "|"
                 << staf.kebangsaan << "|" << staf.status << endl;
        }
        
        for(TreeNode* child : node->children) {
            saveNodeToFile(file, child);
        }
    }
    
    void menu() {
        int pilihan;
        
        do {
            cout << "\n=== SISTEM MANAJEMEN STAF TIM ===" << endl;
            cout << "1. Tampilkan Hirarki Staf" << endl;
            cout << "2. Tambah Staf Baru" << endl;
            cout << "3. Hapus Staf" << endl;
            cout << "4. Keluar" << endl;
            cout << "Pilihan Anda: ";
            cin >> pilihan;
            
            switch(pilihan) {
                case 1:
                    tampilkanHirarki();
                    break;
                case 2:
                    tambahStaf();
                    break;
                case 3:
                    hapusStaf();
                    break;
                case 4:
                    cout << "Terima kasih!" << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid!" << endl;
            }
        } while(pilihan != 4);
    }
};

void staf() {
    StafManager manager;
    manager.menu();
}