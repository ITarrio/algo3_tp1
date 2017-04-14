
#include <iostream>

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
    int largo;
    std::cin >> largo;
    int arreglo[largo];

    int num;
    for (int i = 0; i < largo; ++i) {
        std::cin >> num;
        arreglo[i] = num;
    }

    std::cout << ej3(arreglo, largo);
    return 0;
}