#include <iostream>
#include <fstream>  // Para manejar ficheros (guardar/cargar)
#include <string>   // Para textos
#include <cstdlib>  // Para rand() y system()
#include <ctime>    // Para la semilla aleatoria

using namespace std;

// --- CONSTANTES ---
// CAMBIO AQUÍ: Ahora es 9x9
const int FILAS = 9;
const int COLUMNAS = 9;
const string ARCHIVO_GUARDADO = "partida_guardada.txt";
const string ARCHIVO_HISTORIAL = "historial_partidas.txt";

// --- ESTRUCTURAS ---

// Estructura para la configuración de las fichas
struct Configuracion {
    char fichaJ1;
    char fichaJ2;
};

// Estructura principal que guarda todo el estado de la partida
struct EstadoJuego {
    char tablero[FILAS][COLUMNAS];
    string nombreJ1;
    string nombreJ2;
    int turno; // 1 para Jugador 1, 2 para Jugador 2
    int modo;  // 1 = PvP, 2 = PvE (contra máquina)
    int nJugadas;
    bool partidaActiva; // Para saber si seguimos jugando
};

// --- PROTOTIPOS DE FUNCIONES ---
void limpiarPantalla();
void mostrarMenuPrincipal();
void menuConfiguracion(Configuracion &config);
void verInstrucciones();
void verHistorial();

// Funciones del juego
void nuevaPartida(EstadoJuego &juego, Configuracion config);
void bucleJuego(EstadoJuego &juego, Configuracion config);
void inicializarTablero(EstadoJuego &juego);
void dibujarTablero(EstadoJuego juego, Configuracion config);
bool colocarFicha(EstadoJuego &juego, int columna, char ficha);
bool comprobarVictoria(EstadoJuego juego, char ficha);
bool tableroLleno(EstadoJuego juego);
int movimientoMaquina(EstadoJuego juego, char fichaIA, char fichaRival);

// Funciones para gestión de archivos
void guardarPartida(EstadoJuego juego);
bool cargarPartida(EstadoJuego &juego);
void guardarEnHistorial(EstadoJuego juego, string ganador);

// --------------------------------------------------------------------------------
// FUNCIÓN PRINCIPAL (MAIN)
// --------------------------------------------------------------------------------
int main() {
    srand(time(NULL)); // Inicializar semilla aleatoria
    Configuracion miConfig = {'X', 'O'}; // Fichas por defecto
    EstadoJuego juegoActual;
    int opcion;

    do {
        limpiarPantalla();
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
            case 1: // Iniciar nueva partida
                nuevaPartida(juegoActual, miConfig);
                break;
            case 2: // Cargar una partida anterior
                if (cargarPartida(juegoActual)) {
                    cout << "\n[!] Partida cargada correctamente." << endl;
                    cout << "Presiona ENTER para continuar...";
                    cin.ignore(); cin.get();
                    bucleJuego(juegoActual, miConfig);
                } else {
                    cout << "\n[!] No se encontró ninguna partida guardada." << endl;
                    cout << "Presiona ENTER para volver.";
                    cin.ignore(); cin.get();
                }
                break;
            case 3: // Ver historial de ganadores
                verHistorial();
                break;
            case 4: // Configuración
                menuConfiguracion(miConfig);
                break;
            case 0: // Salir
                cout << "¡Hasta la proxima!" << endl;
                break;
            default:
                cout << "Opción no válida." << endl;
        }
    } while (opcion != 0);

    return 0;
}

// --------------------------------------------------------------------------------
// MENÚS Y NAVEGACIÓN
// --------------------------------------------------------------------------------

void mostrarMenuPrincipal() {
    cout << "========================================" << endl;
    cout << "       CUATRO EN RAYA (EDICION 9x9)     " << endl;
    cout << "========================================" << endl;
    cout << "1. Nueva Partida" << endl;
    cout << "2. Cargar Partida Guardada" << endl;
    cout << "3. Ver Historial de Partidas" << endl;
    cout << "4. Configuracion e Instrucciones" << endl;
    cout << "0. Salir" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Selecciona una opcion: ";
}

