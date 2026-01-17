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

### 🎄 Versión 2.0 (Actualización Navideña): `4enraya.cpp`

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

## 📚 Bibliografía y Declaración de Recursos Externos

Siguiendo los principios de honestidad académica e ingeniería, se documenta a continuación el origen de las soluciones lógicas implementadas, diferenciando entre desarrollo propio, investigación en repositorios y asistencia de IA.

### 1. Investigación y Referencias (StackOverflow / GitHub)
Para la mecánica base del juego (Versión 1.0), se consultaron fuentes externas para resolver la gestión de coordenadas en matrices:

* **Función `introducirFicha` (Gravedad):**
    * *Fuente:* Hilos de StackOverflow sobre *"Gravity logic in Connect 4 C++ arrays"*.
    * *Uso:* Adaptación del bucle `for` inverso (de `FILAS-1` a `0`) para lograr que la ficha "caiga" al fondo de la columna seleccionada, en lugar de quedarse arriba.

* **Función `comprobarVictoria` (Algoritmia):**
    * *Fuente:* Repositorio de referencia `KeithGalli/Connect4-Python` (adaptado a C++).
    * *Uso:* Implementación de los 4 bucles anidados independientes para verificar: Horizontal, Vertical, Diagonal Positiva y Diagonal Negativa. Se ajustaron los límites de los bucles (`COLUMNAS - 3`) para evitar errores de desbordamiento de memoria (*Segmentation Fault*).

### 2. Uso de Asistentes de IA (Claude AI / LLMs)
Para el desarrollo de la **Versión 2.0 (PvE)**, se utilizó Inteligencia Artificial Generativa como herramienta de soporte (*Pair Programming*) para los siguientes módulos específicos:

* **Función `pensarJugadaMaquina` (Heurística):**
    * *Consultas realizadas:* "Cómo hacer una IA simple para 3 en raya sin Minimax" y "Simular movimientos en arrays C++".
    * *Implementación:* La IA sugirió la estructura lógica de **Simulación -> Verificación -> Retroceso** (Undo), que permite a la máquina poner una ficha temporalmente, ver si gana, y borrarla inmediatamente para restaurar el tablero.

* **Limpieza y Refactorización:**
    * Se utilizó el asistente para limpiar la indentación del código y optimizar los nombres de las variables, asegurando que el estilo cumpliera con los estándares de legibilidad de la asignatura (Clean Code).

---
*Este documento certifica que, aunque se han utilizado herramientas de apoyo e investigación, la comprensión y defensa de todo el código presentado corresponde al autor del proyecto.*
