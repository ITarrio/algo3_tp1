#include <iostream>

class SinPintarR {
    int **m, largo, *arreglo;
public:
    SinPintarR(int arreglo[], int largo);
    virtual ~SinPintarR();

    int getOptimoPara(int ultimoRojo, int ultimoAzul);
private:
    void obtenerOptimo(int ultimoRojo, int ultimoAzul);
    int buscarOptimoRojo(int indiceRojoSiguiente, int indiceAzulFijo);
    int buscarOptimoAzul(int indiceAzulSiguiente, int indiceRojoFijo);
};

SinPintarR::SinPintarR(int arreglo[], int largo) {
    this->arreglo = arreglo;
    this->largo = largo;
    this->m = new int *[largo+1];
    for (int i = 0; i <= largo; i++) {
        m[i] = new int[largo+1];
        for(int j = 0; j <= largo; j++){
            m[i][j] = -1;
        }
    }
    m[0][largo] = largo - 1; // Sabemos que si pintamos el primero de rojo o de azul nada mas vamos a tener n(el largo) -1 (el que estamos pintando)
    m[largo][0] = largo - 1;
    m[largo][largo] = largo; // Y si no pintamos ninguno van a quedar los n sin pintar
}

SinPintarR::~SinPintarR() {
    for(int i = 0; i <= largo; i++) {
        delete[] m[i];
    }
    delete [] m;
}

int SinPintarR::getOptimoPara(int ultimoRojo, int ultimoAzul) {
    if (this->m[ultimoRojo][ultimoAzul] == -1) {//Si no lo calculamos todavia lo mandamos a calcular
        obtenerOptimo(ultimoRojo, ultimoAzul);
    }
    return this->m[ultimoRojo][ultimoAzul];
}

void SinPintarR::obtenerOptimo(int ultimoRojo, int ultimoAzul) {
    int valor;
    if ((ultimoAzul < ultimoRojo && ultimoRojo != largo) || ultimoAzul == largo){
        valor = buscarOptimoRojo(ultimoRojo, ultimoAzul);
    }else{
        valor = buscarOptimoAzul(ultimoAzul, ultimoRojo);
    }
    this->m[ultimoRojo][ultimoAzul] = valor;
}

int SinPintarR::buscarOptimoRojo(int indiceRojoSiguiente, int indiceAzulFijo) {
    int optimo = getOptimoPara(this->largo, this->largo); // Ponemos como el optimo como si no hubiesemos pintado ningun rojo antes
    for(int r = 0; r < indiceRojoSiguiente; r++){ // Dejamos el indice del azul fijo y movemos el rojo, para buscar cual es el que menos numeros sin pintar tiene
        if (r != indiceAzulFijo && this->arreglo[r] < this->arreglo[indiceRojoSiguiente] && getOptimoPara(r, indiceAzulFijo) < optimo) {
            optimo = getOptimoPara(r, indiceAzulFijo);
        }
    }
    if(indiceRojoSiguiente != this->largo && getOptimoPara(this->largo, indiceAzulFijo) < optimo){
        optimo = getOptimoPara(this->largo, indiceAzulFijo);
    }
    // Una vez encontrado el optimo devolvemos este menos uno ya que este nuevo numero lo pintamos
    return optimo - 1;
}

int SinPintarR::buscarOptimoAzul(int indiceAzulSiguiente, int indiceRojoFijo) { // Lo mismo que con el rojo pero con el azul
    int optimo = getOptimoPara(this->largo, this->largo);
    for(int a = 0; a < indiceAzulSiguiente; a++){
        if (a != indiceRojoFijo && this->arreglo[a] > this->arreglo[indiceAzulSiguiente] && getOptimoPara(indiceRojoFijo, a) < optimo) {
            optimo = getOptimoPara(indiceRojoFijo, a);
        }
    }
    if(indiceAzulSiguiente != this->largo && getOptimoPara(indiceRojoFijo, this->largo) < optimo){
        optimo = getOptimoPara(indiceRojoFijo, this->largo);
    }
    return optimo - 1;
}

int ej4(int a[], int n){
    SinPintarR m(a, n);

    //Tenemos que fijarnos cual es el menor (lo recorremos de atras para adelante nada mas para demostrar que se puede
    int optimo = n;
    for (int i = n; i >= 0; i--) {
        for (int j = n; j >= 0; j--) {
            if ((j != i || i == n) && m.getOptimoPara(i, j) < optimo) {
                optimo = m.getOptimoPara(i, j);
                if (optimo == 0){
                    return optimo;
                }
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