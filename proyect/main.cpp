#include <iostream>
#include <array>
#include <vector>
#include <chrono>
#include <random>

#define ya chrono::high_resolution_clock::now

using namespace std;

//Retorna la cantidad de numeros sin pintar
int backtrack(int i, int arreglo[], int n, int ultimoAzulPintado, int ultimoRojoPintado, bool hayAzulPintado, bool hayRojoPintado) {
    if (i == n - 1) {
        //Aqui llegamos al fin de la recursion, devolvemos 0 si pintamos este numero y uno si lo dejamos sin pintar
        if (!hayRojoPintado || arreglo[i] > ultimoRojoPintado || !hayAzulPintado || arreglo[i] < ultimoAzulPintado){
            return 0;
        } else {;
            return 1;
        }
    }else{
        int minSiRojo = n, minSiAzul = n, minSinPintar;
        if (!hayRojoPintado || arreglo[i] > ultimoRojoPintado) { // Pintamos de rojo solo si el numero es mas grande que el ultimo rojo pintado
            minSiRojo = backtrack(i + 1, arreglo, n, ultimoAzulPintado, arreglo[i], hayAzulPintado, true); // Aca obtenemos la cantidad minima de numero sin pintar si pintamos este num de rojo
        }

        if (!hayAzulPintado || arreglo[i] < ultimoAzulPintado) { // Igual que para el rojo ahora lo hacemos para el azul
            minSiAzul = backtrack(i + 1, arreglo, n, arreglo[i], ultimoRojoPintado, true, hayRojoPintado);
        }

        minSinPintar = backtrack(i + 1, arreglo, n, ultimoAzulPintado, ultimoRojoPintado, hayAzulPintado, hayRojoPintado) + 1;// Ahora probamos sin pintarlo, le sumamos uno porque este numero no lo pintamos

        //Seleccionamos el menor(ya que estamos buscando el optimo) y retornamos ese
        if (minSiRojo <= minSiAzul && minSiRojo <= minSinPintar) {
            return minSiRojo;
        } else {
            if (minSiAzul <= minSinPintar) {
                return minSiAzul;
            } else {
                return minSinPintar;
            }
        }
    }
}

int backtrackImproved(int i, int arreglo[], int n, int ultimoAzul, int ultimoRojo, bool hayAzul, bool hayRojo )
{
    if (i == n - 1) {
        if (!hayRojo || arreglo[i] > ultimoRojo || !hayAzul || arreglo[i] < ultimoAzul){
            return 0;
        } else {;
            return 1;
        }
    }else{
        int minSiRojo = n, minSiAzul = n, minSinPintar;
        if (!hayRojo || arreglo[i] > ultimoRojo){ // Pintamos de rojo solo si el numero es mas grande que el ultimo rojo pintado
            minSiRojo = backtrackImproved(i + 1, arreglo, n, ultimoAzul, arreglo[i], hayAzul, true); // Aca obtenemos la cantidad minima de numero sin pintar si pintamos este num de rojo
            if (minSiRojo == 0) {
                return minSiRojo;
            }
        }


        if (!hayAzul || arreglo[i] < ultimoAzul){ // Igual que para el rojo ahora lo hacemos para el azul
            minSiAzul = backtrackImproved(i + 1, arreglo, n, arreglo[i], ultimoRojo, true, hayRojo);
            if (minSiAzul == 0) {
                return minSiAzul;
            }
        }

        minSinPintar = backtrackImproved(i + 1, arreglo, n, ultimoAzul, ultimoRojo, hayAzul, hayRojo) + 1;// Ahora probamos sin pintarlo, le sumamos uno porque este numero no lo pintamos

        if (minSiRojo <= minSiAzul && minSiRojo <= minSinPintar) {
            return minSiRojo;
        } else {
            if (minSiAzul <= minSinPintar) {
                return minSiAzul;
            } else {
                return minSinPintar;
            }
        }
    }
}

