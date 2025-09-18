#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// Struktur data untuk informasi penerbangan
struct Penerbangan {
    string kodePenerbangan;
    string tujuan;
    string status;
};

// Struktur node untuk linked list
struct Node {
    Penerbangan data;
    Node* next;
};

// Deklarasi head dan last
Node* head = NULL;
Node* last = NULL;

// Variabel global untuk counter kode penerbangan
int counterKode = 1;

// Fungsi untuk memeriksa apakah linked list kosong
bool isEmpty() {
    return head == NULL;
}

// Fungsi untuk menghasilkan kode penerbangan unik
string generateKodePenerbangan(string nim) {
    string tigaDigitAkhir = "024"; // Default jika NIM kosong
    if (!nim.empty() && nim.length() >= 3) {
        tigaDigitAkhir = nim.substr(nim.length() - 3);
    }
    string kode = "JT-" + tigaDigitAkhir + "-" + to_string(counterKode);
    counterKode++;
    return kode;
}

// Fungsi untuk membersihkan layar (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi untuk menampilkan header
void tampilkanHeader(string nama, string nim) {
    cout << "================================================================" << endl;
    cout << "                  FLIGHT SCHEDULE SYSTEM                       " << endl;
    cout << "                  " << nama << " - " << nim << endl;
    cout << "================================================================" << endl;
}

// Fungsi untuk menambahkan jadwal di awal
void tambahAwal(string tujuan, string status, string nim) {
    Node* nodeBaru = new Node;
    nodeBaru->data.kodePenerbangan = generateKodePenerbangan(nim);
    nodeBaru->data.tujuan = tujuan;
    nodeBaru->data.status = status;
    nodeBaru->next = head;
    head = nodeBaru;
    if (last == NULL) {
        last = head;
    }
    cout << ">> Jadwal berhasil ditambahkan di awal!" << endl;
}

// Fungsi untuk menambahkan jadwal di tengah (posisi tertentu)
void sisipkanJadwal(string tujuan, string status, int posisi, string nim) {
    if (posisi <= 1) {
        tambahAwal(tujuan, status, nim);
        return;
    }

    Node* temp = head;
    int hitung = 1;

    while (temp != NULL && hitung < posisi - 1) {
        temp = temp->next;
        hitung++;
    }

    if (temp == NULL) {
        cout << ">> Posisi tidak valid, melebihi panjang list" << endl;
        return;
    } else {
        Node* nodeBaru = new Node;
        nodeBaru->data.kodePenerbangan = generateKodePenerbangan(nim);
        nodeBaru->data.tujuan = tujuan;
        nodeBaru->data.status = status;
        nodeBaru->next = temp->next;
        temp->next = nodeBaru;
        
        if (nodeBaru->next == NULL) {
            last = nodeBaru;
        }
        
        cout << ">> Jadwal berhasil disisipkan di posisi " << posisi << "!" << endl;
    }
}

