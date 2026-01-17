#include <iostream>
#include <string>

using namespace std;

// Definimos constantes para el tamaño del tablero (Tema 6 - Arrays)
const int FILAS = 6;
const int COLUMNAS = 7;

// Prototipos de funciones (Tema 7 - Programación Modular)
void mostrarTitulo();
void inicializarTablero(char tablero[FILAS][COLUMNAS]);
void dibujarTablero(char tablero[FILAS][COLUMNAS]);
bool introducirFicha(char tablero[FILAS][COLUMNAS], int columna, char jugador);
bool comprobarVictoria(char tablero[FILAS][COLUMNAS], char jugador);
bool tableroLleno(char tablero[FILAS][COLUMNAS]);

int main() {
    char tablero[FILAS][COLUMNAS];
    bool juegoTerminado = false;
    char jugadorActual = 'X'; // Jugador 1 es X, Jugador 2 es O
    int columna;
    bool fichaColocada;

    mostrarTitulo();
    
    // Inicializamos el tablero con espacios vacíos
    inicializarTablero(tablero);

    // Bucle principal del juego (Tema 5 - Estructuras iterativas)
    do {
        dibujarTablero(tablero);
        
        // Entrada de datos protegida
        do {
            cout << "Turno del Jugador " << jugadorActual << ". Elige columna (1-7): ";
            cin >> columna;
            
            // Ajustamos porque los arrays empiezan en 0, pero el usuario ve 1-7
            columna--; 

            if (columna < 0 || columna >= COLUMNAS) {
                cout << "Columna no valida. Intentalo de nuevo." << endl;
                fichaColocada = false;
            } else {
                // Intentamos poner la ficha (simulando gravedad)
                fichaColocada = introducirFicha(tablero, columna, jugadorActual);
                if (!fichaColocada) {
                    cout << "Esa columna esta llena. Elige otra." << endl;
                }
            }

        } while (!fichaColocada);

        // Comprobamos si el movimiento actual ganó la partida
        if (comprobarVictoria(tablero, jugadorActual)) {
            dibujarTablero(tablero);
            cout << "\n\n***************************************" << endl;
            cout << "   FELICIDADES JUGADOR " << jugadorActual << "! HAS GANADO!" << endl;
            cout << "***************************************\n" << endl;
            juegoTerminado = true;
        } 
        // Comprobamos si hay empate
        else if (tableroLleno(tablero)) {
            dibujarTablero(tablero);
            cout << "Empate! El tablero esta lleno." << endl;
            juegoTerminado = true;
        } else {
            // Cambio de turno: Si es X pasa a O, si no, a X
            jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
        }

    } while (!juegoTerminado);

    cout << "Gracias por jugar." << endl;
    return 0;
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

void mostrarTitulo() {
    // Arte ASCII solicitado
    cout << "  _  _                   ____                            " << endl;
    cout << " | || |   ___ _ __      |  _ \\ __ _ _   _  __ _          " << endl;
    cout << " | || |_ / _ \\ '_ \\     | |_) / _` | | | |/ _` |         " << endl;
    cout << " |__   _|  __/ | | |    |  _ < (_| | |_| | (_| |         " << endl;
    cout << "    |_|  \\___|_| |_|    |_| \\_\\__,_|\\__, |\\__,_|         " << endl;
    cout << "                                    |___/                " << endl;
    cout << "            por Marcos de Aza                            " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << endl;
}

// Llena la matriz de espacios en blanco (Tema 6)
void inicializarTablero(char tablero[FILAS][COLUMNAS]) {
    for(int i = 0; i < FILAS; i++) {
        for(int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = ' ';
        }
    }
}

// Muestra el estado actual del juego
void dibujarTablero(char tablero[FILAS][COLUMNAS]) {
    cout << "\n";
    cout << " 1   2   3   4   5   6   7" << endl;
    cout << "---------------------------" << endl;
    for(int i = 0; i < FILAS; i++) {
        cout << "|";
        for(int j = 0; j < COLUMNAS; j++) {
            cout << " " << tablero[i][j] << " |";
        }
        cout << endl;
        cout << "---------------------------" << endl;
    }
}

// Coloca la ficha en la posición más baja disponible de la columna (Gravedad)
bool introducirFicha(char tablero[FILAS][COLUMNAS], int columna, char jugador) {
    // Recorremos desde abajo (FILAS-1) hacia arriba (0)
    for (int i = FILAS - 1; i >= 0; i--) {
        if (tablero[i][columna] == ' ') {
            tablero[i][columna] = jugador;
            return true; // Ficha colocada con éxito
        }
    }
    return false; // La columna estaba llena
}

// Comprueba si el tablero está lleno (Empate)
bool tableroLleno(char tablero[FILAS][COLUMNAS]) {
    for(int j = 0; j < COLUMNAS; j++) {
        if (tablero[0][j] == ' ') return false; // Si hay un hueco arriba, no está lleno
    }
    return true;
}

// Algoritmo para verificar 4 en línea
bool comprobarVictoria(char tablero[FILAS][COLUMNAS], char jugador) {
    // 1. Comprobar Horizontal (-)
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] == jugador && 
                tablero[i][j+1] == jugador && 
                tablero[i][j+2] == jugador && 
                tablero[i][j+3] == jugador) {
                return true;
            }
        }
    }

    // 2. Comprobar Vertical (|)
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == jugador && 
                tablero[i+1][j] == jugador && 
                tablero[i+2][j] == jugador && 
                tablero[i+3][j] == jugador) {
                return true;
            }
        }
    }

    // 3. Comprobar Diagonal descendente (\)
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] == jugador && 
                tablero[i+1][j+1] == jugador && 
                tablero[i+2][j+2] == jugador && 
                tablero[i+3][j+3] == jugador) {
                return true;
            }
        }
    }

    // 4. Comprobar Diagonal ascendente (/)
    for (int i = 3; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] == jugador && 
                tablero[i-1][j+1] == jugador && 
                tablero[i-2][j+2] == jugador && 
                tablero[i-3][j+3] == jugador) {
                return true;
            }
        }
    }

    return false;
}