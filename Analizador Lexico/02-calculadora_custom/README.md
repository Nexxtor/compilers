# Analizador Lexicográfico en C Puro - Ejemplo Pedagógico

Este proyecto demuestra cómo implementar un **analizador lexicográfico** (lexer) desde cero usando **C puro**, sin dependencias de Flex o herramientas externas. El análisis se realiza **caracter por caracter**.

## 🎯 Objetivo Pedagógico

Mostrar la implementación manual de un lexer para entender:
- Cómo funciona internamente un analizador lexicográfico
- Manejo de estado y posición en el archivo
- Reconocimiento de patrones sin expresiones regulares
- Gestión de memoria y buffers
- Control de flujo en análisis léxico

## 📋 Características

### Tokens Reconocidos
- **Números**: Enteros y decimales (`42`, `3.14159`)
- **Identificadores**: Variables (`x`, `resultado`, `variable_larga`)
- **Operadores**: `+`, `-`, `*`, `/`
- **Paréntesis**: `(`, `)`
- **Asignación**: `=`
- **Fin de línea**: `\n`
- **Espacios**: Se ignoran automáticamente

### Información de Posición
- **Número de línea**: Para cada token
- **Número de columna**: Posición exacta en la línea
- **Manejo de errores**: Con ubicación precisa

## 🛠️ Compilación y Ejecución

### Compilar
```bash
# Opción 1: Usando Makefile
make

# Opción 2: Comando directo
gcc -Wall -Wextra -std=c99 -g -o calculadora calculadora.c
```

### Ejecutar

#### Modo Interactivo
```bash
# Entrada desde teclado
make run
# o
./calculadora
```

#### Modo Archivo
```bash
# Con archivo de entrada
./calculadora test_input.txt

# Usando Makefile
make test
```

#### Pruebas Específicas
```bash
# Probar manejo de errores
make test-errors

# Ejecutar todos los ejemplos
make test-all

# Comparar con versión Flex
make compare
```

## 📝 Ejemplos de Uso

### Entrada de Ejemplo
```
x = 42
y = 3.14159
resultado = x + y * 2
expresion = (10 - 5) / 2
```

### Salida Esperada
```
=== ANALIZADOR LEXICOGRAFICO - CALCULADORA (C PURO) ===
Implementación sin Flex - Análisis caracter por caracter

TOKEN: IDENTIFICADOR, Nombre: x
TOKEN: ASIGNACION (=)
TOKEN: NUMERO, Valor: 42.00
TOKEN: FIN_LINEA
TOKEN: IDENTIFICADOR, Nombre: y
TOKEN: ASIGNACION (=)
TOKEN: NUMERO, Valor: 3.14
TOKEN: FIN_LINEA
...
```

## 🔍 Arquitectura del Código

### Estructura Principal

```c
// Enumeración de tipos de token
typedef enum {
    TOKEN_NUMERO, TOKEN_SUMA, TOKEN_RESTA,
    TOKEN_IDENTIFICADOR, TOKEN_EOF, ...
} TipoToken;

// Estructura del token
typedef struct {
    TipoToken tipo;
    double valor_numerico;
    char lexema[256];
    int linea, columna;
} Token;
```

### Funciones Clave

#### 1. **Control de Entrada**
```c
int leer_caracter(void);           // Lee siguiente caracter
void retroceder_caracter(void);    // Retrocede un caracter
void saltar_espacios(void);        // Ignora espacios
```

#### 2. **Reconocimiento de Tokens**
```c
Token leer_numero(void);           // Reconoce números
Token leer_identificador(void);    // Reconoce variables
Token obtener_siguiente_token(void); // Función principal
```

#### 3. **Utilidades**
```c
void imprimir_token(Token token);  // Muestra información
const char* nombre_token(TipoToken); // Convierte a string
```

## 🧠 Algoritmo de Análisis

### Flujo Principal
1. **Inicialización**: Configurar archivo de entrada
2. **Lectura**: Obtener caracter actual
3. **Clasificación**: Determinar tipo de token
4. **Construcción**: Leer token completo
5. **Retorno**: Devolver token construido
6. **Repetición**: Hasta EOF

### Reconocimiento de Números
```c
// Algoritmo simplificado
while (es_digito(caracter) || (caracter == '.' && !tiene_punto)) {
    agregar_a_buffer(caracter);
    leer_siguiente_caracter();
}
```

### Reconocimiento de Identificadores
```c
// Algoritmo simplificado
while (es_letra(caracter) || es_digito(caracter) || caracter == '_') {
    agregar_a_buffer(caracter);
    leer_siguiente_caracter();
}
```

## 🔄 Comparación con Flex

| Aspecto | C Puro | Flex |
|---------|--------|------|
| **Dependencias** | Ninguna | Requiere Flex |
| **Control** | Total | Limitado |
| **Complejidad** | Alta | Baja |
| **Rendimiento** | Optimizable | Optimizado |
| **Flexibilidad** | Máxima | Estructurada |
| **Mantenimiento** | Manual | Automático |

## 🎓 Conceptos Demostrados

### 1. **Máquina de Estados Finitos**
- Estado actual del analizador
- Transiciones entre estados
- Reconocimiento de patrones

### 2. **Gestión de Buffers**
- Lectura caracter por caracter
- Construcción de lexemas
- Manejo de memoria

### 3. **Manejo de Errores**
- Detección de caracteres inválidos
- Reporte de posición exacta
- Recuperación de errores

### 4. **Análisis Predictivo**
- Lookahead de un caracter
- Retroceso cuando es necesario
- Decisiones basadas en contexto

## 🧪 Archivos de Prueba

### `test_input.txt`
Casos válidos para verificar funcionamiento correcto.

### `test_errores.txt`
Casos con errores para probar manejo de excepciones.

### `ejemplos.txt`
Conjunto completo de ejemplos con comentarios.

## 🚀 Ejercicios Propuestos

### Nivel Básico
1. **Agregar operador módulo** (`%`)
2. **Soporte para números hexadecimales** (`0xFF`)
3. **Operadores de comparación** (`==`, `!=`, `<`, `>`)

### Nivel Intermedio
4. **Comentarios de línea** (`// comentario`)
5. **Strings literales** (`"texto"`)
6. **Palabras reservadas** (`if`, `while`, `for`)

### Nivel Avanzado
7. **Comentarios multilínea** (`/* ... */`)
8. **Caracteres de escape** (`\n`, `\t`, `\"`)
9. **Estados del lexer** (para contextos diferentes)

## 🔧 Mejoras Posibles

### Optimizaciones
- **Buffer circular** para mejor rendimiento
- **Tabla de hash** para palabras reservadas
- **Pool de memoria** para tokens

### Funcionalidades
- **Modo debug** con información detallada
- **Estadísticas** de análisis
- **Exportación** a diferentes formatos

## 📚 Referencias

- [Compiladores: Principios, Técnicas y Herramientas](https://www.amazon.com/Compilers-Principles-Techniques-Tools-2nd/dp/0321486811) (Libro del Dragón)
- [Crafting Interpreters](https://craftinginterpreters.com/)
- [Documentación de C99](https://www.iso.org/standard/29237.html)

## 🤝 Siguiente Paso

Este ejemplo prepara para:
- **Análisis sintáctico** (parsers)
- **Árboles de sintaxis abstracta**
- **Análisis semántico**
- **Generación de código**

---

**Nota**: Este implementación es pedagógica. Para proyectos de producción, considera usar herramientas como Flex/Bison que están optimizadas y probadas extensivamente.