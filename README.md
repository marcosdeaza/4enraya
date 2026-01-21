# 4 en Raya - Proyecto de C++ (Evolutivo)

**Autor:** Marcos de Aza  
**Asignatura:** Fundamentos de Programación

---

## 📅 Historial de Versiones

### Versión 1.0 (27 de Noviembre): `4enraya27noviembre.cpp`
Esta fue la implementación base del proyecto entregada para la evaluación inicial. Es una versión clásica de **Jugador vs Jugador (PvP)** en el tablero estándar.

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
    * Si detecta que esa jugada provoca una victoria inmediata, la ejecuta.
    
2.  **Prioridad 2: DEFENSA (Bloquear)**
    * Si no puede ganar, simula qué haría el jugador humano en el siguiente turno.
    * Si descubre que el humano ganaría en una columna específica, la máquina coloca su ficha ahí para **bloquear**.

3.  **Prioridad 3: EXPLORACIÓN (Aleatorio)**
    * Si no hay victorias ni derrotas inminentes, utiliza `rand()` para jugar en una columna válida al azar.

---

### ⭐ Versión 3.0 (Entrega Final): `4enrayadef.cpp`

Para cerrar la asignatura, esta versión final organiza mejor el código y permite guardar los progresos, además de ampliar el tablero a uno más grande (9x9) para hacerlo más interesante.

#### 💾 Novedades: Ficheros y Estructuras
Ahora el juego es capaz de "recordar" cosas y el código está mucho más ordenado:

1.  **Uso de Structs (`struct EstadoJuego`):**
    * En las versiones anteriores tenía muchas variables sueltas por el `main` (nombres, turno, el tablero...).
    * Para esta entrega lo he metido todo en una estructura. Así puedo pasar una sola variable a las funciones y el código se entiende mucho mejor.

2.  **Guardar y Cargar Partida (`fstream`):**
    * **Guardar:** Si el usuario escribe `-1`, el juego vuelca los datos al archivo `partida_guardada.txt`.
        * *El truco de los puntos:* Tuve un problema porque al guardar el tablero con espacios vacíos, luego al leerlo el programa se saltaba los espacios. Lo solucioné haciendo que al guardar se escriban puntos `.` y al cargar se vuelvan a transformar en espacios.
    * **Historial:** He añadido un archivo `historial_partidas.txt` que nunca se borra (usando `ios::app`) para llevar un registro de todos los ganadores desde que se ejecuta el programa.

3.  **Tablero Ampliado (9x9):**
    * Aprovechando el uso de constantes, he ampliado el tablero a 9 filas y 9 columnas para que las partidas duren un poco más y la estrategia sea más importante.

---

## 📚 Bibliografía y Recursos Externos

Siguiendo los principios de honestidad académica, documento aquí qué partes he investigado por mi cuenta o dónde he necesitado ayuda para avanzar.

### 1. Investigación (Internet/StackOverflow)
Para la versión inicial, busqué cómo gestionar la matriz:

* **La gravedad de la ficha:**
    * Consulté en foros cómo hacer que la ficha cayera al fondo. La solución fue recorrer el bucle `for` a la inversa (desde abajo hacia arriba).

* **Comprobar victoria:**
    * Me basé en lógica encontrada en repositorios de GitHub para entender cómo plantear los 4 bucles (horizontal, vertical y diagonales) sin salirme de los límites del array y que no diera error de ejecución.

### 2. Uso de Apoyo (IA y Documentación)
Para la IA y la parte final de ficheros, usé herramientas para resolver dudas puntuales:

* **La Lógica de la Máquina:**
    * Le pregunté a una IA cómo hacer una "IA tonta" sin usar algoritmos complejos tipo Minimax. Me dio la idea de "simular" la jugada (poner ficha -> ver si gana -> quitar ficha), que es lo que he implementado.

* **Ficheros y Structs (Versión 3.0):**
    * **Lectura de espacios:** Busqué cómo leer caracteres individuales en un archivo de texto. Al ver que el operador `>>` se salta los espacios en blanco, se me ocurrió la idea de sustituirlos por un carácter visible (el punto) al guardar.
    * **Limpieza:** Pedí consejos sobre cómo organizar las variables globales en `structs` para que el profesor no me bajara nota por tener el `main` demasiado sucio.

---
*Este documento certifica que, aunque he consultado dudas puntuales, entiendo perfectamente todo el código presentado y soy capaz de explicar cada función.*