void menuConfiguracion(Configuracion &config) {
    int op;
    do {
        limpiarPantalla();
        cout << "--- CONFIGURACION ---" << endl;
        cout << "1. Ver Instrucciones de juego" << endl;
        cout << "2. Cambiar ficha Jugador 1 (Actual: " << config.fichaJ1 << ")" << endl;
        cout << "3. Cambiar ficha Jugador 2 (Actual: " << config.fichaJ2 << ")" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Elige: ";
        cin >> op;

        if (op == 1) verInstrucciones();
        else if (op == 2) {
            cout << "Introduce el nuevo caracter para J1: ";
            cin >> config.fichaJ1;
        }
        else if (op == 3) {
            cout << "Introduce el nuevo caracter para J2: ";
            cin >> config.fichaJ2;
        }

    } while (op != 0);
}

void verInstrucciones() {
    limpiarPantalla();
    cout << "--- INSTRUCCIONES ---" << endl;
    cout << "1. El objetivo es conectar 4 fichas del mismo tipo." << endl;
    cout << "   (Horizontal, Vertical o Diagonal)." << endl;
    cout << "2. Se juega por turnos. Elige columna del 1 al 9." << endl;
    cout << "3. Si quieres GUARDAR y salir, escribe '-1' en tu turno." << endl;
    cout << "\nPresiona ENTER para volver...";
    cin.ignore(); cin.get();
}

// --------------------------------------------------------------------------------
// LÓGICA DEL JUEGO
// --------------------------------------------------------------------------------

void nuevaPartida(EstadoJuego &juego, Configuracion config) {
    limpiarPantalla();
    cout << "--- NUEVA PARTIDA ---" << endl;
    cout << "1. Jugador vs Jugador" << endl;
    cout << "2. Jugador vs Maquina" << endl;
    cout << "Elige modo de juego: ";
    cin >> juego.modo;

    cin.ignore(); // Limpiar el buffer antes de leer strings con espacios
    cout << "Nombre Jugador 1: ";
    getline(cin, juego.nombreJ1);

    if (juego.modo == 1) {
        cout << "Nombre Jugador 2: ";
        getline(cin, juego.nombreJ2);
    } else {
        juego.nombreJ2 = "CPU";
        juego.modo = 2; // Aseguramos el modo por si el usuario puso algo raro
    }

    inicializarTablero(juego);
    juego.turno = 1; // Siempre empieza el jugador 1
    juego.nJugadas = 0;
    juego.partidaActiva = true;

    bucleJuego(juego, config);
}

void inicializarTablero(EstadoJuego &juego) {
    for(int i=0; i<FILAS; i++)
        for(int j=0; j<COLUMNAS; j++)
            juego.tablero[i][j] = ' '; // Rellenamos con espacios
}

void dibujarTablero(EstadoJuego juego, Configuracion config) {
    limpiarPantalla();
    cout << "\nTurno de: " << (juego.turno == 1 ? juego.nombreJ1 : juego.nombreJ2) << endl;
    cout << "Fichas: " << config.fichaJ1 << " vs " << config.fichaJ2 << endl;
    cout << "\n";
    
    // CAMBIO AQUÍ: Cabecera con números del 1 al 9
    cout << "  1   2   3   4   5   6   7   8   9" << endl;
    cout << "+---+---+---+---+---+---+---+---+---+" << endl;
    
    for(int i=0; i<FILAS; i++) {
        cout << "|";
        for(int j=0; j<COLUMNAS; j++) {
            char fichaMostrar = ' ';
            // Mostramos la ficha personalizada según la configuración
            if (juego.tablero[i][j] == 'X') fichaMostrar = config.fichaJ1;
            else if (juego.tablero[i][j] == 'O') fichaMostrar = config.fichaJ2;
            
            cout << " " << fichaMostrar << " |";
        }
        cout << endl;
        cout << "+---+---+---+---+---+---+---+---+---+" << endl;
    }
    cout << "Columna (1-9) o '-1' para Guardar: ";
}

