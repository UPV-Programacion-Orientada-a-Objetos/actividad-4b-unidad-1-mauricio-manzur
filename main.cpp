#include <iostream>
#include "Simulador2D.h"

void inicio();

int main(){

    inicio();





    return 0;

}


void inicio(){

    do{

        int opcion = 0;

        std::cout << "---- Modelado de Propagación Física Manzur ----" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "[1] Construir una nueva Matriz" << std::endl;
        std::cout << "[2] Aplicar Valores a la Matriz (Por fila)" << std::endl;
        std::cout << "[3] Simular paso siguiente" << std::endl;
        std::cout << "[4] Finalizar Sistema" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "\n" << std::endl;

        std::cin.ignore();
        std::cin >> opcion;

        if(std::cin.good()){

            switch (opcion)
            {
            case 1:
                /* code */
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                std::cout << "\n--- GRACIAS POR UTILIZAR LA APLICACIÓN, FINALIZANDO SISTEMA ---" << std::endl;
                break;

            default:
                std::cout << "\n--- INGRESE UNA OPCIÓN VÁLIDA ---" << std::endl;
                break;
            }

        }


    }while(true);

}