#include <iostream>
using namespace std;

struct Vector {
    int vect[5];
    int len;
};

void mostrar(int vec[], int len) {
    for (int i = 0; i < len; i++) {
        cout << vec[i] << endl;
    }
}
void ordenamientoBurbuja(Vector& vec, int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (vec.vect[j] > vec.vect[j + 1]){
                int temp = vec.vect[j];
                vec.vect[j] = vec.vect[j + 1];    
                vec.vect[j + 1] = temp;
            }
        }
    }
}

int main()
{
    Vector vec;
    vec.vect[0] = 22;
    vec.vect[1] = 12;
    vec.vect[2] = 33;
    vec.vect[3] = 120;
    vec.vect[4] = 2;
    ordenamientoBurbuja(vec, 5);
    for (int i = 0; i < 5; i++) {
        cout << vec.vect[i]<< endl;
    }
}

