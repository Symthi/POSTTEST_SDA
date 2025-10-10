#include <iostream>
using namespace std;

// Struktur Node untuk Binary Tree
struct Node {
    int data;        // Menyimpan nilai data
    Node* left;      // Pointer ke anak kiri
    Node* right;     // Pointer ke anak kanan

    // Constructor untuk inisialisasi node baru
    Node(int val) {
        data = val;          // Set nilai data
        left = nullptr;      // Set anak kiri menjadi null
        right = nullptr;     // Set anak kanan menjadi null
    }
};

// Fungsi insert untuk membangun tree
Node* insert(Node* root, int val) {
    if (root == nullptr) {           // Jika tree kosong
        return new Node(val);        // Buat node baru sebagai root
    }
    if (val < root->data) {          // Jika nilai lebih kecil dari root
        root->left = insert(root->left, val);  // Masukkan ke subtree kiri
    } else if (val > root->data) {   // Jika nilai lebih besar dari root
        root->right = insert(root->right, val); // Masukkan ke subtree kanan
    }
    return root;  // Kembalikan root yang sudah diupdate
}

int countNodes(Node* root) {
    // --- LENGKAPI KODE DI SINI ---
    if (root == nullptr) {           // Jika tree kosong atau mencapai leaf
        return 0;                   // Kembalikan 0 karena tidak ada node
    }
    // Hitung: 1 (node saat ini) + node kiri + node kanan
    return 1 + countNodes(root->left) + countNodes(root->right);
    // -----------------------------
}

int main() {
    Node* root = nullptr;            // Inisialisasi root sebagai null
    root = insert(root, 50);         // Insert nilai 50 sebagai root
    insert(root, 30);                // Insert nilai 30
    insert(root, 70);                // Insert nilai 70
    insert(root, 20);                // Insert nilai 20

    // Tampilkan jumlah total node
    cout << "Jumlah total node dalam tree adalah: " << countNodes(root) << endl;
    return 0;
}