#include <iostream>
#include <string>
using namespace std;

// Node untuk menyimpan nama dokumen
struct Node {
    string document;
    Node* next;
};

// Fungsi untuk menambahkan dokumen ke antrian (belakang)
void enqueue(Node*& front, Node*& rear, string document) {
    Node* newNode = new Node{document, nullptr};

    // --- LENGKAPI DI SINI ---

    // 1. Kalo antrian masih kosong
    if (front == nullptr) {
        // Maka elemen baru ini jadi yang paling depan (front) sekaligus paling belakang (rear)
        front = newNode;
        rear = newNode;
    } else {
    // 2. Kalo antrian udah ada isinya
        // Sambungin elemen paling belakang yang lama ke elemen baru
        rear->next = newNode;
        // Terus update, biar elemen baru ini jadi yang paling belakang
        rear = newNode;
    }
    // --- LENGKAPI DI SINI ---
}

// Fungsi untuk mengambil dokumen dari antrian (depan)
string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return "Antrian kosong!"; // Kalo ga ada apa-apa di antrian

    // --- LENGKAPI DI SINI ---

    // 1. Simpen dulu node paling depan ke variabel sementara
    Node* temp = front;
    string documentData = temp->document;

    // 2. Geser 'front' ke elemen berikutnya di antrian
    front = front->next;

    // 3. Kalo setelah digeser ternyata 'front' jadi kosong,
    // artinya antriannya abis. 'rear' juga harus dikosongin.
    if (front == nullptr) {
        rear = nullptr;
    }

    // 4. Hapus node paling depan yang lama dan balikin datanya
    delete temp;
    return documentData;
    // --- LENGKAPI DI SINI ---
}

// Fungsi buat proses semua dokumen di antrian
void processAllDocuments(Node*& front, Node*& rear) {
    // --- LENGKAPI DI SINI ---

    // Selama antrian masih ada isinya (front belum kosong)
    while (front != nullptr) {
        // Ambil satu dokumen dari depan, terus cetak namanya
        cout << "Memproses: " << dequeue(front, rear) << endl;
    }
    // --- LENGKAPI DI SINI ---
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;

    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");

    cout << "Memulai pemrosesan antrian printer:" << endl;
    processAllDocuments(front, rear);

    return 0;
}