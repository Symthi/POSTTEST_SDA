#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void exchangeHeadAndTail(Node *&head_ref) {
    // Kalo listnya kosong, cuma 1, atau cuma 2 node, ga perlu ribet-ribet
    if (head_ref == nullptr || head_ref->next == head_ref) {
        return;
    }

    // Kalo cuma 2 node, tinggal tuker head_ref aja
    if (head_ref->next->next == head_ref) {
        head_ref = head_ref->next;
        return;
    }

    // Ambil referensi ke node-node penting
    Node* old_head = head_ref;
    Node* old_tail = head_ref->prev;
    Node* head_next = head_ref->next; // Tetangga head
    Node* tail_prev = old_tail->prev; // Tetangga tail

    // --- Proses penukaran pointer ---

    // 1. Sambungkan tetangga lama ke node yang ditukar
    // Tetangga head (head_next) sekarang nyambung ke tail
    head_next->prev = old_tail;
    // Tetangga tail (tail_prev) sekarang nyambung ke head
    tail_prev->next = old_head;

    // 2. Atur pointer untuk head dan tail yang posisinya baru
    // `next` dari tail baru (yang tadinya head) adalah head_next
    old_head->next = old_tail;
    // `prev` dari tail baru (yang tadinya head) adalah tail_prev
    old_head->prev = tail_prev;

    // `next` dari head baru (yang tadinya tail) adalah head_next
    old_tail->next = head_next;
    // `prev` dari head baru (yang tadinya tail) adalah old_head
    old_tail->prev = old_head;

    // 3. Terakhir, update head_ref biar nunjuk ke kepala yang bener
    head_ref = old_tail;
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

void insertEnd(Node *&head_ref, int data) {
    Node *newNode = new Node{data, nullptr, nullptr};
    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }
    Node *tail = head_ref->prev;
    newNode->next = head_ref;
    head_ref->prev = newNode;
    tail->next = newNode;
    newNode->prev = tail;
}

int main() {
    Node *head = nullptr;

    // Buat list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head); // Output: 1 2 3 4 5

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    printList(head); // Output: 5 2 3 4 1

    return 0;
}