template <typename T>
class Simulador2D {
private:
    // Matriz de la cuadrícula (Dinámica y Genérica)
    T **_grid = nullptr;
    int _filas;
    int _columnas;

    // Vector de Fuentes (Dinámico y Genérico)
    T *_fuentes = nullptr;
    int _numFuentes;
    int _capacidadFuentes;

    // Vector de Constantes (Estático)
    float _constantes[3]; // [0] = Coeficiente de Difusión, [1] = DeltaX, [2] = DeltaT

public:
    // MÉTODOS PÚBLICOS OBLIGATORIOS:
    Simulador2D(int f, int c){

        // crear grid nuevo
        _grid = new T*[f];

        for(int i = 0; i < f; i++){

            _grid[i] = new T[c];

        }   

        for(int i = 0; i < f; i++){

            for(int j = 0; j < c; j++){

                _grid[i][j] = 0;

            }

        }

        _filas = f;
        _columnas = c;

    } // Constructor

    ~Simulador2D(){

        std::cout << "\nLiberando memoria de Grid y Fuentes...";

        // elimino la matriz de la memoria cuando se destruya el objeto.
        for(int i = 0; i < _filas; i++){

            delete[] _grid[i]; 

        }

        delete[] _grid;

        // elimino el vector dinámico de la memoria
        delete[] _fuentes;

        std::cout << " Sistema Liberado." << std::endl;

    } // Destructor

    void redimensionarGrid(int nuevaF, int nuevaC){

        T **nuevaMat = new T*[nuevaF];

        for(int i = 0; i < nuevaF; i++){

            nuevaMat[i] = new T[nuevaC];

        }

        // copiar todos los elementos del vector anterior y pasarlos al nuevo vector Columna + 1
        for(int i = 0; i < nuevaF; i++){

            for(int j = 0; j < nuevaC; j++){

                nuevaMat[i][j] = _grid[i][j];

            }

        }

        _grid = nuevaMat;

        // eliminar el contenido de las filas de la matriz.
        for(int i = 0; i < nuevaF; i++){

            delete[] nuevaMat[i];

        }

        // eliminar el vector principal
        delete[] nuevaMat;

        nuevaMat = nullptr;

        _filas = nuevaF;
        _columnas = nuevaC;

        std::cout << "Se añadió correctamente la nueva dimension de la matriz" << std::endl;

    }

    // metodo para agregar una fuente al vector dinamico ( si numero de fuentes excede la capacidad del vector, agregar uno nuevo.)
    void agregarFuente(T valor){

        if(_numFuentes >= _capacidadFuentes){

            T *nuevaFuentes = new T[_capacidadFuentes+1];

            for(int i = 0; i < _capacidadFuentes; i++){

                nuevaFuentes[i] = _fuentes[i];
            
            }

            _fuentes = nuevaFuentes;
            delete[] nuevaFuentes;
            nuevaFuentes = nullptr;

            _capacidadFuentes++;

        }

        _fuentes[_capacidadFuentes] = valor;
        _numFuentes++;

        std::cout << "Se agregó la fuente correctamente." << std::endl;

    } // Expansión manual del vector dinámico si es necesario

    void simularPaso(){



    } // Implementación del algoritmo


    // metodo que imprimie el grid en pantalla
    void mostrarGrid(){

        std::cout << "---- Visualizar Grid ----" << std::endl;

        for(int i = 0; i < _filas; i++){

            std::cout << "| ";

            for(int j = 0; j < _columnas; j++){

                std::cout << " " << _grid[i][j] << " |";

            }

            std::cout << std::endl;

        }

    }



};
