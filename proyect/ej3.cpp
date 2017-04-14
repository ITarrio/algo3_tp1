#include <iostream>

class SinPintarM {
    int **m, largo;
public:
    SinPintarM(int);
    virtual ~SinPintarM();

    void setOptimoPara(int cantSinPintar, int ultimoRojo, int ultimoAzul);
    int getOptimoPara(int ultimoRojo, int ultimoAzul);
};

SinPintarM::SinPintarM(int largo) {
    this->largo = largo;
    this->m = new int *[largo];
    for(int i = 0; i < largo; i++)
        m[i] = new int[largo];
}

SinPintarM::~SinPintarM() {
    for(int i = 0; i < largo; i++) {
        delete (m[i]);
    }
    delete(m);
}

void SinPintarM::setOptimoPara(int cantSinPintar, int ultimoRojo, int ultimoAzul) {
    this->m[ultimoRojo][ultimoAzul] = cantSinPintar;
}

int SinPintarM::getOptimoPara(int ultimoRojo, int ultimoAzul) {
    return this->m[ultimoRojo][ultimoAzul];
}

int buscarOptimoRojo(int indiceRojoSiguiente, int indiceAzulFijo, int arreglo[], SinPintarM &m, int n ) {
    int optimo = m.getOptimoPara(n, indiceAzulFijo); // Si no encontramos un numero menor anterior, siempre podemos partir si no pintamos todavia nada de rojo
    for(int r = 0; r < indiceRojoSiguiente; r++){
        if (r != indiceAzulFijo && arreglo[r] < arreglo[indiceRojoSiguiente] && m.getOptimoPara(r, indiceAzulFijo) < optimo) {
            optimo = m.getOptimoPara(r, indiceAzulFijo);
        }
    }
    return optimo - 1;
}

int buscarOptimoAzul(int indiceAzulSiguiente, int indiceRojoFijo, int arreglo[], SinPintarM &m, int n ) {
    int optimo = m.getOptimoPara(indiceRojoFijo, n);
    for(int a = 0; a < indiceAzulSiguiente; a++){
        if (a != indiceRojoFijo && arreglo[a] > arreglo[indiceAzulSiguiente] && m.getOptimoPara(indiceRojoFijo, a) < optimo) {
            optimo = m.getOptimoPara(indiceRojoFijo, a);
        }
    }
    return optimo - 1;
}

int ej3(int a[], int n){
    SinPintarM m(n +1);

    m.setOptimoPara(n - 1, 0, n); // Sabemos que si pintamos el primero de rojo o de azul nada mas vamos a tener n(el largo) -1 (el que estamos pintando)
    m.setOptimoPara(n - 1, n, 0);
    m.setOptimoPara(n, n, n); // Y si no pintamos ninguno van a quedar los n sin pintar

    for (int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            m.setOptimoPara(buscarOptimoRojo(i, j, a, m, n), i, j);
            m.setOptimoPara(buscarOptimoAzul(i, j, a, m, n), j, i);
        }
        m.setOptimoPara(buscarOptimoRojo(i, n, a, m, n), i, n);
        m.setOptimoPara(buscarOptimoAzul(i, n, a, m, n), n, i);
    }

    //buscamos el optimo
    int optimo = n;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if ((j != i || i == n) && m.getOptimoPara(i, j) < optimo) {
                optimo = m.getOptimoPara(i, j);
            }
        }
    }

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