// Bucle principal donde ocurre la partida
void bucleJuego(EstadoJuego &juego, Configuracion config) {
    int col;
    char fichaActual;

    while (juego.partidaActiva) {
        // Asignamos la ficha interna ('X' o 'O') según el turno
        fichaActual = (juego.turno == 1) ? 'X' : 'O';
        
        dibujarTablero(juego, config);

        // Turno de la Máquina o del Humano
        if (juego.modo == 2 && juego.turno == 2) {
            cout << "La maquina esta pensando..." << endl;
            col = movimientoMaquina(juego, 'O', 'X'); 
        } else {
            cin >> col;
            
            // Si el usuario introduce -1, guardamos y salimos
            if (col == -1) {
                guardarPartida(juego);
                juego.partidaActiva = false;
                return;
            }
            col--; // Ajustamos el número visual (1-9) al índice del array (0-8)
        }

        // Validamos si la columna es correcta y tiene espacio
        if (col >= 0 && col < COLUMNAS) {
            if (colocarFicha(juego, col, fichaActual)) {
                juego.nJugadas++;
                
                // 1. Comprobar Victoria
                if (comprobarVictoria(juego, fichaActual)) {
                    dibujarTablero(juego, config);
                    string ganador = (juego.turno == 1) ? juego.nombreJ1 : juego.nombreJ2;
                    cout << "\n*** VICTORIA DE " << ganador << " ***" << endl;
                    
                    guardarEnHistorial(juego, ganador);
                    juego.partidaActiva = false;
                    
                    cout << "Presiona ENTER para volver al menu...";
                    cin.ignore(); cin.get();
                } 
                // 2. Comprobar Empate
                else if (tableroLleno(juego)) {
                    dibujarTablero(juego, config);
                    cout << "\n*** EMPATE (TABLERO LLENO) ***" << endl;
                    guardarEnHistorial(juego, "EMPATE");
                    juego.partidaActiva = false;
                    
                    cout << "Presiona ENTER para volver al menu...";
                    cin.ignore(); cin.get();
                } 
                // 3. Continuar partida
                else {
                    // Cambio de turno (1->2 o 2->1)
                    juego.turno = (juego.turno == 1) ? 2 : 1;
                }
            } else {
                if (juego.modo == 1 || juego.turno == 1) {
                    cout << "Esa columna esta llena. Elige otra." << endl;
                    cin.ignore(); cin.get();
                }
            }
        } else {
            cout << "Numero de columna no valido." << endl;
            cin.ignore(); cin.get();
        }
    }
}

// Simula la gravedad: busca la posición libre más baja
bool colocarFicha(EstadoJuego &juego, int columna, char ficha) {
    for (int i = FILAS - 1; i >= 0; i--) {
        if (juego.tablero[i][columna] == ' ') {
            juego.tablero[i][columna] = ficha;
            return true;
        }
    }
    return false; // Columna llena
}

// --------------------------------------------------------------------------------
// MANEJO DE FICHEROS (GUARDAR Y CARGAR)
// --------------------------------------------------------------------------------

void guardarPartida(EstadoJuego juego) {
    ofstream archivo;
    archivo.open(ARCHIVO_GUARDADO.c_str());

    if (archivo.fail()) {
        cout << "Error: No se pudo crear el archivo." << endl;
        return;
    }

    // Guardamos las variables esenciales
    archivo << juego.modo << endl;
    archivo << juego.nombreJ1 << endl;
    archivo << juego.nombreJ2 << endl;
    archivo << juego.turno << endl;
    archivo << juego.nJugadas << endl;

    // Guardamos el tablero. Usamos '.' para representar espacios vacíos
    // para facilitar la lectura posterior
    for(int i=0; i<FILAS; i++) {
        for(int j=0; j<COLUMNAS; j++) {
            if (juego.tablero[i][j] == ' ') archivo << '.';
            else archivo << juego.tablero[i][j];
        }
        archivo << endl;
    }

    archivo.close();
    cout << "Partida guardada en '" << ARCHIVO_GUARDADO << "'." << endl;
    cout << "Presiona ENTER para salir...";
    cin.ignore(); cin.get();
}

bool cargarPartida(EstadoJuego &juego) {
    ifstream archivo;
    archivo.open(ARCHIVO_GUARDADO.c_str());

    if (archivo.fail()) return false; // El archivo no existe

    // Leemos en el mismo orden que guardamos
    archivo >> juego.modo;
    archivo.ignore(); // Saltamos el salto de línea del buffer
    getline(archivo, juego.nombreJ1);
    getline(archivo, juego.nombreJ2);
    archivo >> juego.turno;
    archivo >> juego.nJugadas;

    // Recuperamos el tablero transformando puntos '.' en espacios ' '
    char celda;
    for(int i=0; i<FILAS; i++) {
        for(int j=0; j<COLUMNAS; j++) {
            archivo >> celda;
            if (celda == '.') juego.tablero[i][j] = ' ';
            else juego.tablero[i][j] = celda;
        }
    }

    juego.partidaActiva = true;
    archivo.close();
    return true;
}

