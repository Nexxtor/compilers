# Parser LL(1) Personalizado en C

## 📋 Descripción

Implementación completamente manual de un analizador léxico y parser LL(1) en **lenguaje C puro** sin usar herramientas externas. Esta implementación demuestra los conceptos fundamentales del análisis sintáctico para la siguiente gramática:

```
E  -> T E'
E' -> + T E' | ε
T  -> F T'
T' -> * F T' | ε
F  -> ( E ) | ident
```

## 🛠️ Herramientas Requeridas

- **gcc**: Compilador C (estándar C99 o superior)

### Instalación en macOS:
```bash
xcode-select --install  # Instala gcc
```

### Instalación en Ubuntu/Debian:
```bash
sudo apt-get install gcc
```

## 📁 Estructura de Archivos

```
02-parser_custom/
├── main.c            # Programa principal
├── lexer.h           # Cabecera del analizador léxico
├── lexer.c           # Implementación del analizador léxico
├── parser.h          # Cabecera del parser LL(1)
├── parser.c          # Implementación del parser LL(1)
├── Makefile          # Archivo de construcción
├── test_input.txt    # Casos de prueba válidos
├── test_errores.txt  # Casos de prueba con errores
├── ejemplos.txt      # Ejemplos de uso
└── README.md         # Esta documentación
```

## 🚀 Compilación y Ejecución

### Compilar el proyecto:
```bash
make all
```

### Modos de ejecución:

#### 1. Modo interactivo:
```bash
make run
# o directamente:
./parser
```

#### 2. Procesar archivo:
```bash
./parser test_input.txt
```

#### 3. Expresión directa:
```bash
./parser -e "a + b * c"
```

### Ejecutar pruebas:
```bash
make test           # Casos válidos
make test-errors    # Casos con errores
make test-all       # Todas las pruebas
make test-expr      # Probar expresión específica
```

### Compilación en modo debug:
```bash
make debug
```

### Limpiar archivos generados:
```bash
make clean
```

## 📝 Ejemplos de Uso

### Modo Interactivo:
```
$ ./parser
=== PARSER LL(1) PERSONALIZADO EN C ===
Gramática implementada:
E  -> T E'
E' -> + T E' | ε
T  -> F T'
T' -> * F T' | ε
F  -> ( E ) | ident

Modo interactivo - Ingrese expresiones (escriba 'salir' para terminar):

>>> a + b * c
🔍 Analizando: a + b * c
----------------------------------------
✅ ANÁLISIS SINTÁCTICO EXITOSO
Árbol de análisis sintáctico:
+
  ID: a
  *
    ID: b
    ID: c
----------------------------------------

>>> salir
¡Hasta luego!
```

### Procesamiento de Archivo:
```bash
$ ./parser test_input.txt
📁 Procesando archivo: test_input.txt
========================================

Línea 4: 🔍 Analizando: a
----------------------------------------
✅ ANÁLISIS SINTÁCTICO EXITOSO
Árbol de análisis sintáctico:
ID: a
----------------------------------------
```

### Expresión Directa:
```bash
$ ./parser -e "(a + b) * c"
🔍 Analizando: (a + b) * c
----------------------------------------
✅ ANÁLISIS SINTÁCTICO EXITOSO
Árbol de análisis sintáctico:
*
  ()
    +
      ID: a
      ID: b
  ID: c
----------------------------------------
```

## 🔧 Arquitectura del Sistema

### 1. Analizador Léxico (lexer.c/lexer.h)

#### Características:
- ✅ **Tokenización manual**: Reconocimiento carácter por carácter
- ✅ **Gestión de memoria**: Asignación y liberación automática
- ✅ **Seguimiento de posición**: Línea y columna para cada token
- ✅ **Manejo de errores**: Detección de caracteres no válidos
- ✅ **Tokens soportados**: Identificadores, operadores, paréntesis

#### Tokens Reconocidos:
```c
typedef enum {
    TOKEN_IDENTIFICADOR,     // [a-zA-Z][a-zA-Z0-9_]*
    TOKEN_SUMA,              // +
    TOKEN_MULTIPLICACION,    // *
    TOKEN_PAREN_IZQ,         // (
    TOKEN_PAREN_DER,         // )
    TOKEN_EOF,               // Fin de entrada
    TOKEN_ERROR              // Error léxico
} TipoToken;
```

### 2. Analizador Sintáctico (parser.c/parser.h)

#### Características:
- ✅ **Parser LL(1)**: Análisis descendente recursivo
- ✅ **Construcción de AST**: Árbol de sintaxis abstracta
- ✅ **Manejo de precedencia**: Operadores con precedencia correcta
- ✅ **Detección de errores**: Mensajes detallados con posición
- ✅ **Recuperación de errores**: Manejo robusto de errores sintácticos

