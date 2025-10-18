# Analizador Lexicográfico con Flex - Ejemplo Pedagógico

Este proyecto demuestra cómo crear un analizador lexicográfico (lexer) usando **Flex** para una calculadora simple.

## 📋 Descripción

El analizador reconoce los siguientes elementos léxicos:
- **Números**: Enteros y decimales (ej: `42`, `3.14`)
- **Identificadores**: Variables (ej: `x`, `resultado`, `var1`)
- **Operadores**: `+`, `-`, `*`, `/`
- **Paréntesis**: `(`, `)`
- **Asignación**: `=`
- **Espacios**: Se ignoran
- **Salto de línea**: Marca fin de expresión

## 🛠️ Requisitos

### macOS
```bash
# Instalar Flex usando Homebrew
brew install flex

# Verificar instalación
flex --version
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install flex
```

## 🚀 Compilación y Ejecución

### Opción 1: Usando Makefile
```bash
# Verificar que Flex esté instalado
make check-flex

# Compilar
make

# Ejecutar
make run

# Limpiar archivos generados
make clean
```

### Opción 2: Comandos manuales
```bash
# 1. Generar código C desde el archivo Flex
flex calculadora.l

# 2. Compilar el ejecutable
gcc -o calculadora lex.yy.c -lfl

# 3. Ejecutar
./calculadora
```

## 📝 Ejemplos de Uso

Al ejecutar el programa, puedes ingresar expresiones como:

```
x = 3.14 + 2 * (5 - 1)
resultado = 10 / 2
y = x + resultado
```

### Salida esperada:
```
=== ANALIZADOR LEXICOGRAFICO - CALCULADORA ===
Ingrese expresiones matemáticas (Ctrl+D para terminar):

x = 3.14 + 2 * (5 - 1)
TOKEN: IDENTIFICADOR, Nombre: x
TOKEN: ASIGNACION (=)
TOKEN: NUMERO, Valor: 3.14
TOKEN: SUMA (+)
TOKEN: NUMERO, Valor: 2.00
TOKEN: MULTIPLICACION (*)
TOKEN: PARENTESIS_IZQ ()
TOKEN: NUMERO, Valor: 5.00
TOKEN: RESTA (-)
TOKEN: NUMERO, Valor: 1.00
TOKEN: PARENTESIS_DER ()
TOKEN: FIN_LINEA
```

## 📚 Estructura del Archivo Flex

### 1. Sección de Declaraciones (`%{ ... %}`)
```c
%{
#include <stdio.h>
#include <stdlib.h>
// Definiciones de tokens y variables globales
%}
```

### 2. Definiciones de Patrones
```flex
DIGITO      [0-9]
NUMERO      {DIGITO}+(\.{DIGITO}+)?
IDENTIFICADOR {LETRA}({LETRA}|{DIGITO})*
```

### 3. Reglas de Reconocimiento (`%% ... %%`)
```flex
%%
{NUMERO}        { /* Acción para números */ }
"+"             { /* Acción para suma */ }
%%
```

### 4. Código C Adicional
```c
int main() {
    // Función principal
}
```

## 🔍 Conceptos Clave

### Expresiones Regulares en Flex
- `[0-9]`: Cualquier dígito
- `[a-zA-Z]`: Cualquier letra
- `+`: Una o más repeticiones
- `?`: Cero o una repetición
- `\.`: Punto literal (escapado)

### Variables Especiales
- `yytext`: Contiene el texto del token actual
- `yylval`: Variable para almacenar valores
- `yylex()`: Función que retorna el siguiente token

### Funciones Importantes
- `yylex()`: Función principal del lexer
- `yywrap()`: Indica si hay más entrada que procesar
- `atof()`: Convierte string a número decimal

## 🎯 Ejercicios Propuestos

1. **Agregar más operadores**: `%`, `^` (potencia)
2. **Soporte para comentarios**: `// comentario`
3. **Palabras reservadas**: `if`, `while`, `for`
4. **Números hexadecimales**: `0xFF`
5. **Strings**: `"texto entre comillas"`

## 🐛 Manejo de Errores

El lexer detecta caracteres no reconocidos:
```
ERROR: Caracter no reconocido '@' en línea 1
```

## 📖 Referencias

- [Manual de Flex](https://westes.github.io/flex/manual/)
- [Tutorial de Lex/Yacc](https://www.epaperpress.com/lexandyacc/)
- [Expresiones Regulares](https://regexr.com/)

## 🤝 Próximos Pasos

Este lexer puede integrarse con:
1. **Bison/Yacc**: Para crear un parser completo
2. **Árbol Sintáctico**: Para análisis semántico
3. **Intérprete**: Para evaluar expresiones
4. **Compilador**: Para generar código