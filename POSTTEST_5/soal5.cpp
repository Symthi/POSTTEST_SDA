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

void preOrderTraversal(Node* root) {
    // --- LENGKAPI KODE DI SINI ---
    if (root == nullptr) {           // Jika tree kosong atau mencapai leaf
        return;                     // Keluar dari fungsi
    }
    
    cout << root->data << " ";       // Cetak node saat ini (root) terlebih dahulu
    preOrderTraversal(root->left);   // Kemudian kunjungi subtree kiri
    preOrderTraversal(root->right);  // Terakhir kunjungi subtree kanan
    // -----------------------------
}

int main() {
    Node* root = nullptr;            // Inisialisasi root sebagai null
    root = insert(root, 50);         // Insert nilai 50 sebagai root
    insert(root, 30);                // Insert nilai 30
    insert(root, 70);                // Insert nilai 70
    insert(root, 20);                // Insert nilai 20
    insert(root, 40);                // Insert nilai 40
    insert(root, 60);                // Insert nilai 60
    insert(root, 80);                // Insert nilai 80

    // Lakukan pre-order traversal
    cout << "Pre-order traversal dari tree adalah: ";
    preOrderTraversal(root);
    cout << endl;
    return 0;
}