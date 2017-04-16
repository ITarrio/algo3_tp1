#include <iostream>
#include <fstream>
#include <random>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
#include "ej1.cpp"
#include "ej2.cpp"
#include "ej3.cpp"

#define ya chrono::high_resolution_clock::now

void generarArregloAleatorio(int arreglo[], int largo, int min, int max) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
    for (int i = 0; i < largo; i ++) {
        arreglo[i] = uni(rng);
    }
}

void generarArchivos() {
    int *arreglo;
    int largo;
    std::ofstream myfile;
    int largos[] = {1, 2, 5, 10, 15, 20, 25, 30, 35, 40};
    for (int l = 0; l < 9; l++) {
        largo = largos[l];
        myfile.open ("arreglos largo "+ std::to_string(largo));
        arreglo = new int [largo];
        for ( int i = 0; i < 30; i++){
            generarArregloAleatorio(arreglo, largo, 0, 2*largo);
            for(int j = 0; j < largo; j++) {
                myfile << arreglo[j] << " ";
            }
            myfile << std::endl;
        }
        delete(arreglo);
        myfile.close();
    }
}

void probar(){
    int u, d, t;
    int largos[] = {1, 2, 5, 10, 15, 20, 25, 30, 35};
    for (int l = 0; l < 9; l++) {
        ifstream file;
        int largo = largos[l];
        int arreglo[largo];
        cout << "largo "<< largo << endl;
        file.open("arreglos largo " + std::to_string(largo));

        for (int a = 0; a < 30; a++) {
            for (int i = 0; i < largo; i++) {
                file >> arreglo[i];
            }
            auto start = ya();
            ej1(arreglo, largo);
            auto end = ya();
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "|";
            start = ya();
            ej2(arreglo, largo);
            end = ya();
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << ",";
            start = ya();
            ej3(arreglo, largo);
            end = ya();
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << ";";
        }
        cout << endl;
        file.close();
    }
}

int main() {
    probar();
    return 0;
}
