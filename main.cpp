#include <iostream>
#include "Simulador2D.h"
#include <limits>

// definicion de prototipos.
int menu();

template <typename T>
void redimensionar(Simulador2D<T> &grid);

int main(){

    std::cout << "--- Inicializando Sistema (Tipo FLOAT) ---" << std::endl;
    Simulador2D<float> A(5, 5);

    std::cout << "--- Agregando Fuentes de Concentración ---" << std::endl;
    A.agregarFuente(100.0);
    std::cout << "Agregar Fuente 1 (Valor 100.0): Éxito" << std::endl;
    A.agregarFuente(50.0);
    std::cout << "Agregar Fuente 2 (Valor 50.0): Éxito" << std::endl;

    std::cout << "Agregando a la posicion (2, 2): 100" << std::endl;
    A._grid[2][2] = 100.0;
    A._grid[4][0] = 50.0;


    std::cout << "\n--- Grid Inicial (Paso 0) ---" << std::endl;
    A.mostrarGrid();

    int opcion = menu();

    switch (opcion)
    {
    case 1:
        A.simularPaso();
        std::cout << "\n--- Grid Tras 1 Paso ---" << std::endl;
        A.mostrarGrid();
        break;

    case 2:
        
        redimensionar(A);
        break;
    
    default:
        break;
    }

    return 0;
}

// funcion que muestra el menu principal de accioines.
int menu(){

    int opcion = 0;

    std::cout << "\n--- Opciones ---" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "[1] Simular 1 paso" << std::endl;
    std::cout << "[2] Redimensionar" << std::endl;
    std::cout << "[3] Salir" << std::endl;

    std::cin >> opcion;

    if(std::cin.good()){

        return opcion;

    }
    else{

        std::cout << "--- No ingresó una opción válida, finalizando ---" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;

    }

}

// funcion que pregunta la cantidad de filas y columnas de 
template <typename T>
void redimensionar(Simulador2D<T> &grid){

    int filas;
    int columnas;

    std::cout << "--- Redimensionar Grid ---" << std::endl;
    std::cout << "--------------------------" << std::endl;

    std::cout << "Valor de filas: ";
    std::cin >> filas;

    std::cout << "\nValor de columnas: ";
    std::cin >> columnas;

    grid.redimensionarGrid(filas, columnas);


    

}


