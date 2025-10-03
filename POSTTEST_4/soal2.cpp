#include <iostream>
#include <string>
using namespace std;

// Struktur Node, sama seperti soal 1
struct Node {
    char data;
    Node* next;
};

// Fungsi push dan pop dari soal sebelumnya kita pakai lagi
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}


bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr;

    // --- LENGKAPI DI SINI ---

    // 1. Kita cek setiap karakter di dalam string
    for (char c : expr) {
        // 2. Kalo nemu kurung buka, langsung masukin ke stack
        if (c == '(' || c == '{' || c == '[') {
            push(stackTop, c);
        }
        // 3. Kalo nemu kurung tutup, kita proses
        else if (c == ')' || c == '}' || c == ']') {
            // Cek dulu, jangan-jangan stack udah kosong, padahal ada kurung tutup.
            // Kalo iya, udah pasti ga seimbang.
            if (stackTop == nullptr) {
                return false;
            }

            // Ambil kurung buka terakhir dari stack
            char topChar = pop(stackTop);

            // Cocokin pasangannya. Kalo ga cocok, berarti ga seimbang.
            // Contoh: kurung tutupnya ')' tapi di stack paling atas malah '{', kan ga nyambung.
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '[')) {
                return false;
            }
        }
    }

    // 4. Setelah semua karakter dicek, stack harusnya kosong.
    // Kalo masih ada sisa, berarti ada kurung buka yang ga punya pasangan.
    return stackTop == nullptr;

    // --- LENGKAPI DI SINI ---
}

int main() {
    string expr1 = "{[()]}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;

    string expr2 = "{[(])}";
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;

    return 0;
}