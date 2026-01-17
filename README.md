# PROYECTO FINAL: MOTOR LÓGICO DE "CONECTA 4" EN C++

**Asignatura:** Fundamentos de Programación  
**Autor:** Marcos de Aza  
**Curso Académico:** 2025-2026  
**Lenguaje:** C++ (ISO Standard)

---

## 1. RESUMEN EJECUTIVO
Este proyecto consiste en el diseño, implementación y documentación de una aplicación de software que simula el juego de mesa "Conecta 4". El sistema permite dos modalidades de ejecución: **Jugador vs Jugador (PvP)** y **Jugador vs Entorno (PvE)**, implementando en esta última un algoritmo heurístico de toma de decisiones.

El desarrollo se ha regido estrictamente por los paradigmas de la **Programación Estructurada** y **Modular**, cumpliendo con los requisitos académicos establecidos en el plan de estudios.

---

## 2. ARQUITECTURA DEL SOFTWARE

El código sigue una arquitectura monolítica modular, dividida en capas lógicas de procesamiento.

### 2.1. Estructuras de Datos (Tema 6)
La representación del estado del juego se basa en **Arrays Multidimensionales** estáticos.
- **Matriz:** `char tablero[6][7]`.
- **Justificación:** Se opta por memoria estática (Stack) frente a dinámica (Heap) debido a que las dimensiones del tablero son constantes e invariables durante la ejecución, optimizando así el acceso a memoria.

### 2.2. Control de Flujo y Algoritmia (Tema 5)
El motor del juego utiliza estructuras de control iterativas anidadas para:
1.  **Recorrido Matricial:** Búsqueda de patrones de victoria (Horizontal, Vertical, Diagonal).
2.  **Gestión de Turnos:** Bucle `do-while` principal que garantiza la persistencia del estado hasta la condición de parada (Victoria o Empate).

### 2.3. Modularidad (Tema 7)
Se aplica el principio de *Divide y Vencerás*. El `main` actúa únicamente como orquestador, delegando la lógica en funciones especializadas:
* `introducirFicha()`: Gestiona la lógica de gravedad inversa (llenado de abajo a arriba).
* `comprobarVictoria()`: Algoritmo de verificación de patrones.
* `pensarJugadaMaquina()`: Motor de decisión de la IA.

---

## 3. CRONOLOGÍA Y EVOLUCIÓN DEL DESARROLLO

El proyecto se ha desarrollado en dos fases incrementales, siguiendo un modelo de ciclo de vida evolutivo.

### Fase 1: Motor Base PvP (27 Noviembre)
**Objetivo:** Implementación de la lógica fundamental y gestión de memoria.
* **Hito:** Validación de la lógica de "gravedad" en la matriz y detección de 4 en línea.
* **Estado:** Funcional y validado. (Ver `4enraya27noviembre.cpp`).

### Fase 2: Implementación de Agente Inteligente (Periodo Vacacional)
**Objetivo:** Desarrollo de un algoritmo capaz de competir contra el usuario.
* **Desafío:** Crear un comportamiento "inteligente" sin utilizar librerías externas ni redes neuronales, limitándose a las estructuras de control vistas en clase.
* **Solución:** Algoritmo Heurístico de Bloqueo y Ataque.

> *Esquema conceptual de la evolución del módulo de IA:*
> ![Evolución IA](https://i.ibb.co/hRqL5mxQ/imagen-2026-01-17-130215675.png)

---

## 4. METODOLOGÍA Y RECURSOS TÉCNICOS

Para garantizar la robustez del código y aplicar las mejores prácticas de la industria, se ha seguido una metodología de **Investigación y Desarrollo (I+D)** apoyada en las siguientes fuentes:

### 4.1. Ingeniería Inversa y Análisis de Código
Para resolver la lógica de detección de victoria en diagonales (la parte más compleja algorítmicamente), se analizaron soluciones de código abierto en repositorios de referencia.
* **Algoritmo de Victoria:** Adaptado de discusiones técnicas en *StackOverflow* sobre optimización de recorridos en matrices C++.
* **Lógica de Gravedad:** Basada en el análisis del repositorio `Connect-4-Console` de GitHub, adaptando la lógica de punteros a índices de arrays para cumplir con el temario.

### 4.2. Uso de Asistentes de IA Generativa
Se utilizaron Modelos de Lenguaje (LLMs) como herramienta de soporte al desarrollo (Pair Programming) para:
1.  **Refactorización:** Limpieza de código redundante y optimización de sintaxis.
2.  **Generación de Escenarios:** La IA sugirió la lógica de "Simulación - Evaluación - Retroceso" usada en la función `pensarJugadaMaquina()`, permitiendo predecir movimientos sin alterar el estado real del tablero.

---

## 5. MANUAL DE COMPILACIÓN

El proyecto no requiere dependencias externas (makefiles o librerías dinámicas). Se compila utilizando el estándar GNU C++.

**Compilación del Proyecto Final (con IA):**
```bash
g++ -o 4enRaya_Final 4enraya_IA.cpp
./4enRaya_Final
