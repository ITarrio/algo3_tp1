#include <iostream>

//Retorna la cantidad de numeros sin pintar
int cantidadDeNumerosSinPintar(int i, int arreglo[], int n, int ultimoAzulPintado, int ultimoRojoPintado, bool hayAzulPintado, bool hayRojoPintado) {
    if (i == n - 1) {
        //Aqui llegamos al fin de la recursion(caso base), como es el ultimo numero devolvemos 0 si pintamos este numero y uno si lo dejamos sin pintar
        if (!hayRojoPintado || arreglo[i] > ultimoRojoPintado || !hayAzulPintado || arreglo[i] < ultimoAzulPintado){
            return 0;
        } else {;
            return 1;
        }
    }else{
        int minSiRojo = n, minSiAzul = n, minSinPintar;
        if (!hayRojoPintado || arreglo[i] > ultimoRojoPintado) { // Pintamos de rojo solo si el numero es mas grande que el ultimo rojo pintado
            minSiRojo = cantidadDeNumerosSinPintar(i + 1, arreglo, n, ultimoAzulPintado, arreglo[i], hayAzulPintado, true); // Aca obtenemos la cantidad minima de numero sin pintar si pintamos este num de rojo
        }

        if (!hayAzulPintado || arreglo[i] < ultimoAzulPintado) { // Igual que para el rojo ahora lo hacemos para el azul
            minSiAzul = cantidadDeNumerosSinPintar(i + 1, arreglo, n, arreglo[i], ultimoRojoPintado, true, hayRojoPintado);
        }

        minSinPintar = cantidadDeNumerosSinPintar(i + 1, arreglo, n, ultimoAzulPintado, ultimoRojoPintado, hayAzulPintado, hayRojoPintado) + 1;// Ahora probamos sin pintarlo, le sumamos uno porque este numero no lo pintamos

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

int ej1(int arreglo[], int n){
    return cantidadDeNumerosSinPintar(0, arreglo, n, NULL, NULL, false, false);
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

    std::cout<<ej1(arreglo, largo);
    return 0;
}