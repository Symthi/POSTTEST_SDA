#include <iostream>
using namespace std;

int main() {
    int matriks [3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int jumlah = 0;
    
    // Cetak matriks
    cout << "Matriks 3x3:\n";
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout << matriks [i][j] << "\t";
        }
        cout << endl;
    }
    
    // Hitung jumlah baris genap (index 1 = baris ke-2)
    for(int j=0; j<3; j++) {
        jumlah += matriks [1][j];
    }
    
    // Cetak hasil perhitungan
    cout << "\nHasil perhitungan:";
    cout << "\nJumlah elemen baris genap (baris ke-2): ";
    cout << matriks [1][0] << " + " << matriks [1][1] << " + " << matriks [1][2] << " = " << jumlah;
    
    return 0;
}