#### Funciones de Análisis:
```c
NodoArbol* analizar_E(Parser *parser);        // E -> T E'
NodoArbol* analizar_E_prima(Parser *parser);  // E' -> + T E' | ε
NodoArbol* analizar_T(Parser *parser);        // T -> F T'
NodoArbol* analizar_T_prima(Parser *parser);  // T' -> * F T' | ε
NodoArbol* analizar_F(Parser *parser);        // F -> ( E ) | ident
```

### 3. Árbol Sintáctico

#### Tipos de Nodos:
```c
typedef enum {
    NODO_EXPRESION,
    NODO_TERMINO,
    NODO_FACTOR,
    NODO_IDENTIFICADOR,
    NODO_SUMA,
    NODO_MULTIPLICACION,
    NODO_PARENTESIS
} TipoNodo;
```

#### Estructura del Nodo:
```c
typedef struct NodoArbol {
    TipoNodo tipo;
    char *valor;
    struct NodoArbol *izquierdo;
    struct NodoArbol *derecho;
    int linea;
    int columna;
} NodoArbol;
```

## 🧪 Casos de Prueba

### Casos Válidos (test_input.txt):
- ✅ Identificadores simples: `a`, `variable`, `x1`
- ✅ Operaciones básicas: `a + b`, `a * b`
- ✅ Precedencia: `a + b * c`
- ✅ Paréntesis: `(a + b) * c`
- ✅ Expresiones complejas: `(a + b) * (c + d)`

### Casos con Errores (test_errores.txt):
- ❌ Caracteres no válidos: `a @ b`, `x # y`
- ❌ Operadores sin operandos: `+`, `a +`, `+ a`
- ❌ Paréntesis desbalanceados: `(a`, `a)`
- ❌ Secuencias inválidas: `a b`, `a + + b`

## 📊 Análisis de Precedencia

### Tabla de Precedencia:
| Operador | Precedencia | Asociatividad | Implementación |
|----------|-------------|---------------|----------------|
| `()`     | Máxima      | N/A           | `analizar_F()` |
| `*`      | Alta        | Izquierda     | `analizar_T_prima()` |
| `+`      | Baja        | Izquierda     | `analizar_E_prima()` |

### Ejemplos de Precedencia:
```
a + b * c    →    a + (b * c)
(a + b) * c  →    (a + b) * c
a * b + c    →    (a * b) + c
```

## 🔍 Manejo de Errores

### Tipos de Errores Detectados:

#### 1. Errores Léxicos:
```
Error léxico: Carácter no reconocido '@' en línea 1, columna 3
```

#### 2. Errores Sintácticos:
```
Error sintáctico en línea 1, columna 5: Se esperaba ')'. Token encontrado: EOF
```

#### 3. Errores de Secuencia:
```
Error sintáctico en línea 1, columna 3: Se esperaba identificador o '('. Token encontrado: SUMA
```

## 💡 Características Avanzadas

### 1. Gestión de Memoria:
- ✅ **Liberación automática**: Todos los recursos se liberan correctamente
- ✅ **Detección de fugas**: Verificación de asignaciones de memoria
- ✅ **Manejo de errores**: Liberación en casos de error

### 2. Múltiples Modos de Entrada:
- ✅ **Interactivo**: Entrada línea por línea
- ✅ **Archivo**: Procesamiento de archivos de prueba
- ✅ **Directo**: Análisis de expresiones desde línea de comandos

### 3. Información de Debug:
- ✅ **Posición exacta**: Línea y columna para cada elemento
- ✅ **Trazado de análisis**: Seguimiento del proceso de parsing
- ✅ **Árbol visual**: Representación gráfica del AST

## 🔧 Compilación Avanzada

### Opciones del Makefile:
```bash
make all          # Compilación estándar
make debug        # Compilación con símbolos de debug
make clean        # Limpiar archivos generados
make info         # Información del proyecto
make help         # Ayuda completa
```

### Flags de Compilación:
```makefile
CFLAGS = -Wall -Wextra -std=c99 -g -O2
```

## 🚀 Ventajas de la Implementación Manual

### Ventajas:
- ✅ **Control total**: Manejo completo del proceso de análisis
- ✅ **Comprensión profunda**: Entendimiento de los algoritmos
- ✅ **Personalización**: Fácil modificación y extensión
- ✅ **Sin dependencias**: No requiere herramientas externas
- ✅ **Portabilidad**: Funciona en cualquier sistema con gcc

### Desventajas:
- ❌ **Más código**: Implementación más extensa
- ❌ **Mantenimiento**: Requiere más esfuerzo de mantenimiento
- ❌ **Optimización**: Menos optimizado que herramientas especializadas

## 📚 Referencias Técnicas

- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [Compilers: Principles, Techniques, and Tools](https://en.wikipedia.org/wiki/Compilers:_Principles,_Techniques,_and_Tools)
- [Recursive Descent Parsing](https://en.wikipedia.org/wiki/Recursive_descent_parser)
- [LL Parser](https://en.wikipedia.org/wiki/LL_parser)