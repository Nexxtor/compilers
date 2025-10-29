# Parser LL(1) con Lex/Yacc

## 📋 Descripción

Implementación de un analizador léxico y parser LL(1) utilizando las herramientas **Flex** (Lex) y **Bison** (Yacc) para la siguiente gramática:

```
E  -> T E'
E' -> + T E' | ε
T  -> F T'
T' -> * F T' | ε
F  -> ( E ) | ident
```

## 🛠️ Herramientas Requeridas

- **gcc**: Compilador C
- **flex**: Generador de analizadores léxicos
- **bison**: Generador de analizadores sintácticos

### Instalación en macOS:
```bash
brew install flex bison gcc
```

### Instalación en Ubuntu/Debian:
```bash
sudo apt-get install flex bison gcc
```

## 📁 Estructura de Archivos

```
01-parser_yacc/
├── lexer.l           # Especificación del analizador léxico (Flex)
├── parser.y          # Especificación del parser (Bison)
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

### Ejecutar interactivamente:
```bash
make run
```

### Ejecutar pruebas automáticas:
```bash
make test           # Casos válidos
make test-errors    # Casos con errores
make test-all       # Todas las pruebas
```

### Limpiar archivos generados:
```bash
make clean
```

## 📝 Ejemplos de Uso

### Entrada válida:
```
a + b * c
```

### Salida esperada:
```
=== ANÁLISIS SINTÁCTICO EXITOSO ===
Árbol de análisis sintáctico:
E: +
  F: a
  T: *
    F: b
    F: c
```

### Casos válidos:
- `a` - Identificador simple
- `a + b` - Suma
- `a * b` - Multiplicación
- `(a + b)` - Expresión con paréntesis
- `a + b * c` - Precedencia de operadores
- `(a + b) * c` - Expresión compleja

### Casos con errores:
- `a +` - Operador sin operando derecho
- `+ a` - Operador sin operando izquierdo
- `(a` - Paréntesis sin cerrar
- `a b` - Dos identificadores consecutivos

## 🔧 Características Implementadas

### Analizador Léxico (lexer.l):
- ✅ Reconocimiento de identificadores (`[a-zA-Z][a-zA-Z0-9_]*`)
- ✅ Reconocimiento de operadores (`+`, `*`)
- ✅ Reconocimiento de paréntesis (`(`, `)`)
- ✅ Manejo de espacios en blanco y saltos de línea
- ✅ Reporte de errores léxicos con posición
- ✅ Seguimiento de línea y columna

### Analizador Sintáctico (parser.y):
- ✅ Implementación de gramática LL(1)
- ✅ Construcción de árbol de análisis sintáctico
- ✅ Manejo de precedencia de operadores
- ✅ Manejo de asociatividad izquierda
- ✅ Reporte de errores sintácticos
- ✅ Liberación de memoria del árbol

### Funcionalidades Adicionales:
- ✅ Generación de árbol de análisis sintáctico visual
- ✅ Mensajes de error detallados con posición
- ✅ Casos de prueba exhaustivos
- ✅ Makefile con múltiples opciones
- ✅ Documentación completa

## 📊 Gramática y Precedencia

La gramática implementada maneja correctamente:

1. **Precedencia**: `*` tiene mayor precedencia que `+`
2. **Asociatividad**: Ambos operadores son asociativos por la izquierda
3. **Paréntesis**: Modifican la precedencia natural

### Tabla de Precedencia:
| Operador | Precedencia | Asociatividad |
|----------|-------------|---------------|
| `*`      | Alta        | Izquierda     |
| `+`      | Baja        | Izquierda     |
| `()`     | Máxima      | N/A           |

## 🧪 Casos de Prueba

### Archivo `test_input.txt`:
Contiene casos válidos que cubren todas las producciones de la gramática.

### Archivo `test_errores.txt`:
Contiene casos que deben generar errores léxicos o sintácticos.

## 🔍 Análisis de la Implementación

### Ventajas de usar Lex/Yacc:
- ✅ Generación automática de código
- ✅ Manejo robusto de errores
- ✅ Optimización automática
- ✅ Sintaxis declarativa clara
- ✅ Herramientas maduras y probadas

### Limitaciones:
- ❌ Dependencia de herramientas externas
- ❌ Menos control sobre el proceso de análisis
- ❌ Curva de aprendizaje para la sintaxis específica

## 📚 Referencias

- [Flex Manual](https://westes.github.io/flex/manual/)
- [Bison Manual](https://www.gnu.org/software/bison/manual/)
- [Compilers: Principles, Techniques, and Tools (Dragon Book)](https://en.wikipedia.org/wiki/Compilers:_Principles,_Techniques,_and_Tools)