int backtrackImproved2(int i, int arreglo[], int n, int ultimoAzul, int ultimoRojo, bool hayAzul, bool hayRojo, int mayor, int menor)
{
    if (i == n - 1) {
        if (!hayRojo || arreglo[i] > ultimoRojo || !hayAzul || arreglo[i] < ultimoAzul){
            return 0;
        } else {;
            return 1;
        }
    }else{
        if(hayAzul && hayRojo && ultimoRojo == mayor && ultimoAzul == menor){
            return n - i + 1;
        }

        int minSiRojo = n, minSiAzul = n, minSinPintar = n;
        if (!hayRojo || arreglo[i] > ultimoRojo){ // Pintamos de rojo solo si el numero es mas grande que el ultimo rojo pintado
            minSiRojo = backtrackImproved2(i + 1, arreglo, n, ultimoAzul, arreglo[i], hayAzul, true, mayor, menor); // Aca obtenemos la cantidad minima de numero sin pintar si pintamos este num de rojo
            if (minSiRojo == 0) {
                return minSiRojo;
            }
        }


        if (!hayAzul || arreglo[i] < ultimoAzul){ // Igual que para el rojo ahora lo hacemos para el azul
            minSiAzul = backtrackImproved2(i + 1, arreglo, n, arreglo[i], ultimoRojo, true, hayRojo, mayor, menor);
            if (minSiAzul == 0) {
                return minSiAzul;
            }
        }

        minSinPintar = backtrackImproved2(i + 1, arreglo, n, ultimoAzul, ultimoRojo, hayAzul, hayRojo, mayor, menor) + 1;// Ahora probamos sin pintarlo, le sumamos uno porque este numero no lo pintamos

        if (minSiRojo <= minSiAzul && minSiRojo <= minSinPintar) {
            return minSiRojo;
        } else {
            if (minSiAzul <= minSinPintar) {
                return minSiAzul;
            } else {
                return minSinPintar;
            }
        }
    }
}


int ej1(int arreglo[], int n){
    return backtrack(0, arreglo, n, NULL, NULL, false, false);
}

int ej2(int arreglo[], int n) {
    return backtrackImproved(0, arreglo, n, NULL, NULL, false, false);
}

int ej2bis(int arreglo[], int n) {
    int menor = arreglo[0], mayor = arreglo[0];
    for (int i = 1; i < n; i++) {
        if (arreglo[i] < menor) {
            menor = arreglo[i];
        }
        if (mayor < arreglo[i]) {
            mayor = arreglo[i];
        }
    }
    return backtrackImproved2(0, arreglo, n, NULL, NULL, false, false, mayor, menor);
}



void generarArregloAleatorio(int arreglo[], int largo, int min, int max) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
    for (int i = 0; i < largo; i ++) {
        arreglo[i] = uni(rng);
    }
}

/*
int main() {
    //int arreglo[] = {3, 11, 0, 1, 3, 5, 2, 4 , 1, 0, 9, 3};
    //int largo = 12;

    //int arreglo[] = {0, 7, 1, 2, 2, 1, 5, 0};
    //int largo = 8;

    int largo = 30;

    //int arreglo[] = {3, -9, 50, 26, 21, 27, 8, 38, -1, 45, 39, -35, -2, -17, 7, 0, -20, 35, 27, 29, 22, 12, 33, -34, -33, -37, 21, 40, 8, -50, -36, -46, 35, -30, -4, -13, -26, -11, 34, 47, -39, -22, 20, -32, 46, 11, -32, 16, -29, 13};
    int arreglo[largo];
    generarArregloAleatorio(arreglo, largo, -largo, largo);

    for (int i = 0; i < largo; i ++) {
        cout << arreglo[i] << ", ";
    }
    cout << endl;

    int a,b,c,d;

    auto start = ya();
    b = ej2(arreglo, largo);
    auto end = ya();
    cout << "E2:"<< chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << endl;
    cout << b << endl;

    start = ya();
    d = ej3(arreglo, largo);
    end = ya();
    cout << "Ej3:" << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << endl;
    cout << d << endl;


    start = ya();
    a = ej1(arreglo, largo);
    end = ya();
    cout << "Ej1:" << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << endl;
    cout << a << endl;







    return 0;
}
//*/

int main() {
    int largo;
    std::cin >> largo;
    int arreglo[largo];

    int num;
    for (int i = 0; i < largo; ++i) {
        std::cin >> num;
        arreglo[i] = num;
    }

    for (int i = 0; i < largo; i ++) {
        cout << arreglo[i] << ", ";
    }
    cout << endl;
    int a,b,c,d;

    auto start = ya();
    d = ej3(arreglo, largo);
    auto end = ya();
    cout << "Ej3:" << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << endl;
    cout << d << endl;

    return 0;
}