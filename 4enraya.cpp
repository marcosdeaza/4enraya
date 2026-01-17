#include <iostream>
#include <cstdlib> // Para rand() y srand() (Aleatorios)
#include <ctime>   // Para time() (Semilla aleatoria)

using namespace std;

// --- CONSTANTES ---
const int FILAS = 6;
const int COLUMNAS = 7;

// --- PROTOTIPOS ---
void mostrarTitulo();
void inicializarTablero(char tablero[FILAS][COLUMNAS]);
void dibujarTablero(char tablero[FILAS][COLUMNAS]);
bool introducirFicha(char tablero[FILAS][COLUMNAS], int columna, char jugador);
bool comprobarVictoria(char tablero[FILAS][COLUMNAS], char jugador);
bool tableroLleno(char tablero[FILAS][COLUMNAS]);
int pensarJugadaMaquina(char tablero[FILAS][COLUMNAS], char soyMaquina, char esRival);

int main() {
    // Semilla para que los números aleatorios cambien en cada partida
    srand(time(NULL));

    char tablero[FILAS][COLUMNAS];
    bool juegoTerminado = false;
    char jugadorActual = 'X'; // El humano (X) siempre empieza
    int columna;
    bool fichaColocada;
    int modoJuego;

    mostrarTitulo();

    // --- MENÚ DE SELECCIÓN ---
    cout << "SELECCIONA MODO DE JUEGO:" << endl;
    cout << "1. Humano vs Humano (PvP)" << endl;
    cout << "2. Humano vs Maquina (PvE)" << endl;
    cout << "Elige una opcion (1 o 2): ";
    cin >> modoJuego;

    // Validación básica del menú
    if (modoJuego != 1 && modoJuego != 2) {
        modoJuego = 2; // Por defecto jugamos contra la máquina si se equivoca
        cout << "Opcion no valida. Jugaras contra la Maquina por defecto." << endl;
    }

    inicializarTablero(tablero);

    // --- BUCLE PRINCIPAL DEL JUEGO (Game Loop) ---
    do {
        dibujarTablero(tablero);

        // Lógica para decidir quién tira
        // Tira el Humano SI: Es su turno (X) O si es turno de O pero estamos en modo PvP
        if (jugadorActual == 'X' || (jugadorActual == 'O' && modoJuego == 1)) {

            // --- TURNO HUMANO ---
            do {
                cout << "Turno del Jugador " << jugadorActual << ". Elige columna (1-7): ";
                cin >> columna;
                columna--; // Ajustamos de 1-7 a 0-6

                if (columna < 0 || columna >= COLUMNAS) {
                    cout << "Columna invalida! Intentalo de nuevo." << endl;
                    fichaColocada = false;
                } else {
                    fichaColocada = introducirFicha(tablero, columna, jugadorActual);
                    if (!fichaColocada) cout << "Esa columna esta llena!" << endl;
                }
            } while (!fichaColocada);

        } else {
            // --- TURNO MÁQUINA (IA Lógica) ---
            cout << "\nLa Maquina (O) esta calculando su movimiento..." << endl;

            // Aquí la máquina usa su "cerebro" hecho con IFs y FORs
            columna = pensarJugadaMaquina(tablero, 'O', 'X');

            introducirFicha(tablero, columna, jugadorActual);
            cout << "La Maquina ha tirado en la columna " << columna + 1 << endl;
        }

        // --- COMPROBACIONES DE FINAL DE JUEGO ---
        if (comprobarVictoria(tablero, jugadorActual)) {
            dibujarTablero(tablero);
            cout << "\n***************************************" << endl;
            if (jugadorActual == 'O' && modoJuego == 2) {
                cout << "       LA MAQUINA TE HA GANADO :(" << endl;
                cout << "     (La rebelion de las maquinas ha comenzado)" << endl;
            } else {
                cout << "     FELICIDADES JUGADOR " << jugadorActual << "! HAS GANADO!" << endl;
            }
            cout << "***************************************\n" << endl;
            juegoTerminado = true;
        }
        else if (tableroLleno(tablero)) {
            dibujarTablero(tablero);
            cout << "¡EMPATE! No caben mas fichas." << endl;
            juegoTerminado = true;
        } else {
            // Cambio de turno (Operador ternario)
            jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
        }

    } while (!juegoTerminado);

    // Pausa final para que no se cierre la ventana de golpe
    cout << "Presiona Enter para salir...";
    cin.ignore(); cin.get();

    return 0;
}

// -----------------------------------------------------------------------------
// IMPLEMENTACIÓN DE FUNCIONES (El "motor" del juego)
// -----------------------------------------------------------------------------

