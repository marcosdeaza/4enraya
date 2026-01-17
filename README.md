# 4 en Raya - Proyecto de C++

**Autor:** Marcos de Aza  
**Asignatura:** Fundamentos de Programación

## 📖 Descripción
Este proyecto es una implementación del clásico juego de mesa **"Conecta 4"** (4 en Raya) desarrollado en C++ para consola. El objetivo es alinear cuatro fichas del mismo tipo (horizontales, verticales o diagonales) antes que el oponente.

El código ha sido estructurado siguiendo los principios de la **programación modular** y **estructurada** vistos en clase.

## 🛠️ Conceptos de Clase Aplicados

Este proyecto pone en práctica los conocimientos adquiridos en los siguientes temas:

### 1. Programación Modular (Tema 7)
Se ha evitado escribir todo el código en el `main`. [cite_start]En su lugar, se ha dividido el problema en subproblemas más pequeños y manejables[cite: 2587].
- [cite_start]**Uso de Prototipos:** Se definen las cabeceras de las funciones antes del `main` para informar al compilador[cite: 2781].
- **Funciones Específicas:**
  - [cite_start]`dibujarTablero()`: Procedimiento (`void`) que se encarga de la salida por pantalla[cite: 2732].
  - [cite_start]`comprobarVictoria()`: Función que devuelve un valor booleano (`true` o `false`) indicando si alguien ganó[cite: 2662].
- [cite_start]**Paso de Parámetros:** Se pasan arrays como argumentos a las funciones para operar sobre el tablero[cite: 2873, 2986].

### 2. Datos Estructurados: Arrays Multidimensionales (Tema 6)
[cite_start]El tablero de juego no es una lista simple, sino una **Matriz** (Array Bidimensional) de 6 filas por 7 columnas[cite: 198].
- **Declaración:** `char tablero[FILAS][COLUMNAS];`
- [cite_start]**Acceso:** Se utilizan dos índices (fila y columna) para localizar cada celda, tal como se requiere para estructuras tipo tabla[cite: 200].

### 3. Estructuras de Control (Tema 5)
El flujo del juego se controla mediante diversas estructuras lógicas:
- [cite_start]**Bucle `do-while`:** Se utiliza para el turno del jugador y la validación de la columna, garantizando que el código se ejecute al menos una vez (pedir ficha) hasta que la entrada sea válida[cite: 2334].
- [cite_start]**Bucles `for` anidados:** Esenciales para recorrer la matriz completa (dibujar tablero, buscar victorias)[cite: 276].
- [cite_start]**Condicionales `if-else`:** Para verificar límites del tablero, columnas llenas y cambios de turno[cite: 2018].

### 4. Tipos de Datos y Constantes (Tema 4)
- [cite_start]**Constantes:** Se definen `FILAS` y `COLUMNAS` como `const int` para evitar "números mágicos" y facilitar el mantenimiento, tal como se recomienda en lugar de usar valores estáticos[cite: 560].
- [cite_start]**Booleanos:** Uso de variables `bool` (`juegoTerminado`, `fichaColocada`) para controlar los estados lógicos del programa (verdadero/falso)[cite: 650].

```bash
g++ 4enRaya.cpp -o 4enRaya
./4enRaya
