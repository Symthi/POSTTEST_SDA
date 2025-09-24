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

// Struktur node untuk double linked list
struct Node {
    Penerbangan data;
    Node* next;
    Node* prev;
};

// Deklarasi head dan tail (menggantikan last)
Node* head = NULL;
Node* tail = NULL;

// Variabel global untuk counter kode penerbangan
int counterKode = 1;
int panjangList = 0;

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
    nodeBaru->prev = NULL;
    nodeBaru->next = head;

    if (head == NULL && tail == NULL) {
        head = nodeBaru;
        tail = nodeBaru;
    } else {
        head->prev = nodeBaru;
        head = nodeBaru;
    }
    
    panjangList++;
    cout << ">> Jadwal berhasil ditambahkan di awal!" << endl;
}

// Fungsi untuk menambahkan jadwal di akhir
void tambahAkhir(string tujuan, string status, string nim) {
    Node* nodeBaru = new Node;
    nodeBaru->data.kodePenerbangan = generateKodePenerbangan(nim);
    nodeBaru->data.tujuan = tujuan;
    nodeBaru->data.status = status;
    nodeBaru->prev = tail;
    nodeBaru->next = NULL;

    if (head == NULL && tail == NULL) {
        head = nodeBaru;
        tail = nodeBaru;
    } else {
        tail->next = nodeBaru;
        tail = nodeBaru;
    }
    
    panjangList++;
    cout << ">> Jadwal berhasil ditambahkan di akhir!" << endl;
}

// Fungsi untuk menambahkan jadwal di tengah (posisi tertentu)
void sisipkanJadwal(string tujuan, string status, int posisi, string nim) {
    if (posisi < 1 || posisi > panjangList + 1) {
        cout << ">> Posisi tidak valid!" << endl;
        return;
    }

    if (posisi == 1) {
        tambahAwal(tujuan, status, nim);
        return;
    } else if (posisi == panjangList + 1) {
        tambahAkhir(tujuan, status, nim); // PERBAIKAN: sebelumnya 'tambahakhir'
        return;
    }

    Node* temp = head;
    for (int i = 1; i < posisi - 1; i++) {
        temp = temp->next;
    }

    Node* nodeBaru = new Node;
    nodeBaru->data.kodePenerbangan = generateKodePenerbangan(nim);
    nodeBaru->data.tujuan = tujuan;
    nodeBaru->data.status = status;
    
    nodeBaru->next = temp->next;
    nodeBaru->prev = temp;
    temp->next->prev = nodeBaru;
    temp->next = nodeBaru;
    
    panjangList++;
    cout << ">> Jadwal berhasil disisipkan di posisi " << posisi << "!" << endl;
}

// Fungsi untuk menghapus jadwal paling awal
void hapusAwal() {
    if (head == NULL && tail == NULL) {
        cout << ">> Linked list masih kosong" << endl;
        return;
    }
    
    if (head->next == NULL) {
        cout << ">> Jadwal dengan kode " << head->data.kodePenerbangan << " berhasil dihapus!" << endl;
        delete head;
        head = NULL;
        tail = NULL;
    } else {
        Node* del = head;
        head = head->next;
        head->prev = NULL;
        cout << ">> Jadwal dengan kode " << del->data.kodePenerbangan << " berhasil dihapus!" << endl;
        delete del;
    }
    
    panjangList--;
}

// Fungsi untuk menghapus jadwal di akhir
void hapusAkhir() {
    if (head == NULL && tail == NULL) {
        cout << ">> Linked list masih kosong" << endl;
        return;
    }
    
    if (head->next == NULL) {
        cout << ">> Jadwal dengan kode " << head->data.kodePenerbangan << " berhasil dihapus!" << endl;
        delete head;
        head = NULL;
        tail = NULL;
    } else {
        Node* del = tail;
        tail = tail->prev;
        tail->next = NULL;
        cout << ">> Jadwal dengan kode " << del->data.kodePenerbangan << " berhasil dihapus!" << endl;
        delete del;
    }
    
    panjangList--;
}

