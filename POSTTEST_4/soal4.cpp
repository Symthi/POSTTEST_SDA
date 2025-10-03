#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void sortedInsert(Node *&head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr};

    // Kasus 1: Kalo list-nya masih kosong banget
    if (head_ref == nullptr) {
        newNode->next = newNode; // nunjuk ke diri sendiri
        newNode->prev = newNode; // nunjuk ke diri sendiri juga
        head_ref = newNode;      // dia jadi kepala
        return;
    }

    // --- LENGKAPI DI SINI ---

    Node* current = head_ref;
    Node* tail = head_ref->prev; // Ekor adalah elemen sebelum head

    // Kasus 2: Data baru lebih kecil dari head, jadi dia jadi head baru
    if (data <= head_ref->data) {
        newNode->next = head_ref; // `next` dari node baru nunjuk ke head lama
        head_ref->prev = newNode; // `prev` dari head lama nunjuk ke node baru
        newNode->prev = tail;     // `prev` dari node baru nunjuk ke ekor
        tail->next = newNode;     // `next` dari ekor nunjuk ke node baru
        head_ref = newNode;       // Update head_ref jadi node baru
        return;
    }

    // Kasus 3: Cari posisi di tengah atau di akhir
    // Kita jalanin `current` sampe ketemu posisi yang pas
    // Posisinya pas kalo `data` kita lebih besar dari `current` tapi lebih kecil dari `current->next`
    while (current->next != head_ref && current->next->data < data) {
        current = current->next;
    }

    // Sekarang, `current` adalah node sebelum tempat kita nyisipin node baru
    // Kita sambungin node baru di antara `current` dan `current->next`
    newNode->next = current->next;
    current->next->prev = newNode;
    current->next = newNode;
    newNode->prev = current;
    // --- LENGKAPI DI SINI ---
}

void printList(Node *head_ref) {
    if (head_ref == nullptr) {
        cout << "List kosong" << endl;
        return;
    }
    Node *current = head_ref;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

int main() {
    Node *head = nullptr;

    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 40);
    sortedInsert(head, 20);

    cout << "Circular Doubly Linked List (sorted): ";
    printList(head); // Output: 10 20 30 40

    return 0;
}