void guardarEnHistorial(EstadoJuego juego, string ganador) {
    ofstream archivo;
    // ios::app permite añadir texto al final sin borrar lo anterior
    archivo.open(ARCHIVO_HISTORIAL.c_str(), ios::app); 

    if (!archivo.fail()) {
        archivo << "--------------------------------------------" << endl;
        archivo << "Jugadores: " << juego.nombreJ1 << " vs " << juego.nombreJ2 << endl;
        archivo << "Ganador: " << ganador << endl;
        archivo << "Movimientos totales: " << juego.nJugadas << endl;
        archivo << "Tablero Final:" << endl;
        for(int i=0; i<FILAS; i++) {
            archivo << "|";
            for(int j=0; j<COLUMNAS; j++) {
                 archivo << (juego.tablero[i][j] == ' ' ? ' ' : juego.tablero[i][j]);
            }
            archivo << "|" << endl;
        }
        archivo << "--------------------------------------------" << endl;
    }
    archivo.close();
}

void verHistorial() {
    ifstream archivo;
    archivo.open(ARCHIVO_HISTORIAL.c_str());
    string linea;

    limpiarPantalla();
    cout << "--- HISTORIAL DE PARTIDAS ---" << endl;

    if (archivo.fail()) {
        cout << "Aun no hay partidas registradas." << endl;
    } else {
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
    }
    archivo.close();
    
    cout << "\nPresiona ENTER para volver...";
    cin.ignore(); cin.get();
}

// --------------------------------------------------------------------------------
// UTILIDADES Y COMPROBACIONES
// --------------------------------------------------------------------------------

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

bool comprobarVictoria(EstadoJuego juego, char ficha) {
    // 1. Horizontal
    for (int i=0; i<FILAS; i++)
        for (int j=0; j<COLUMNAS-3; j++)
            if (juego.tablero[i][j] == ficha && juego.tablero[i][j+1] == ficha && 
                juego.tablero[i][j+2] == ficha && juego.tablero[i][j+3] == ficha) return true;

    // 2. Vertical
    for (int i=0; i<FILAS-3; i++)
        for (int j=0; j<COLUMNAS; j++)
            if (juego.tablero[i][j] == ficha && juego.tablero[i+1][j] == ficha &&
                juego.tablero[i+2][j] == ficha && juego.tablero[i+3][j] == ficha) return true;

    // 3. Diagonal Descendente
    for (int i=0; i<FILAS-3; i++)
        for (int j=0; j<COLUMNAS-3; j++)
            if (juego.tablero[i][j] == ficha && juego.tablero[i+1][j+1] == ficha &&
                juego.tablero[i+2][j+2] == ficha && juego.tablero[i+3][j+3] == ficha) return true;

    // 4. Diagonal Ascendente
    for (int i=3; i<FILAS; i++)
        for (int j=0; j<COLUMNAS-3; j++)
            if (juego.tablero[i][j] == ficha && juego.tablero[i-1][j+1] == ficha &&
                juego.tablero[i-2][j+2] == ficha && juego.tablero[i-3][j+3] == ficha) return true;

    return false;
}

bool tableroLleno(EstadoJuego juego) {
    for (int j=0; j<COLUMNAS; j++)
        if (juego.tablero[0][j] == ' ') return false;
    return true;
}

int movimientoMaquina(EstadoJuego juego, char fichaIA, char fichaRival) {
    // 1. Intentar ganar
    for(int c=0; c<COLUMNAS; c++) {
        EstadoJuego copia = juego;
        if(colocarFicha(copia, c, fichaIA)) {
            if(comprobarVictoria(copia, fichaIA)) return c;
        }
    }
    // 2. Bloquear al rival
    for(int c=0; c<COLUMNAS; c++) {
        EstadoJuego copia = juego;
        if(colocarFicha(copia, c, fichaRival)) {
            if(comprobarVictoria(copia, fichaRival)) return c;
        }
    }
    // 3. Movimiento aleatorio
    int c;
    do {
        c = rand() % COLUMNAS;
    } while (juego.tablero[0][c] != ' ');
    return c;
}