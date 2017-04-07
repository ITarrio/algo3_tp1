#include <iostream>
#include <array>
#include <vector>
#include <chrono>

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
        if (!hayRojoPintado || arreglo[i] > ultimoRojoPintado){ // Pintamos de rojo solo si el numero es mas grande que el ultimo rojo pintado
            minSiRojo = backtrack(i + 1, arreglo, n, ultimoAzulPintado, arreglo[i], hayAzulPintado, true); // Aca obtenemos la cantidad minima de numero sin pintar si pintamos este num de rojo
        }

        if (!hayAzulPintado || arreglo[i] < ultimoAzulPintado){ // Igual que para el rojo ahora lo hacemos para el azul
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

int backtrackImproved(int i, int arreglo[], int n, int ultimoAzul, int ultimoRojo, bool hayAzul, bool hayRojo, int sinPintar )
{
    if (i == n - 1) {
        if (!hayRojo || arreglo[i] > ultimoRojo || !hayAzul || arreglo[i] < ultimoAzul){
            return 0;
        } else {;
            return 1;
        }
    }else{
        int minSiRojo = n, minSiAzul = n, minSinPintar = n;
        if (!hayRojo || arreglo[i] > ultimoRojo){ // Pintamos de rojo solo si el numero es mas grande que el ultimo rojo pintado
            minSiRojo = backtrackImproved(i + 1, arreglo, n, ultimoAzul, arreglo[i], hayAzul, true, sinPintar); // Aca obtenemos la cantidad minima de numero sin pintar si pintamos este num de rojo
            if (minSiRojo == sinPintar) {
                return minSiRojo;
            }
        }


        if (!hayAzul || arreglo[i] < ultimoAzul){ // Igual que para el rojo ahora lo hacemos para el azul
            minSiAzul = backtrackImproved(i + 1, arreglo, n, arreglo[i], ultimoRojo, true, hayRojo, sinPintar);
            if (minSiAzul == sinPintar) {
                return minSiAzul;
            }
        }

        minSinPintar = backtrackImproved(i + 1, arreglo, n, ultimoAzul, ultimoRojo, hayAzul, hayRojo, sinPintar + 1) + 1;// Ahora probamos sin pintarlo, le sumamos uno porque este numero no lo pintamos

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

int backtrackImproved2(int i, int arreglo[], int n, int ultimoAzul, int ultimoRojo, bool hayAzul, bool hayRojo, int sinPintar, int mayor, int menor)
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
            minSiRojo = backtrackImproved2(i + 1, arreglo, n, ultimoAzul, arreglo[i], hayAzul, true, sinPintar, mayor, menor); // Aca obtenemos la cantidad minima de numero sin pintar si pintamos este num de rojo
            if (minSiRojo == sinPintar) {
                return minSiRojo;
            }
        }


        if (!hayAzul || arreglo[i] < ultimoAzul){ // Igual que para el rojo ahora lo hacemos para el azul
            minSiAzul = backtrackImproved2(i + 1, arreglo, n, arreglo[i], ultimoRojo, true, hayRojo, sinPintar, mayor, menor);
            if (minSiAzul == sinPintar) {
                return minSiAzul;
            }
        }

        minSinPintar = backtrackImproved2(i + 1, arreglo, n, ultimoAzul, ultimoRojo, hayAzul, hayRojo, sinPintar + 1, mayor, menor) + 1;// Ahora probamos sin pintarlo, le sumamos uno porque este numero no lo pintamos

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
    return backtrackImproved(0, arreglo, n, NULL, NULL, false, false, 0);
}



int buscarOptimoRojo(int indiceRojoSiguiente, int indiceAzulFijo, int arreglo[], int **m, int n ) {
    int optimo = m[n][indiceAzulFijo];
    for(int r = 0; r < indiceRojoSiguiente; r++){
        if (r != indiceAzulFijo && arreglo[r] < arreglo[indiceRojoSiguiente] && m[r][indiceAzulFijo] < optimo) {
            optimo = m[r][indiceAzulFijo];
        }
    }
    return optimo - 1;
}

int buscarOptimoAzul(int indiceAzulSiguiente, int indiceRojoFijo, int arreglo[], int **m, int n ) {
    int optimo = m[indiceRojoFijo][n];
    for(int a = 0; a < indiceAzulSiguiente; a++){
        if (a != indiceRojoFijo && arreglo[a] > arreglo[indiceAzulSiguiente] && m[indiceRojoFijo][a] < optimo) {
            optimo = m[indiceRojoFijo][a];
        }
    }
    return optimo - 1;
}

int ej3(int a[], int n){
    int **m;
    m = new int *[n+1];
    for(int i = 0; i <n+1; i++)
        m[i] = new int[n+1];

    //Para el primer indice ya sabemos que pasa
    m[0][n] = n - 1;
    m[n][0] = n - 1;
    m[n][n] = n;

    for (int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            m[i][j] = buscarOptimoRojo(i, j, a, m, n);
            m[j][i] = buscarOptimoAzul(i, j, a, m, n);
        }
        m[i][n] = buscarOptimoRojo(i, n, a, m, n);
        m[n][i] = buscarOptimoAzul(i, n, a, m, n);
    }

    //buscamos el optimo
    int optimo = n;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if ((j != i || i == n) && m[i][j] < optimo) {
                optimo = m[i][j];
            }
        }
    }

    for(int i = 0; i < n+1; i++)
        delete(m[i]);
    delete(m);

    return optimo;
}

int main() {
    //int arreglo[] = {3, 11, 0, 1, 3, 5, 2, 4 , 1, 0, 9, 3};
    //int largo = 12;

    //int arreglo[] = {0, 7, 1, 2, 2, 1, 5, 0};
    //int largo = 8;

    int largo = 40;
    int arreglo[largo];
    for (int i = 0; i < largo; i++) {
        arreglo[i] = std::rand();
    }

    int a,b,c;


    auto start = ya();
    c = ej3(arreglo, largo);
    auto end = ya();
    cout << "Ej3:" << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << endl;


    start = ya();
    b = ej2(arreglo, largo);
    end = ya();
    cout << "Ej2:"<< chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << endl;

    start = ya();
    b = ej2(arreglo, largo);
    end = ya();
    cout << "Ej2:"<< chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << endl;

    start = ya();
    a = ej1(arreglo, largo);
    end = ya();
    cout << "Ej1:" << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << endl;

    cout << a << b << c;

    return 0;
}