// Fungsi untuk menambahkan jadwal di akhir
void tambahAkhir(string tujuan, string status, string nim) {
    Node* nodeBaru = new Node;
    nodeBaru->data.kodePenerbangan = generateKodePenerbangan(nim);
    nodeBaru->data.tujuan = tujuan;
    nodeBaru->data.status = status;
    nodeBaru->next = NULL;

    if (head == NULL) {
        head = nodeBaru;
        last = nodeBaru;
        cout << ">> Jadwal berhasil ditambahkan di akhir!" << endl;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = nodeBaru;
    last = nodeBaru;
    cout << ">> Jadwal berhasil ditambahkan di akhir!" << endl;
}

// Fungsi untuk menghapus jadwal paling awal
void hapusAwal() {
    if (head == NULL) {
        cout << ">> Linked list masih kosong" << endl;
        return;
    }
    
    Node* temp = head;
    head = head->next;
    cout << ">> Jadwal dengan kode " << temp->data.kodePenerbangan << " berhasil dihapus!" << endl;
    delete temp;
    
    if (head == NULL) {
        last = NULL;
    }
}

// Fungsi untuk mengupdate status penerbangan
void updateStatus(string kode, string statusBaru) {
    if (head == NULL) {
        cout << ">> Linked list masih kosong" << endl;
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        if (temp->data.kodePenerbangan == kode) {
            cout << ">> Status penerbangan " << kode << " diubah dari '" 
                 << temp->data.status << "' menjadi '" << statusBaru << "'" << endl;
            temp->data.status = statusBaru;
            return;
        }
        temp = temp->next;
    }
    
    cout << ">> Kode penerbangan " << kode << " tidak ditemukan!" << endl;
}

// Fungsi untuk menampilkan semua jadwal
void tampilkanSemua() {
    if (head == NULL) {
        cout << ">> Linked list kosong" << endl;
        return;
    }

    cout << "================================================================" << endl;
    cout << "                   DAFTAR JADWAL PENERBANGAN                   " << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "| KODE             | TUJUAN              | STATUS               |" << endl;
    cout << "----------------------------------------------------------------" << endl;
    
    Node* temp = head;
    while (temp != NULL) {
        cout << "| " << setw(16) << left << temp->data.kodePenerbangan;
        cout << "| " << setw(19) << left << temp->data.tujuan;
        cout << "| " << setw(20) << left << temp->data.status << "|" << endl;
        
        temp = temp->next;
    }
    cout << "================================================================" << endl;
}

// Fungsi untuk membersihkan seluruh linked list
void clearList() {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
    last = NULL;
    cout << ">> Semua jadwal berhasil dihapus. Program selesai." << endl;
}

// Fungsi untuk menampilkan menu
void tampilkanMenu(string nama, string nim) {
    tampilkanHeader(nama, nim);
    cout << "======================== MENU UTAMA =========================" << endl;
    cout << "1. Tambah Jadwal Penerbangan (Akhir)" << endl;
    cout << "2. Sisipkan Jadwal Penerbangan (Posisi Tengah)" << endl;
    cout << "3. Hapus Jadwal Paling Awal" << endl;
    cout << "4. Update Status Penerbangan" << endl;
    cout << "5. Tampilkan Semua Jadwal" << endl;
    cout << "0. Keluar" << endl;
    cout << "================================================================" << endl;
    cout << "Pilihan Anda: ";
}

int main() {
    string nama, nim;
    int digitTerakhirNIM;
    
    clearScreen();
    // Input identitas pengguna
    cout << "================================================================" << endl;
    cout << "               SISTEM JADWAL PENERBANGAN                       " << endl;
    cout << "================================================================" << endl;
    cout << "Masukkan Nama Anda: ";
    getline(cin, nama);
    cout << "Masukkan NIM Anda: ";
    getline(cin, nim);
    
    // Hitung digit terakhir NIM untuk posisi sisip
    digitTerakhirNIM = 5; // Default value
    if (!nim.empty()) {
        char lastChar = nim[nim.length()-1];
        if (isdigit(lastChar)) {
            digitTerakhirNIM = (lastChar - '0') + 1;
        }
    }
    
    int pilihan;
    string tujuan, status, kode;
    
    do {
        clearScreen();
        tampilkanMenu(nama, nim);
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer

        switch(pilihan) {
            case 1:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "============== TAMBAH JADWAL PENERBANGAN ==============" << endl;
                cout << "Masukkan Tujuan Penerbangan: ";
                getline(cin, tujuan);
                cout << "Masukkan Status Penerbangan (Tepat Waktu/Terlambat/Naik Pesawat): ";
                getline(cin, status);
                tambahAkhir(tujuan, status, nim);
                break;
                
            case 2:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "============ SISIPKAN JADWAL PENERBANGAN =============" << endl;
                cout << "Masukkan Tujuan Penerbangan: ";
                getline(cin, tujuan);
                cout << "Masukkan Status Penerbangan (Tepat Waktu/Terlambat/Naik Pesawat): ";
                getline(cin, status);
                sisipkanJadwal(tujuan, status, digitTerakhirNIM, nim);
                break;
                
            case 3:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== HAPUS JADWAL AWAL ================" << endl;
                hapusAwal();
                break;
                
            case 4:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== UPDATE STATUS PENERBANGAN ================" << endl;
                cout << "Masukkan Kode Penerbangan yang akan diupdate: ";
                getline(cin, kode);
                cout << "Masukkan Status Baru (Tepat Waktu/Terlambat/Naik Pesawat): ";
                getline(cin, status);
                updateStatus(kode, status);
                break;
                
            case 5:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== SEMUA JADWAL PENERBANGAN ================" << endl;
                tampilkanSemua();
                break;
                
            case 0:
                clearList();
                break;
                
            default:
                cout << ">> Pilihan tidak valid!" << endl;
        }
        
        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (pilihan != 0);

    return 0;
}