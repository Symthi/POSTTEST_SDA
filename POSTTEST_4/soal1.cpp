#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk linked list kita
struct Node {
    char data;
    Node* next;
};

// Fungsi buat nambahin elemen ke atas tumpukan (stack)
void push(Node*& top, char data) {
    // Bikin node baru, terus `next`-nya nunjuk ke `top` yang lama
    Node* newNode = new Node{data, top};
    // Update `top` biar jadi node yang baru
    top = newNode;
}

// Fungsi buat ngambil elemen paling atas dari tumpukan
char pop(Node*& top) {
    // Kalo stack-nya kosong, ya balikin karakter kosong aja
    if (top == nullptr) return '\0';

    // Simpen dulu `top` sekarang ke `temp` biar ga ilang
    Node* temp = top;
    // Ambil datanya sebelum dihapus
    char poppedValue = temp->data;
    // Pindahin `top` ke elemen di bawahnya
    top = top->next;
    // Hapus node yang udah ga kepake
    delete temp;
    // Balikin data yang tadi diambil
    return poppedValue;
}

string reverseString(string s) {
    Node* stackTop = nullptr; // Awalnya, stack kita kosong
    string reversed = "";

    // --- LENGKAPI DI SINI ---

    // 1. Masukin semua karakter dari string 's' ke dalam stack
    // Kita looping satu-satu karakternya
    for (char c : s) {
        // Setiap karakter kita 'push' atau tumpuk ke atas stack
        push(stackTop, c);
    }

    // 2. Keluarin semua karakter dari stack dan gabungin ke string `reversed`
    // Selama stack-nya belum kosong...
    while (stackTop != nullptr) {
        // Kita 'pop' atau ambil karakter paling atas,
        // terus langsung ditambahin ke belakang string `reversed`
        reversed += pop(stackTop);
    }

    // --- LENGKAPI DI SINI ---

    return reversed;
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl; // Output: ataD rukurts
    return 0;
}