// Fungsi untuk menghapus jadwal di posisi tertentu
void hapusPosisi(int posisi) {
    if (posisi < 1 || posisi > panjangList) {
        cout << ">> Posisi tidak valid!" << endl;
        return;
    }

    if (posisi == 1) {
        hapusAwal();
        return;
    } else if (posisi == panjangList) {
        hapusAkhir();
        return;
    }

    Node* temp = head;
    for (int i = 1; i < posisi; i++) {
        temp = temp->next;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    cout << ">> Jadwal dengan kode " << temp->data.kodePenerbangan << " berhasil dihapus!" << endl;
    delete temp;
    
    panjangList--;
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

// Fungsi untuk menampilkan semua jadwal dari depan (maju)
void tampilkanSemua() {
    if (head == NULL) {
        cout << ">> Linked list kosong" << endl;
        return;
    }

    cout << "================================================================" << endl;
    cout << "                   DAFTAR JADWAL PENERBANGAN                   " << endl;
    cout << "                         (DARI DEPAN)                          " << endl;
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

// Fungsi untuk menampilkan semua jadwal dari belakang (mundur)
void tampilkanDariBelakang() {
    if (tail == NULL) {
        cout << ">> Linked list kosong" << endl;
        return;
    }

    cout << "================================================================" << endl;
    cout << "                   DAFTAR JADWAL PENERBANGAN                   " << endl;
    cout << "                        (DARI BELAKANG)                        " << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "| KODE             | TUJUAN              | STATUS               |" << endl;
    cout << "----------------------------------------------------------------" << endl;
    
    Node* temp = tail;
    while (temp != NULL) {
        cout << "| " << setw(16) << left << temp->data.kodePenerbangan;
        cout << "| " << setw(19) << left << temp->data.tujuan;
        cout << "| " << setw(20) << left << temp->data.status << "|" << endl;
        
        temp = temp->prev;
    }
    cout << "================================================================" << endl;
}

// Fungsi untuk mencari dan menampilkan detail data berdasarkan kode atau nama
void cariDetailData(string keyword) {
    if (head == NULL) {
        cout << ">> Linked list kosong" << endl;
        return;
    }

    Node* temp = head;
    bool ditemukan = false;
    
    cout << "================================================================" << endl;
    cout << "                   HASIL PENCARIAN DATA                        " << endl;
    cout << "----------------------------------------------------------------" << endl;
    
    while (temp != NULL) {
        if (temp->data.kodePenerbangan == keyword || temp->data.tujuan == keyword) {
            cout << "Kode Penerbangan : " << temp->data.kodePenerbangan << endl;
            cout << "Tujuan           : " << temp->data.tujuan << endl;
            cout << "Status           : " << temp->data.status << endl;
            cout << "----------------------------------------------------------------" << endl;
            ditemukan = true;
        }
        temp = temp->next;
    }
    
    if (!ditemukan) {
        cout << ">> Data dengan kode atau tujuan '" << keyword << "' tidak ditemukan!" << endl;
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
    tail = NULL;
    panjangList = 0;
    cout << ">> Semua jadwal berhasil dihapus. Program selesai." << endl;
}

// Fungsi untuk menampilkan menu
void tampilkanMenu(string nama, string nim) {
    tampilkanHeader(nama, nim);
    cout << "======================== MENU UTAMA =========================" << endl;
    cout << "1. Tambah Jadwal Penerbangan (Awal)" << endl;
    cout << "2. Tambah Jadwal Penerbangan (Akhir)" << endl;
    cout << "3. Sisipkan Jadwal Penerbangan (Posisi Tengah)" << endl;
    cout << "4. Hapus Jadwal Paling Awal" << endl;
    cout << "5. Hapus Jadwal Paling Akhir" << endl;
    cout << "6. Hapus Jadwal di Posisi Tertentu" << endl;
    cout << "7. Update Status Penerbangan" << endl;
    cout << "8. Tampilkan Semua Jadwal (Dari Depan)" << endl;
    cout << "9. Tampilkan Semua Jadwal (Dari Belakang)" << endl;
    cout << "10. Cari Detail Data (Berdasarkan Kode/Tujuan)" << endl;
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
    
    int pilihan, posisi;
    string tujuan, status, kode, keyword;
    
    do {
        clearScreen();
        tampilkanMenu(nama, nim);
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer

        switch(pilihan) {
            case 1:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "============== TAMBAH JADWAL PENERBANGAN (AWAL) ==============" << endl;
                cout << "Masukkan Tujuan Penerbangan: ";
                getline(cin, tujuan);
                cout << "Masukkan Status Penerbangan (Tepat Waktu/Terlambat/Naik Pesawat): ";
                getline(cin, status);
                tambahAwal(tujuan, status, nim);
                break;
                
            case 2:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "============== TAMBAH JADWAL PENERBANGAN (AKHIR) ==============" << endl;
                cout << "Masukkan Tujuan Penerbangan: ";
                getline(cin, tujuan);
                cout << "Masukkan Status Penerbangan (Tepat Waktu/Terlambat/Naik Pesawat): ";
                getline(cin, status);
                tambahAkhir(tujuan, status, nim);
                break;
                
            case 3:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "============ SISIPKAN JADWAL PENERBANGAN (TENGAH) =============" << endl;
                cout << "Masukkan Tujuan Penerbangan: ";
                getline(cin, tujuan);
                cout << "Masukkan Status Penerbangan (Tepat Waktu/Terlambat/Naik Pesawat): ";
                getline(cin, status);
                cout << "Masukkan Posisi (1-" << panjangList + 1 << "): ";
                cin >> posisi;
                cin.ignore();
                sisipkanJadwal(tujuan, status, posisi, nim);
                break;
                
            case 4:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== HAPUS JADWAL AWAL ================" << endl;
                hapusAwal();
                break;
                
            case 5:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== HAPUS JADWAL AKHIR ================" << endl;
                hapusAkhir();
                break;
                
            case 6:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== HAPUS JADWAL POSISI TERTENTU ================" << endl;
                cout << "Masukkan Posisi (1-" << panjangList << "): ";
                cin >> posisi;
                cin.ignore();
                hapusPosisi(posisi);
                break;
                
            case 7:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== UPDATE STATUS PENERBANGAN ================" << endl;
                cout << "Masukkan Kode Penerbangan yang akan diupdate: ";
                getline(cin, kode);
                cout << "Masukkan Status Baru (Tepat Waktu/Terlambat/Naik Pesawat): ";
                getline(cin, status);
                updateStatus(kode, status);
                break;
                
            case 8:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== SEMUA JADWAL PENERBANGAN (DARI DEPAN) ================" << endl;
                tampilkanSemua();
                break;
                
            case 9:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== SEMUA JADWAL PENERBANGAN (DARI BELAKANG) ================" << endl;
                tampilkanDariBelakang();
                break;
                
            case 10:
                clearScreen();
                tampilkanHeader(nama, nim);
                cout << "=============== CARI DETAIL DATA ================" << endl;
                cout << "Masukkan Kode Penerbangan atau Tujuan: ";
                getline(cin, keyword);
                cariDetailData(keyword);
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