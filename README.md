# 4 en Raya - Proyecto de C++ (Evolutivo)

**Autor:** Marcos de Aza  
**Asignatura:** Fundamentos de Programación

---

## 📅 Historial de Versiones

### Versión 1.0 (27 de Noviembre): `4enraya27noviembre.cpp`
Esta fue la implementación base del proyecto entregada para la evaluación inicial. Es una versión clásica de **Jugador vs Jugador (PvP)**.

#### 🛠️ Conceptos de Clase Aplicados (Versión Base)
El código se estructuró siguiendo los principios fundamentales vistos en clase:

1.  **Programación Modular (Tema 7):**
    * Uso estricto de funciones y prototipos para dividir el problema.
    * Pasos de parámetros (arrays por referencia) para manipular el tablero.
2.  **Datos Estructurados (Tema 6):**
    * Uso de **Matrices** (`char tablero[FILAS][COLUMNAS]`) para representar el juego.
3.  **Estructuras de Control (Tema 5):**
    * Bucles `do-while` para validar la entrada del usuario.
    * Bucles `for` anidados para la lógica de verificación de victoria.
4.  **Tipos de Datos (Tema 4):**
    * Uso de `const int` para evitar números mágicos en el tamaño del tablero.

---

### 🎄 Versión 2.0 (Actualización Navideña): `4enraya_IA.cpp`

Para mejorar el proyecto durante las vacaciones, me planteé el reto de poder jugar solo contra la máquina.

> *"¿Por qué limitarse a jugar contra otra persona cuando puedes enseñar a la máquina a jugar?"*

![Meme PvP vs IA](https://i.ibb.co/hRqL5mxQ/imagen-2026-01-17-130215675.png)

#### 🚀 Novedades: Inteligencia Artificial Heurística
En lugar de conectar una API externa (que requeriría librerías no vistas en clase), he desarrollado un **Algoritmo Lógico** basado puramente en los conceptos de la asignatura.

**¿Cómo piensa la Máquina?**
La función `pensarJugadaMaquina()` utiliza "simulaciones" mediante bucles y condicionales:

1.  **Prioridad 1: ATAQUE (Ganar)**
    * La máquina recorre el array del tablero "imaginando" que pone su ficha en cada columna.
    * Si detecta que esa jugada provoca una victoria inmediata (llamando a `comprobarVictoria`), la ejecuta.
    
2.  **Prioridad 2: DEFENSA (Bloquear)**
    * Si no puede ganar, simula qué haría el jugador humano en el siguiente turno.
    * Si descubre que el humano ganaría en una columna específica, la máquina coloca su ficha ahí para **bloquear**.

3.  **Prioridad 3: EXPLORACIÓN (Aleatorio)**
    * Si no hay victorias ni derrotas inminentes, utiliza `rand()` (librería `cstdlib`) para jugar en una columna válida al azar, haciendo el juego impredecible.

---

## 🎮 Cómo Compilar y Jugar

Puedes compilar cualquiera de las dos versiones con `g++`:

**Para la versión clásica:**
```bash
g++ 4enraya27noviembre.cpp -o 4enRaya_Clasico
./4enRaya_Clasico
