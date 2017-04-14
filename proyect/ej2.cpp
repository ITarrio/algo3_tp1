#include <iostream>

int cantidadDeNumerosSinPintarMejorado(int i, int arreglo[], int n, int ultimoAzul, int ultimoRojo, bool hayAzul, bool hayRojo ) {
    if (i == n - 1) {
        //Aqui llegamos al fin de la recursion(caso base), como es el ultimo numero devolvemos 0 si pintamos este numero y uno si lo dejamos sin pintar
        if (!hayRojo || arreglo[i] > ultimoRojo || !hayAzul || arreglo[i] < ultimoAzul){
            return 0;
        } else {;
            return 1;
        }
    }else{
        int minSiRojo = n, minSiAzul = n, minSinPintar;
        if (!hayRojo || arreglo[i] > ultimoRojo){ // Pintamos de rojo solo si el numero es mas grande que el ultimo rojo pintado
            minSiRojo = cantidadDeNumerosSinPintarMejorado(i + 1, arreglo, n, ultimoAzul, arreglo[i], hayAzul, true); // Aca obtenemos la cantidad minima de numero sin pintar si pintamos este num de rojo
            if (minSiRojo == 0) { // Si es el optimo ya devuelvo esto
                return minSiRojo;
            }
        }


        if (!hayAzul || arreglo[i] < ultimoAzul){ // Igual que para el rojo ahora lo hacemos para el azul
            minSiAzul = cantidadDeNumerosSinPintarMejorado(i + 1, arreglo, n, arreglo[i], ultimoRojo, true, hayRojo);
            if (minSiAzul == 0) { // Si es el optimo ya devuelvo esto
                return minSiAzul;
            }
        }

        minSinPintar = cantidadDeNumerosSinPintarMejorado(i + 1, arreglo, n, ultimoAzul, ultimoRojo, hayAzul, hayRojo) + 1;// Ahora probamos sin pintarlo, le sumamos uno porque este numero no lo pintamos

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

int ej2(int arreglo[], int n){
    return cantidadDeNumerosSinPintarMejorado(0, arreglo, n, NULL, NULL, false, false);
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

    std::cout<<ej2(arreglo, largo);
    return 0;
}