# 4 en Raya - Proyecto de C++ (Evolutivo)

**Autor:** Marcos de Aza  
**Asignatura:** Fundamentos de Programación

---

## 📅 Historial del Proyecto

### Versión 1.0: Implementación Base (PvP)
Esta fue la primera versión entregada (27 de Noviembre). Se trata de una implementación clásica de **Jugador contra Jugador** en consola.

Para desarrollar la lógica del tablero, especialmente la simulación de la "gravedad" (que las fichas caigan al fondo), realicé una **investigación de código abierto**, analizando cómo otros desarrolladores resolvían la gestión de matrices en juegos de tablero.

#### 🛠️ Conceptos Aplicados:
* **Arrays Bidimensionales:** Gestión de coordenadas [fila][columna] (Tema 6).
* **Bucles Anidados:** Para la verificación de victoria (horizontal, vertical y diagonal).
* **Validación de Entradas:** Uso de `do-while` para asegurar que el usuario no introduce columnas erróneas.

### 🎄 Versión 2.0: Actualización con IA (PvE)
Durante las vacaciones, decidí ampliar el proyecto implementando un modo **Jugador vs Máquina**.

> *"¿Por qué limitarse a jugar contra otra persona cuando puedes enseñar a la máquina a jugar?"*

![Meme PvP vs IA](https://i.ibb.co/hRqL5mxQ/imagen-2026-01-17-130215675.png)

Para esta fase, utilicé herramientas de **Inteligencia Artificial Generativa** como asistente de programación. La IA me ayudó a:
1.  Optimizar la estructura de las funciones (refactorización).
2.  Diseñar el **algoritmo heurístico** de bloqueo y ataque (la "inteligencia" de la máquina).
3.  Depurar errores lógicos en los bucles de comprobación de victoria.

---

## 📚 Bibliografía y Recursos Externos

Para la realización de este proyecto, se han consultado y analizado las siguientes fuentes de información y repositorios de código abierto:

### 🔍 Investigación y Lógica Base (Gravedad y Tablero)
La lógica de caída de fichas y la estructura del tablero se basaron en el estudio de hilos de discusión y repositorios educativos:

* **StackOverflow:** *Checking Winner in connect 4 C++ Algorithm* (Fuente de inspiración para los 4 bucles de comprobación de victoria).
* **StackOverflow:** *Placing a piece in a connect four game using C++* (Referencia para la lógica de "gravedad" invertida en los arrays).
* **GitHub (Repositorios de referencia):**
    * `sharktrexer/Connect-Four-Console-App`: Análisis de estructura básica de consola.
    * `MichaelEstes/Connect-4`: Consulta sobre gestión de turnos.

### 🤖 Herramientas de Desarrollo
* **Generación de Código:** Uso de LLMs (Modelos de Lenguaje) para la generación de la lógica de la IA heurística y limpieza del código.
* **Entorno:** CLion / Visual Studio Code con compilador MinGW (G++).

---

## 🎮 Cómo Compilar y Jugar

**Para la versión clásica (PvP):**
```bash
g++ 4enraya27noviembre.cpp -o 4enRaya_Clasico
./4enRaya_Clasico
