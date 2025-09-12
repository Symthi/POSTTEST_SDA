#include <iostream>
using namespace std;

void balik(int *a) {
    for(int i=0; i<3; i++) {
        int temp = a[i];
        a[i] = a[6-i];
        a[6-i] = temp;
    }
}

int main() {
    int data[7] = {2,3,5,7,11,13,17};
    
    cout << "Awal: ";
    for(int i=0; i<7; i++) cout << data[i] << " ";
    
    balik(data);
    
    cout << "\nAkhir: ";
    for(int i=0; i<7; i++) cout << data[i] << " ";
    
    return 0;
}