// Función "Cerebro": Decide dónde tirar basándose en reglas lógicas
int pensarJugadaMaquina(char tablero[FILAS][COLUMNAS], char soyMaquina, char esRival) {

    // ESTRATEGIA 1: INTENTAR GANAR (Ataque)
    // Recorremos todas las columnas probando "¿Si tiro aquí, gano?"
    for (int col = 0; col < COLUMNAS; col++) {
        if (tablero[0][col] == ' ') { // Solo si cabe ficha
            // 1. Simular jugada
            introducirFicha(tablero, col, soyMaquina);
            // 2. Comprobar si esa jugada da victoria
            if (comprobarVictoria(tablero, soyMaquina)) {
                // ¡Bingo! Ganamos. Pero antes deshacemos la simulación para jugar de verdad fuera.
                // Truco: Borramos la ficha superior de esa columna
                for(int f=0; f<FILAS; f++) { if(tablero[f][col] != ' ') { tablero[f][col] = ' '; break; } }
                return col;
            }
            // 3. Deshacer simulación si no ganamos
            for(int f=0; f<FILAS; f++) { if(tablero[f][col] != ' ') { tablero[f][col] = ' '; break; } }
        }
    }

    // ESTRATEGIA 2: EVITAR PERDER (Defensa)
    // Recorremos todas las columnas probando "¿Si EL RIVAL tira aquí, gana?"
    for (int col = 0; col < COLUMNAS; col++) {
        if (tablero[0][col] == ' ') {
            // 1. Simular jugada del RIVAL
            introducirFicha(tablero, col, esRival);
            // 2. Comprobar si él ganaría
            if (comprobarVictoria(tablero, esRival)) {
                // ¡Peligro! Hay que tapar ese hueco.
                // Deshacer simulación primero
                for(int f=0; f<FILAS; f++) { if(tablero[f][col] != ' ') { tablero[f][col] = ' '; break; } }
                return col; // Devolvemos esta columna para bloquearle
            }
            // 3. Deshacer simulación
            for(int f=0; f<FILAS; f++) { if(tablero[f][col] != ' ') { tablero[f][col] = ' '; break; } }
        }
    }

    // ESTRATEGIA 3: JUGAR AL AZAR (Si no hay peligro ni victoria inmediata)
    int columnaAzar;
    do {
        columnaAzar = rand() % COLUMNAS;
    } while (tablero[0][columnaAzar] != ' '); // Repetir hasta encontrar columna libre

    return columnaAzar;
}

void mostrarTitulo() {
    cout << "   ___  _   _    ____                    " << endl;
    cout << "  /   || | | |  |  _ \\ __ _ _   _  __ _  " << endl;
    cout << " / /| || |_| |  | |_) / _` | | | |/ _` | " << endl;
    cout << "/ /_| ||  _  |  |  _ < (_| | |_| | (_| | " << endl;
    cout << "___/ |_| |_|  |_| \\_\\__,_|\\__, |\\__,_| " << endl;
    cout << "                            |___/        " << endl;
    cout << "       por Marcos de Aza                 " << endl;
    cout << "-----------------------------------------" << endl;
}

void inicializarTablero(char tablero[FILAS][COLUMNAS]) {
    for(int i = 0; i < FILAS; i++) {
        for(int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = ' ';
        }
    }
}

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

bool introducirFicha(char tablero[FILAS][COLUMNAS], int columna, char jugador) {
    // Recorremos de abajo a arriba (gravedad)
    for (int i = FILAS - 1; i >= 0; i--) {
        if (tablero[i][columna] == ' ') {
            tablero[i][columna] = jugador;
            return true;
        }
    }
    return false; // Columna llena
}

bool comprobarVictoria(char tablero[FILAS][COLUMNAS], char jugador) {
    // Horizontal
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] == jugador && tablero[i][j+1] == jugador &&
                tablero[i][j+2] == jugador && tablero[i][j+3] == jugador) return true;
        }
    }
    // Vertical
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == jugador && tablero[i+1][j] == jugador &&
                tablero[i+2][j] == jugador && tablero[i+3][j] == jugador) return true;
        }
    }
    // Diagonal Descendente
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] == jugador && tablero[i+1][j+1] == jugador &&
                tablero[i+2][j+2] == jugador && tablero[i+3][j+3] == jugador) return true;
        }
    }
    // Diagonal Ascendente
    for (int i = 3; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] == jugador && tablero[i-1][j+1] == jugador &&
                tablero[i-2][j+2] == jugador && tablero[i-3][j+3] == jugador) return true;
        }
    }
    return false;
}

bool tableroLleno(char tablero[FILAS][COLUMNAS]) {
    for(int j = 0; j < COLUMNAS; j++) {
        if (tablero[0][j] == ' ') return false;
    }
    return true;
}
