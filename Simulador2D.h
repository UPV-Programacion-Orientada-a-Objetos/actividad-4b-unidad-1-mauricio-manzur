#include <iostream>

template <typename T>
class Simulador2D {
public:
    // Matriz de la cuadrícula (Dinámica y Genérica)
    T **_grid = nullptr;
    int _filas = 0;
    int _columnas = 0;

    // Vector de Fuentes (Dinámico y Genérico)
    T *_fuentes = nullptr;
    int _numFuentes = 0;
    int _capacidadFuentes = 0;

    // Vector de Constantes (Estático)
    float _constantes[3]; // [0] = Coeficiente de Difusión, [1] = DeltaX, [2] = DeltaT

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
        // inicializar constantes si es necesario
        _constantes[0] = 0.0f;
        _constantes[1] = 0.0f;
        _constantes[2] = 0.0f;
    } // Constructor

    ~Simulador2D(){
        std::cout << "\nLiberando memoria de Grid y Fuentes...";
        // eliminar matriz si existe
        if (_grid != nullptr) {
            for(int i = 0; i < _filas; i++){
                delete[] _grid[i];
            }
            delete[] _grid;
            _grid = nullptr;
        }
        // eliminar vector dinámico de fuentes si existe
        delete[] _fuentes;
        _fuentes = nullptr;
        std::cout << " Sistema Liberado." << std::endl;
    } // Destructor

    void redimensionarGrid(int nuevaF, int nuevaC){
        if (nuevaF <= 0 || nuevaC <= 0) {
            std::cout << "Dimensiones inválidas." << std::endl;
            return;
        }
        // Crear nueva matriz e inicializar a 0
        T **nuevaMat = new T*[nuevaF];
        for(int i = 0; i < nuevaF; i++){
            nuevaMat[i] = new T[nuevaC];
            for(int j = 0; j < nuevaC; j++){
                nuevaMat[i][j] = 0;
            }
        }
        // Copiar la región común
        int filasACopiar = (nuevaF < _filas ? nuevaF : _filas);
        int colsACopiar  = (nuevaC < _columnas ? nuevaC : _columnas);
        for(int i = 0; i < filasACopiar; i++){
            for(int j = 0; j < colsACopiar; j++){
                nuevaMat[i][j] = _grid[i][j];
            }
        }
        // Liberar la matriz anterior
        if (_grid != nullptr) {
            for(int i = 0; i < _filas; i++){
                delete[] _grid[i];
            }
            delete[] _grid;
        }
        // Actualizar puntero y dimensiones
        _grid = nuevaMat;
        _filas = nuevaF;
        _columnas = nuevaC;
        std::cout << "Se añadió correctamente la nueva dimension de la matriz" << std::endl;
    }

    // metodo para agregar una fuente al vector dinamico ( si numero de fuentes excede la capacidad del vector, agregar uno nuevo.)
    void agregarFuente(T valor){
        if(_numFuentes >= _capacidadFuentes){
            int nuevaCap = (_capacidadFuentes == 0) ? 1 : (_capacidadFuentes + 1);
            T *nuevaFuentes = new T[nuevaCap];
            // Copiar existentes
            for(int i = 0; i < _numFuentes; i++){
                nuevaFuentes[i] = _fuentes ? _fuentes[i] : T{};
            }
            // Liberar anterior
            delete[] _fuentes;
            _fuentes = nuevaFuentes;
            _capacidadFuentes = nuevaCap;
        }
        // Agregar al final
        _fuentes[_numFuentes] = valor;
        _numFuentes++;
        std::cout << "Se agregó la fuente correctamente." << std::endl;
    } // Expansión manual del vector dinámico si es necesario

    void simularPaso(){
        if (_filas <= 0 || _columnas <= 0) return;

        // Crear matriz temporal del mismo tamaño
        T **temp = new T*[_filas];
        for (int i = 0; i < _filas; ++i) {
            temp[i] = new T[_columnas];
            for (int j = 0; j < _columnas; ++j) {
                temp[i][j] = _grid[i][j]; // inicializamos con el estado actual
            }
        }

        // Difusión para celdas internas (excluye bordes)
        if (_filas >= 3 && _columnas >= 3) {
            for (int i = 1; i < _filas - 1; ++i) {
                for (int j = 1; j < _columnas - 1; ++j) {
                    double arriba   = static_cast<double>(_grid[i-1][j]);
                    double abajo    = static_cast<double>(_grid[i+1][j]);
                    double izquierda= static_cast<double>(_grid[i][j-1]);
                    double derecha  = static_cast<double>(_grid[i][j+1]);
                    double promedio = (arriba + abajo + izquierda + derecha) / 4.0;
                    temp[i][j] = static_cast<T>(promedio);
                }
            }
        }

        // Bordes: condición de contorno
        T borde = (_numFuentes > 0) ? _fuentes[0] : static_cast<T>(0);
        // Filas superior e inferior
        for (int j = 0; j < _columnas; ++j) {
            temp[0][j] = borde;
            temp[_filas - 1][j] = borde;
        }
        // Columnas izquierda y derecha
        for (int i = 0; i < _filas; ++i) {
            temp[i][0] = borde;
            temp[i][_columnas - 1] = borde;
        }

        // Copiar temp a _grid
        for (int i = 0; i < _filas; ++i) {
            for (int j = 0; j < _columnas; ++j) {
                _grid[i][j] = temp[i][j];
            }
        }

        // Liberar temp
        for (int i = 0; i < _filas; ++i) delete[] temp[i];
        delete[] temp;
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
