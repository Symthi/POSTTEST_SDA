#include <iostream>
using namespace std;

void tukar(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x, y;
    cout << "Input 2 angka: ";
    cin >> x >> y;
    
    cout << "Sebelum: " << x << " " << y;
    tukar(x, y);
    cout << "\nSesudah: " << x << " " << y;
    
    return 0;
}