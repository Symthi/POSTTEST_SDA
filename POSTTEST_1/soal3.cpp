#include <iostream>
using namespace std;

struct Mahasiswa {
    char nama[50];
    char nim[15];
    float ipk;
};

int main() {
    Mahasiswa matriks[4];
    
    // Input
    for(int i=0; i<4; i++) {
        cout << "Data " << i+1 << endl;
        cout << "Nama: ";
        cin.ignore();
        cin.getline(matriks[i].nama, 50);
        cout << "NIM: ";
        cin.getline(matriks[i].nim, 15);
        cout << "IPK: ";
        cin >> matriks[i].ipk;
        cout << endl;
    }
    
    // Sorting
    for(int i=0; i<4; i++) {
        for(int j=i+1; j<4; j++) {
            if(matriks[i].ipk > matriks[j].ipk) {
                Mahasiswa temp = matriks[i];
                matriks[i] = matriks[j];
                matriks[j] = temp;
            }
        }
    }
    
    // Output
    cout << "Urutan IPK:\n";
    for(int i=0; i<4; i++) {
        cout << matriks[i].nama << " - " << matriks[i].ipk << endl;
    }
    
    return 0;
}